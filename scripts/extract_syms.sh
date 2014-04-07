#!/bin/bash

IDIR="$1"
ODIR="$2"
if [ -z "$READELF" ]; then
	READELF=$(which arm-eabi-readelf)
fi
if [ ! -x "$READELF" ]; then
	echo "Can't find readelf in your path."
	echo "Try setting the READELF variable"
	echo ""
	exit 1
fi

if [ ! -d "$IDIR" -o ! -d "$ODIR" ]; then
	echo "usage: $0 {input/dir} {output/dir}"
	exit 1
fi

LIBS=($(find "$IDIR/" -type f -name *.so | sed "s,$IDIR/*,,"))

for l in "${LIBS[@]}"; do
	ofile="${ODIR}/${l/.so/.sym}"
	mkdir -p "$(dirname "$ofile")" 2>/dev/null
	echo "Extracting symbols from $(basename "$l")..."
	$READELF -W -s "${IDIR}/$l" | grep "GLOBAL\|WEAK" | grep -v UND | awk '{print $8}' > "$ofile"
done
