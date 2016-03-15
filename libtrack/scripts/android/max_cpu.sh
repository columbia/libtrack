#!/system/bin/sh

SYSCPUDIR=/sys/devices/system/cpu

echo "Maximizing CPU performance..."
for cpu in `busybox ls -1 $SYSCPUDIR/ | busybox grep cpu[0-9][0-9]*`; do
	d=$SYSCPUDIR/$cpu
	echo "    $cpu..."
	cpufreq=$d/cpufreq
	echo 1 > $d/online 2>/dev/null
	sleep 1
	echo 1 > $d/online 2>/dev/null
	sleep 1
	if [ -f "$cpufreq/scaling_governor" ]; then
		echo "        scaling:performance"
		echo "performance" > $cpufreq/scaling_governor
	fi
	if [ -f "$cpufreq/cpuinfo_max_freq" ]; then
		max=`cat $cpufreq/cpuinfo_max_freq`
		echo $max > $cpufreq/scaling_max_freq 2>/dev/null
		echo $max > $cpufreq/scaling_min_freq 2>/dev/null
		echo "        $max - $max"
	fi
done
echo "Done."
