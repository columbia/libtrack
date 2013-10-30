#!/bin/bash
#
# wrap_syscalls.sh
# Extract syscall entry points and wrap them in a library
#
CDIR="$(cd `dirname $0` && pwd)"

# keep a "pretty-fied" version of the command for the C file header
# sorry about the sed-mess:
#     the OSX version doesn't like things like \s or \d # :-(
# (look at the generated output for an idea of what's going on)
__CMD="`echo -e '\n *\t'`$0 \\`echo -e '\n *\t'`\
	$(echo $@ | \
	  sed "s/\([^ ][^ ]*\)[ ][ ]*\([^ ][^ ]*\) /\1 \2 \\\\\\`echo -e '\n *\t\t'`/g")"


TOOL_PFX=${CROSS_COMPILE:-arm-eabi-}

FILE=`which file`
OTOOL=`which otool`
SED=`which gsed`
ELF_OBJDUMP=`which ${TOOL_PFX}objdump`
ELF_READELF=`which ${TOOL_PFX}readelf`

if [ -z "$SED" ]; then
	# hope for the best...
	SED=sed
fi

if [ -z "$FILE" ]; then
	echo "WARNING: Can't find 'file' utility be sure to specify the library type!"
fi

ARCH=android

WRAPALL=0
LIB=
LIBDIR=
LIBTYPE=
LIBPATH=
OUTDIR=.

LIBPFX=real_

function usage() {
	echo -e "Usage: $0 --lib path/to/library "
	echo -e "                          [--wrap-all]"
	echo -e "                          [--arch {android|arm|x86}]"
	echo -e "                          [--type {elf|macho}]"
	echo -e "                          [--out path/to/output/dir]"
	echo -e ""
	echo -e "\t--wrap-all                      Wrap (trace) all functions in the library"
	echo -e "\t--arch {android|arm|x86}        Architecture for syscall wrappers"
	echo -e "\t--lib path/to/library           Library (or directory of libraries) to search for syscalls"
	echo -e ""
	echo -e "\t--type {elf|macho}              Specify the type of input library (avoid auto-detection)"
	echo -e ""
	echo -e "\t--out output/dir                Directory to put output C wrappers (defaults to .)"
	echo -e ""
	echo -e "Environment variables:"
	echo -e "\tCROSS_COMPILE                   Used to properly dump ELF objects. Defaults to 'arm-eabi-'"
	echo -e ""
	exit 1
}

#
# Process input args
#
while [[ ! -z "$1" ]]; do
	case "$1" in
		-h | --help )
			usage
			;;
		--wrap-all )
			WRAPALL=1
			shift
			;;
		--arch )
			if [ "$2" != "android" ]; then
				echo "E:"
				echo "E: Architectures other than 'android' are not yet supported!"
				echo "E:"
				usage
			fi
			ARCH="$2"
			shift
			shift
			;;
		--lib )
			if [ -d "$2" ]; then
				LIBDIR="$2"
			elif [ -f "$2" ]; then
				LIB=$2
			else
				echo "E:"
				echo "E: Invalid lib parameter: '$2'"
				echo "E:"
				usage
			fi
			shift
			shift
			;;
		--type )
			LIBTYPE=$2
			shift
			shift
			;;
		--out )
			OUTDIR=$2
			shift
			shift
			;;
		* )
			echo -e "Unknown option '$1': ignoring"
			shift
			;;
	esac
done

#
# Validate inputs
#
if [ -z "$LIB" -a -z "$LIBDIR" ]; then
	usage
fi

if [ -z "$LIBTYPE" -a ! -z "$LIBDIR" ]; then
	echo ""
	echo "You must specify a library type with --type when processing a directory!"
	echo ""
	usage
fi

#
# type of wrapping to do
#
if [ -z "$LIBTYPE" ]; then
	if [ ! -z "$($FILE "$LIB" | grep -i Mach-O)" ]; then
		LIBTYPE="macho"
	elif [ ! -z "$($FILE "$LIB" | grep ELF)" ]; then
		LIBTYPE="elf"
	fi
fi


