#!/bin/bash

DIR="${1:-.}"

GUNZIP=`which gunzip`

if [ ! -x $GUNZIP ]; then
	echo "Can't find gunzip!"
	exit 1
fi

ZDIR=$(cd "${DIR}" && pwd)
LDIR="${ZDIR}/d"
if [ ! -d "${ZDIR}" ]; then
	echo "Invalid directory: '${ZDIR}'"
	exit 1
fi
if [ ! -d "${LDIR}" ]; then
	mkdir "${LDIR}"
fi
rm -rf "${LDIR}/*" > /dev/null 2>/dev/null

ZSZ=$(du -hc "${ZDIR}"/*.gz | tail -1 | awk '{print $1}')
echo "Unpacking ${ZSZ} of logs in '${ZDIR}' into '${LDIR}'..."
pushd "${ZDIR}" >/dev/null 2>/dev/null

for i in `ls -1 *.gz`; do
	S=$(du -h "$i" | awk '{print $1}' | sed 's/[0-9][0-9]*//g; s/[^KkMm]/b/; s/b/_/; s/K/~/; s/M/|/;')
	echo -n "$S"
	$GUNZIP -c "$i" > "${LDIR}/${i/.gz}" 2>>"${ZDIR}/unpack_errors.txt"
done

echo -e "\n"
echo "Copied" "$(
for i in `ls -1 *.log`; do
    cp $i "${LDIR}/$i"
    echo "copy $i"
done | wc -l
)" "uncomplressed files in '${LDIR}'"

SZ=`du -sh d | awk '{print $1}'`
popd >/dev/null 2> /dev/null

echo ""
echo "Unpacked $SZ of logs in '${LDIR}'"
