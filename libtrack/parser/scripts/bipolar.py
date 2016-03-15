#!/usr/bin/env python
"""
module documentation
goes here
"""
import sys
import re
import matplotlib.pyplot as plt
from telesphorus.helpers import path_utils

calls = []
GLOBAL = []

def main(argv=sys.argv):
    """
    Identify missing abstration of frequently occuring
    patterns and print them.
    """
    if len(argv) != 3:
        usage(argv)
    for i in range(len(argv)):
        if argv[i] == "-t":
            trace_dir = argv[i + 1]
            path_utils.walktree(trace_dir, build_from_file)
    #        fw = open("./timeindex", "w")
            for c in calls:
                print >> fw, c[0], GLOBAL[c[1]]
            fw.close()
        if argv[i] == "-csv":
            csv = argv[i + 1]
            fw = open(csv, "r")
            build_from_csv(csv)
    points = []
    for call in calls:
        name = call[1]
        time = int(call[0])
        points.append([time, name])

 #   print len(points)
    plt.plot(map(lambda c:c[0],points), map(lambda c:c[1],points), 'ro', markersize=1, label=None)
    plt.xlabel('Time to complete (microseconds)')
    plt.xscale('log')
    plt.ylabel('POSIX calls')
    plt.title('Bipolar Time Graph')
    #plt.show()
    plt.savefig('time-bipolar.png', format='png')


def build_from_csv(filename):
    fr = open(filename, "r")
    for line in fr:
        call = line.split(' ')[1]
        time = line.split(' ')[0]
        if call not in GLOBAL:
            GLOBAL.append(call)
        calls.append([time, GLOBAL.index(call)])
    fr.close()


def build_from_file(filename):
    for (call, time) in yield_timed_calls(filename):
        if call not in GLOBAL:
            GLOBAL.append(call)
        calls.append([int(time), GLOBAL.index(call)])


def yield_timed_calls(filename):
    try:
        f = open(filename)
    except IOError, error:
        print >> sys.stderr, "I/O error while opening file: %s" % error
        return

    for line in f:
        try:
            if len(line.split(':')) > 5:
                continue
            labels = line.split(':')[:3]
        except Exception, error:
            print >> sys.stderr, "Unhandled Exception:", error, filename
            return
        if labels[1:] in [['LOG', 'T']]:
            if len(line.split(':')) != 5:
                continue
            try:
                call = line.split(':')[3] + ':libc.so'
                if call[:11] == "epoll_wait_":
                    call = "epoll_wait_"
                else:
                    call = re.sub(r'_B:|_D:|_E:|_F:|_f:|_K:|_k:|_P:|_p:|_S:|_U:',    ':', call)
                time = line.split(':')[4]
                msec = int(time.split('.')[0]) * 10 ** 6 \
                        + int(time.split('.')[1])
            except Exception, error:
                print >> sys.stderr, "Unhandled Exception:", error, filename
                continue
            yield (call, str(msec))
    f.close()


def usage(argv):
    print ("Usage:%s -t TRACE-DIR | -csv INDEX-FILE") % argv[0]
    sys.exit(-1)


if __name__ == '__main__':
    sys.exit(main())