#
# Verify tools/input
#
if [ "$LIBTYPE" = "macho" ]; then
	STRIP=`which strip`
	if [ -z "$OTOOL" -o ! -x "$OTOOL" ]; then
		echo "Can't find otool in your path - have you installed the command-line Developer tools?"
		exit 2
	fi
elif [ "$LIBTYPE" = "elf" ]; then
	STRIP="${CDIR}/elfmod/elfmod.py"
	if [ -z "$ELF_OBJDUMP" -o ! -x "$ELF_OBJDUMP" ]; then
		echo "Can't find ${TOOL_PFX}objdump in your path."
		exit 2
	fi
	if [ -z "$ELF_READELF" -o ! -x "$ELF_READELF" ]; then
		echo "Can't find ${TOOL_PFX}readelf in your path."
		exit 2
	fi
fi

if [ -z "$STRIP" -o ! -x "${STRIP}" ]; then
	echo "ERROR: Can't find '${STRIP}' in your path!"
	exit 2
fi


tf_code=
tf_syscalls=
tf_funclist=
declare -a SYSCALLS=( )
SYSCALLS_SEQ=
declare -a FUNCTIONS=( )
declare -a DUP_SYMS=( )
declare -a DUP_SYM_SEQ_A=( )
DUP_SYMS_SEQ=

function extract_code() {
	echo -e "\tdisassembling..."
	if [ "$LIBTYPE" = "elf" ]; then
		${ELF_OBJDUMP} -d "$1" > "$tf_code"
	elif [ "$LIBTYPE" = "macho" ]; then
		${OTOOL} -tV "$1" > "$tf_code"
	else
		echo "E:"
		echo "E: unsupported lib type:'$LIBTYPE'"
		echo "E:"
		exit 1
	fi
}

