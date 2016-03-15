#!/system/bin/sh

SYSCPUDIR=/sys/devices/system/cpu

echo "Resetting CPU performance..."
for cpu in `ls $SYSCPUDIR/ | grep cpu[0-9][0-9]*`; do
	d=$SYSCPUDIR/$cpu/cpufreq
	echo "    $cpu..."
	if [ -f "$d/cpuinfo_max_freq" ]; then
		max=`cat $d/cpuinfo_max_freq 2>/dev/null`
		min=`cat $d/cpuinfo_min_freq 2>/dev/null`
		echo "        $min - $max"
		echo $max > $d/scaling_max_freq 2>/dev/null
		echo $min > $d/scaling_min_freq 2>/dev/null
		sleep 2
		min=`cat $d/cpuinfo_min_freq 2>/dev/null`
		echo "        $min - $max"
		echo $min > $d/scaling_min_freq 2>/dev/null
	fi
	if [ -f "$d/scaling_governor" ]; then
		echo "        scaling:ondemand"
		echo ondemand > $d/scaling_governor
	fi
done
echo "Done."
