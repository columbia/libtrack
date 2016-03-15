#!/bin/bash

function usage() {
	echo "usage: $0 symfile incdir"
	exit 1
}

symfile="$1"
incdir="$2"

if [ ! -f "$symfile" -o ! -d "$incdir" ]; then
	usage
fi

total=0
found=0

for sym in $(cat "$symfile"); do
	total=$(($total+1))
	grep -r "\<$sym\>" "$incdir" | grep -i "inline\|#\s*define\s*${sym}" >/dev/null
	if [ $? -eq 0 ]; then
		echo "Found '$sym'"
		echo "$sym" >> hacks
		found=$(($found+1))
	fi
done

echo "$total Symbols"
echo "$found inline/pre-processor symbols"