#
# Locate all syscalls in a given library
#
function extract_syscalls() {
	echo -e "\textracting syscalls..."
	local extract_pl="${CDIR}/scripts/${LIBTYPE}_${ARCH}_syscalls.pl"
	if [ ! -f "$extract_pl" ]; then
		echo "E:"
		echo "E: missing syscall extraction perl script: '$extract_pl'"
		echo "E:"
	fi
	SYSCALLS=( $(cat "$tf_code" | "$extract_pl") )
	SYSCALLS_SEQ="$(seq 0 $((${#SYSCALLS[@]}-1)))"

	echo -n "" > "$tf_syscalls"
	for s in $SYSCALLS_SEQ; do
		sc=${SYSCALLS[$s]#*:}
		echo "$sc" >> "$tf_syscalls"
	done
}

function extract_syscall_tree() {
	echo -e "\textracting intra-library syscall tree..."
	local extract_pl="${CDIR}/scripts/${LIBTYPE}_${ARCH}_syscall_tree.pl"
	if [ ! -f "$extract_pl" ]; then
		echo "E:"
		echo "E: missing syscall extraction perl script: '$extract_pl'"
		echo "E:"
	fi
	SYSCALLS+=( $("$extract_pl" "$tf_code" "$tf_syscalls") )
	SYSCALLS_SEQ="$(seq 0 $((${#SYSCALLS[@]}-1)))"
}

function find_dup_elf_symbols() {
	local lib="$1"
	local tmpfile="${CDIR}/.$$.$RANDOM.tmp"
	local RE_line='^([0-9a-f]{1,8})[[:space:]]+g.*\.text[[:space:]]+[0-9a-f]{8}[[:space:]]+([a-zA-Z_][a-zA-Z0-9_]+)$'
	local prev_addr=
	local addr=
	local prev_func=
	local func=
	echo -e -n "\tfinding duplicate symbols..."
	declare -a syms=( )

	sym_idx=0
	${ELF_OBJDUMP} -T "$lib" | grep ' g ' | grep .text | sort > "$tmpfile"
	while read -r line; do
		if [[ $line =~ $RE_line ]]; then
			addr="${BASH_REMATCH[1]}"
			func="${BASH_REMATCH[2]}"
			if [ "$addr" = "$prev_addr" ]; then
				syms+=( $func )
				#echo -n -e ",$func"
			else
				prev_addr=$addr
				prev_func=$func
				if [ ${#syms[@]} -gt 1 ]; then
					DUP_SYMS[$sym_idx]="${syms[@]}"
					DUP_SYM_SEQ_A[$sym_idx]="$(seq 0 $((${#syms[@]}-1)))"
					sym_idx=$(($sym_idx + 1))
				fi
				syms=( $func )
			fi
		fi
	done < "$tmpfile"
	if [ ${#syms[@]} -gt 1 ]; then
		${DUP_SYMS[$sym_idx]}=$syms
		sym_idx=$(($sym_idx + 1))
	fi
	rm -f "$tmpfile"
	echo "${#DUP_SYMS[@]}"
	DUP_SYMS_SEQ="$(seq 0 $((${#DUP_SYMS[@]}-1)))"
}

__line_len=0
function write_sym() {
	local _type="$1"
	local _lib="$2"
	local _fcn="$3"
	local _dst="$4"
	local _dup=0
	declare -a syms=( )

	for ii in $DUP_SYMS_SEQ; do
		syms=( ${DUP_SYMS[$ii]} )
		for s in ${DUP_SYM_SEQ_A[$ii]}; do
			if [ "${syms[$s]}" = "${_fcn}" ]; then
				_dup=1
				break;
			fi
		done
		if [ $_dup -gt 0 ]; then
			break;
		fi
	done

	if [ $_dup -gt 0 ]; then
		echo "${_type}_START(${_lib}, ${_fcn})" >> "${_dst}"
		echo -n "${#syms[@]}."
		__line_len=$(($__line_len + 2))
		for sym in "${syms[@]}"; do
			if [ "${sym}" != "${_fcn}" ]; then
				echo "FUNC_ALIAS(${sym})" >> "${_dst}"
			fi
		done
		echo "${_type}_END(${_lib}, ${_fcn})" >> "${_dst}"
	else
		echo -n "."
		__line_len=$(($__line_len + 1))
		echo "${_type}_FUNC(${_lib}, ${_fcn})" >> "${_dst}"
	fi

	if [ $__line_len -gt 80 ]; then
		echo -e -n "\n\t                             "
		__line_len=40
	fi
}


#
# Start the output file
#
FILE_HEADER=
FILE_FOOTER=
function __setup_wrapped_lib() {
	local dir="$1"
	local asm="$2"
	local module_name="$(basename "${asm%.*}")_wrapped"

	# We have to set these variables here to pick up
	# any new definitions of LIB, LIBPATH, etc.
	FILE_HEADER=$(cat -<<__EOF
/*
 * Wrapper library for ${LIB}
 *
 * WARNING: EDIT AT YOUR OWN RISK!
 * WARNING: This file was automatically generated by: ${__CMD}
 *
 */
#define WRAP_TRACE_FUNC wrapped_tracer
#include <asm/wrap_start.h>

WRAP_LIB(${LIB}, ${LIBPATH})

__EOF)

	FILE_FOOTER=$(cat -<<__EOF
#include <asm/wrap_end.h>
#undef WRAP_TRACE_FUNC
__EOF)

	ANDROID_MK=$(cat -<<__EOF
LOCAL_PATH := \$(call my-dir)
include \$(CLEAR_VARS)
LOCAL_CFLAGS := -fPIC \\
		-O3 \\
		-DHAVE_ARM_TLS_REGISTER -DANDROID_SMP=1 \\
		-fno-stack-protector -Werror \\
		-DLIBNAME=${LIB} \\
		-D_IBNAM_=$(basename ${LIBPATH})
LOCAL_CONLYFLAGS := -std=gnu99
LOCAL_CPPFLAGS := -std=c++0x
LOCAL_C_INCLUDE := \$(LOCAL_PATH)/platform/android/\$(TARGET_ARCH)/include
LOCAL_ASFLAGS += -fPIC -I\$(LOCAL_PATH)/arch/\$(TARGET_ARCH)/include \\
		 -I\$(LOCAL_PATH)/platform/android/\$(TARGET_ARCH)/include
LOCAL_NO_CRT := true
LOCAL_SRC_FILES := \\
		platform/android/crtbegin_so.c \\
		$(basename "$asm") \\
		wrap_lib.c \\
		backtrace.c \\
		platform/android/\$(TARGET_ARCH)/crtend_so.S
# platform/android/__stack_chk_fail.cpp
LOCAL_MODULE:= ${module_name}
LOCAL_ADDITIONAL_DEPENDENCIES := \$(LOCAL_PATH)/Android.mk
LOCAL_LDFLAGS := -L\$(LOCAL_PATH) \$(LOCAL_PATH)/${LIBPFX}${LIB} -Wl,-soname=$LIB
LOCAL_SHARED_LIBRARIES := libdl
LOCAL_WHOLE_STATIC_LIBRARIES :=
LOCAL_SYSTEM_SHARED_LIBRARIES :=
__EOF)
	if [ "${LIB}" = "libc.so" ]; then
		ANDROID_MK=$(cat -<<__EOF
$ANDROID_MK
LOCAL_SRC_FILES += \\
		platform/android/libc_wrappers.c \\
		platform/android/libc_init.cpp
LOCAL_CFLAGS += -D_LIBC=1 \\
		-DCRT_LEGACY_WORKAROUND \\
		-DPTHREAD_DEBUG -DPTHREAD_DEBUG_ENABLED=0
__EOF)
	fi
	ANDROID_MK=$(cat -<<__EOF
$ANDROID_MK
include \$(BUILD_SHARED_LIBRARY)
__EOF)

	mkdir -p "$dir" 2>/dev/null
	ln -s "${CDIR}/backtrace.c" "${dir}" 2>/dev/null
	ln -s "${CDIR}/wrap_lib.c" "${dir}" 2>/dev/null
	ln -s "${CDIR}/wrap_lib.h" "${dir}" 2>/dev/null
	ln -s "${CDIR}/arch" "${dir}" 2>/dev/null
	ln -s "${CDIR}/platform" "${dir}" 2>/dev/null
	ln -s "${CDIR}/scripts/Makefile.${ARCH}" "${dir}/Makefile" 2>/dev/null
	if [ "${ARCH}" = "android" ]; then
		echo "${ANDROID_MK}" > "${dir}/Android.mk"
	fi

	# start the ASM file
	echo "${FILE_HEADER}" > "${asm}"
}


function write_wrappers() {
	#local _libname="${OUTDIR}/$1/$(basename $1)"
	local _libname="$1"
	local dir=$(dirname "${_libname}")
	local _libpath="$2"
	local _outfile
	local libname=
	local fcn=
	local num=
	LIBPATH=${_libpath}
	if [ "$LIBTYPE" = "elf" ]; then
		libname=${_libname%.so}.S
	else
		libname=${_libname%.dylib}.S
	fi

	LIB="$(basename $1)"
	echo -e "\tcreating library project in '${dir}'..."
	__setup_wrapped_lib "${dir}" "${libname}"

	echo -e -n "\twriting ${#SYSCALLS[@]} syscall wrappers"
	__line_len=40
	for sc in "${SYSCALLS[@]}"; do
		fcn=${sc#*:}
		num=${sc%:*}
		write_sym "WRAP" "${LIB}" "${fcn}" "${libname}"
	done
	echo ""

	echo "" >> "${libname}"

	echo -e -n "\twriting ${#FUNCTIONS[@]} function wrappers"
	__line_len=40
	for e in "${FUNCTIONS[@]}"; do
		write_sym "PASS" "${LIB}" "${e}" "${libname}"
	done
	echo ""

	echo "${FILE_FOOTER}" >> "${libname}"
}

__FOUND_SYSCALL=0
function is_syscall() {
	local funcname="$1"
	local sc=
	__FOUND_SYSCALL=0
	for s in $SYSCALLS_SEQ; do
		sc=${SYSCALLS[$s]#*:}
		if [ "$sc" = "$funcname" ]; then
			__FOUND_SYSCALL=1
			return
		fi
	done
}

__SHOULD_WRAP=0
function should_wrap_android_elf() {
	local fcn="$1"

	__SHOULD_WRAP=1
	if [ "$fcn" = ".plt" ]; then
		__SHOULD_WRAP=0
		return
	fi
	if [ "$fcn" = "__libc_init" ]; then
		__SHOULD_WRAP=0
		return;
	fi
	if [ "$fcn" = "__errno" ]; then
		__SHOULD_WRAP=0
		return;
	fi
}

#
# Find entry points in a Mach-O binary
#
function macho_functions() {
	local dylib="$1"
	local entries=
	local _libarch=
	local libarch=

	if [ ! "$ARCH" = "arm" ]; then
		echo "E:"
		echo "E: Architecture '$ARCH' is unsupported!"
		echo "E:"
		exit 1
	fi

	_libarch=$(${OTOOL} -h "$dylib" | grep architecture \
			| tail -1 | sed 's,.*(architecture \(.*\)):.*,\1,')
	if [ ! -z "$_libarch" ]; then
		libarch="-arch $_libarch"
	fi
	entries=( $(${OTOOL} $libarch -tV "$dylib" | grep '^[^[]*:\s*$' \
				| grep -v "$dylib" | $SED 's/:[ ]*//g') )
	FUNCTIONS=( )
	for idx in $(seq 0 $((${#entries[@]}-1))); do
		is_syscall "${entries[$idx]}"
		if [ $__FOUND_SYSCALL -eq 0 ]; then
			FUNCTIONS+=( "${entries[$idx]}" )
		fi
	done
	echo -e "\t    (found ${#entries[@]} Mach-O entry points, ${#FUNCTIONS[@]} non-syscall)"
}

#
# Find entry points in an ELF binary
#
function elf_functions() {
	local lib="$1"
	local fcn=
	local entries=( $(cat "$tf_code" \
				| grep '^[0-9a-f][0-9a-f]* <[^>][^>]*>:' \
				| $SED 's/.*<\([^>]*\)>:/\1/') )
	FUNCTIONS=( )
	FUNCTIONS_SEQ="$(seq 0 $((${#entries[@]}-1)))"
	echo -e "\tparsing function list..."
	for idx in $FUNCTIONS_SEQ; do
		fcn="${entries[$idx]}"
		is_syscall "$fcn"
		should_wrap_${ARCH}_${LIBTYPE} "$fcn"
		if [ $__FOUND_SYSCALL -eq 0 -a $__SHOULD_WRAP -eq 1 ]; then
			FUNCTIONS+=( "$fcn" )
		fi
	done
	echo -e "\t    (found ${#entries[@]} ELF entry points, ${#FUNCTIONS[@]} non-syscall)"
	find_dup_elf_symbols "$lib"
}

function extract_functions() {
	local libname="$1"
	echo -e "\textracting functions..."
	if [ "$LIBTYPE" = "elf" ]; then
		elf_functions "$libname"
	elif [ "$LIBTYPE" = "macho" ]; then
		macho_functions "$libname"
	else
		echo "E:"
		echo "E: unsupported library type '$LIBTYPE'"
		echo "E:"
	fi
}

__STRIPPED_LIB=

function strip_elf_library() {
	local in="$1"
	local out="$2"
	local symtable="$3"
	local _soname="$(basename $1)"
	local soname=${_soname:1}

	# Copy the input file, and modify the output file in-place
	cp "$in" "$out"

	# get a list of all the global symbols, and prefix each one with
	# the GNU strip option "-N "
	${ELF_OBJDUMP} -T "$out" | grep ' g' | grep .text \
			| awk -F' ' '{print $6}' > "${tf_funclist}"

	${ELF_READELF} -s "$out" | grep -v FUNC | grep -v UND \
			| tail +4 | head -1 \
			| awk '{print "SAVED(0x"$2","$8")"}' > "${symtable}"

	# The 'STRIP' variable here points to our custom 'elfmod.py' script
	# that modifies ELF libraries in-place
	${STRIP} hidesyms "$out" "${tf_funclist}" >> "${symtable}"

	# Modify the SONAME of the output library to avoid name collisions
	# libdoes_stuff.so -> _ibdoes_stuff_so
	${STRIP} soname "$out" "_${soname//./_}"
}

function strip_macho_library() {
	local in="$1"
	local out="$2"
	local symtable="$3"
	local _libarch=
	local libarch=

	if [ ! "$ARCH" = "arm" ]; then
		echo "E:"
		echo "E: Architecture '$ARCH' is unsupported!"
		echo "E:"
		exit 1
	fi

	_libarch=$(${OTOOL} -h "$dylib" | grep architecture \
			| tail -1 | sed 's,.*(architecture \(.*\)):.*,\1,')
	if [ ! -z "$_libarch" ]; then
		libarch="-arch $_libarch"
	fi

	# Get a list of functions
	${OTOOL} $libarch -tV "$dylib" \
			| grep '^[^0-9].*:$' \
			| grep -v "$dylib" \
			| $SED 's/:[ ]*$//' > "$tf_funclist"

	# TODO: write out 'symtable' with format 'SYM(ADDR,NAME)' (one-per-line)

	# Apple Strip options:
	# -u        :  Save all undefined symbols
	# -R {file} :  Remove all symbols listed in {file}
	# -i        :  Ignore symbols listed in {file} that are _not_ in ${in}
	# -S        :  Remove debugging symbols
	# -o {file} :  Write output library to {file}
	${STRIP} -u -R "${tf_funclist}" -i -S -o "$out" - "$in"
}

function strip_library() {
	local libname="$1"
	local outname="$2"
	local symfile="$3"

	mkdir -p "$(dirname $outname)" 2>/dev/null
	echo -e "\tstripping '${libname}' into '${outname}'..."
	if [ "$LIBTYPE" = "elf" ]; then
		strip_elf_library "$libname" "$outname" "$symfile"
	elif [ "$LIBTYPE" = "macho" ]; then
		strip_macho_library "$libname" "$outname" "$symfile"
	else
		echo "E:"
		echo "E: unsupported library type '$LIBTYPE'"
		echo "E:"
	fi
}

LIB_BASE=
if [ "$LIBTYPE" = "elf" ]; then
	if [ "$ARCH" = "android" ]; then
		LIB_BASE="/system/lib"
	else
		LIB_BASE="/lib"
	fi
elif [ "$LIBTYPE" = "macho" ]; then
	LIB_BASE="/usr/lib"
fi

tf_code="${CDIR}/.$$.$RANDOM.code.tmp"
tf_syscalls="${CDIR}/.$$.$RANDOM.syscalls.tmp"
tf_funclist="${CDIR}/.$$.$RANDOM.funclist.tmp"

if [ -z "${LIB}" -a -d "${LIBDIR}" ]; then
	ALL_LIBS=
	if [ "$LIBTYPE" = "elf" ]; then
		ALL_LIBS="$(find "${LIBDIR}" -type f -name *so)"
	elif [ "$LIBTYPE" = "macho" ]; then
		ALL_LIBS="$(find "${LIBDIR}" -type f -name *dylib)"
	fi
	echo "LIBS of type $LIBTYPE in '$LIBDIR': '$ALL_LIBS'"
	for l in "$ALL_LIBS"; do
		echo "Processing '$l'..."
		extract_code "$l"
		if [ $WRAPALL -eq 0 ]; then
			extract_syscalls "$l"
			extract_syscall_tree
		fi
		extract_functions "$l"
		# use path relative to 'LIBDIR'
		_l="${l#${LIBDIR}/}"
		__l="_${_l:1}"
		_l_out="${OUTDIR}/${_l}/$(basename ${_l})"
		_l_real="${OUTDIR}/${_l}/${LIBPFX}$(basename ${_l})"
		strip_library "${l}" "${_l_real}" "${OUTDIR}/${_l}/real_syms.h"
		write_wrappers "${_l_out}" "${LIB_BASE}/${__l//./_}"
	done
else
	echo "Processing '$LIB'..."
	_l=$(basename ${LIB})
	__l="_${_l:1}"
	_l_out="${OUTDIR}/${LIB}/${_l}"
	_l_real="${OUTDIR}/${LIB}/${LIBPFX}${_l}"
	extract_code "$LIB"
	if [ $WRAPALL -eq 0 ]; then
		extract_syscalls "$LIB"
		extract_syscall_tree
	fi
	extract_functions "$LIB"
	strip_library "$LIB" "${_l_real}" "${OUTDIR}/${LIB}/real_syms.h"
	write_wrappers "${_l_out}" "${LIB_BASE}/${__l//./_}"
fi

rm -f "$tf_code"
rm -f "$tf_syscalls"
rm -f "$tf_funclist"
