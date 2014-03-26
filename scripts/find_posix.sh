#!/bin/bash

function usage() {
	echo "usage: $0 posix_sym_file dir/of/symfiles"
	exit 1
}

symfile="$1"
if [ ! -f "$symfile" ]; then
	usage
fi

symdir="$2"
if [ ! -d "$symdir" ]; then
	usage
fi

symtotal=0
symfound=0

exec 9<$1
while read sym; do
	symtotal=$(($symtotal+1))
	echo -n "Looking for '$sym'..."
	grep -r "\<$sym\>" "$symdir" 2>/dev/null >/dev/null
	if [ $? -eq 0 ]; then
		echo " FOUND!"
		grep -r "\<$sym\>" "$symdir" 2>/dev/null >> found.syms
		symfound=$(($symfound+1))
	else
		echo " not found"
		echo "$sym" >> notimp.syms
	fi
done<&9
exec 9<&-

echo "$symtotal Symbols"
echo "$symfound Implemented"
