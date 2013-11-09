#!/system/bin/sh

tkill=/system/bin/tkill
if [ -z "$tkill" ]; then
	echo "no tkill utility!"
	exit 1
fi
if [ ! -x "$tkill" ]; then
	echo "no tkill utility!"
	exit 1
fi

PID_LIST=`ls /data/trace_logs | grep -v sh | awk -F '.' '{print $1"."$2}' | uniq`
$tkill 12 $PID_LIST
