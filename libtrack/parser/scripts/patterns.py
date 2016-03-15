#!/usr/bin/env python
"""
module documentation
goes here
"""
import sys
import re
from telesphorus.helpers import path_utils


calls_list = []


def main(argv=sys.argv):
    """
    Identify missing abstration of frequently occuring
    patterns and print them.
    """
    if len(argv) != 7:
        usage(argv)
    for i in range(len(argv)):
        if argv[i] == "-t":
            trace_dir = argv[i + 1]
        if argv[i] == "-s":
            samples = int(argv[i + 1])
        if argv[i] == "-m":
            max_len = int(argv[i + 1])

    path_utils.walktree(trace_dir, build_from_file)
    lines_read = 0
    for window_size in range(3, max_len + 1):
        patterns = {}
        timing = {}
        for i in range(0, len(calls_list) - window_size):
            local = map(lambda l: l.split(':')[0],
                        calls_list[i: i + window_size])
            ttime = sum(map(int, map(lambda l: l.split(':')[1],
                                        calls_list[i: i + window_size])))
            # the following will remove circles
            if sorted([local.count(i) for i in local])[-1] > 1:
                continue
            current = ' '.join(local)
            if current in patterns:
                patterns[current] += 1
                timing[current] += ttime
            else:
                patterns[current] = 1
                timing[current] = ttime
        printed = {}
#        for pattern in sorted(timing,
#                              key=timing.get,
#                              reverse=True
#                             )[:samples]:
        for pattern in sorted(patterns,
                              key=patterns.get,
                              reverse=True
                             )[:samples]:
                # filter out permutations
                temp = pattern.split(' ')[:]
                temp.sort()
                if ' '.join(temp) in printed:
                    continue
                else:
                    printed[' '.join(temp)] = 1
                print pattern, patterns[pattern], timing[pattern]
        print "\n"


def build_from_file(filename):
    for call in yield_timed_calls(filename):
        calls_list.append(call)


def yield_timed_calls(filename):
    try:
        f = open(filename)
    except IOError, error:
        print >> sys.stderr, "I/O error while opening file: %s" % error
        return

    for line in f:
        try:
            labels = line.split(':')[:3]
        except Exception, error:
            print >> sys.stderr, "Unhandled Exception:", error, filename
            return
        if labels[1:] in [['LOG', 'T']]:
            if len(line.split(':')) != 5:
                continue
            try:
                call = line.split(':')[3] + ':'
                if call[:11] == "epoll_wait_":
                    call = "epoll_wait_:"
                else:
                    call = re.sub(r'_B:|_D:|_E:|_F:|_f:|_K:|_k:|_P:|_p:|_S:|_U:',    ':', call)
                time = line.split(':')[4]
                msec = int(time.split('.')[0]) * 10 ** 6 \
                        + int(time.split('.')[1])
            except Exception, error:
                print >> sys.stderr, "Unhandled Exception:", error, filename
                return
            # special handling of epoll - it should go to cache later
            yield call + str(msec)
    f.close()


def usage(argv):
    print ("Usage:%s -t TRACE-DIR -s SAMPLES-NUMBER -m MAX-LEN") % argv[0]
    sys.exit(-1)


if __name__ == '__main__':
    sys.exit(main())
