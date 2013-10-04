#!/bin/bash

LIBPFX=real_

ADB=`which adb`
if [ -z "$ADB" ]; then
	echo "Can't find adb in your path!"
	exit 1
fi

libdir="$1"
destroot="${2:-/data/cells/trace/system/lib}"

if [ -z "$libdir" -o ! -d "$libdir" ]; then
	echo ""
	echo "usage: $0 /path/to/libdir [/dest/root]"
	echo ""
	exit 1
fi

lib="$(basename ${libdir%/})"
_lib="_${lib:1}"
symlnk="${_lib//./_}"
real="${LIBPFX}$lib"

realpath="${libdir%/}/${real}"
if [ ! -f "$realpath" ]; then
	echo ""
	echo "Can't find stripped / prepped library '$realpath'"
	echo ""
	exit 1
fi

wrapper="$(cat "${libdir}/Android.mk" | grep LOCAL_MODULE | sed 's/.*=[ \t]*//').so"
wrapper_dir=

if [ ! -d "$OUT" ]; then
	if [ -f "${libdir%/}/${wrapper}" ]; then
		wrapper_dir="${libdir%/}"
	else
		echo "This script should be run from an Android build environment."
		echo "I'm going to help you out though. Please provide the path where"
		echo "the build wrapped library '$wrapper' can be found."
		echo -n "build dir: "
		read wrapper_dir
	fi
fi
if [ -z "$wrapper_dir" ]; then
	wrapper_dir="${OUT}/system/lib"
fi

wrapped_path="${wrapper_dir}/${wrapper}"
if [ ! -f "${wrapped_path}" ]; then
	echo ""
	echo "Can't find '${wrapped_path}' - have you built the module yet?"
	echo ""
	exit 1
fi

target_lib="${destroot}/${lib}"
replacement_lib="${destroot}/$(basename ${wrapped_path})"

echo "Installing into '$destroot'..."
$ADB push "${wrapped_path}" "${destroot}"
$ADB push "${realpath}" "${destroot}"
$ADB shell "rm -f '${destroot}/${symlnk}'; ln -s '${real}' '${destroot}/${symlnk}'"
$ADB shell "chmod 644 '${replacement_lib}'; chmod 644 '${destroot}/$(basename ${realpath})'"
echo "done."

echo ""
echo "I am about to overwrite ${target_lib}!"
echo -n "Are you sure it's OK? [y|N]: "
read ans

if [ ! "${ans:0:1}" = "y" -a ! "${ans:0:1}" = "Y" ]; then
	echo "OK, I didn't replace anything :-)"
	echo "The final step is to replace the current library with the wrapped one:"
	echo "    cp '${destroot}/$(basename ${wrapped_path})' '${target_lib}'"
	echo "    export LD_PRELOAD=${destroot}/${symlnk}"
	echo ""
	exit 0
fi

echo "Here we go (I'll back it up to ${target_lib}.bak first)!"
$ADB shell "if [ ! -f '${target_lib}.bak' ]; then cp '${target_lib}' '${target_lib}.bak'; fi"
$ADB shell "cp '${replacement_lib}' '${target_lib}'; chmod 644 '${target_lib}'"
echo "done."

echo ""
echo "Be sure to preload the data-only library:"
echo "    export LD_PRELOAD=${destroot}/${symlnk}"
echo ""

