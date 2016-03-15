#!/usr/bin/env python
"""
module documentation
goes here
"""
import sys
from telesphorus.helpers import parsing
from telesphorus.helpers import path_utils

PATH_DELIMITER = '->'
full_paths_dict = {}


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
    for full_path in full_paths_dict:
        print "Full path: %s occured %d times." % (full_path, full_paths_dict[full_path])


def build_from_file(filename):
    for path in parsing.yield_paths(filename):
        if len(path) < 2:
            continue
        if PATH_DELIMITER.join(path) in full_paths_dict:
            full_paths_dict[PATH_DELIMITER.join(path)] += 1
        else:
            full_paths_dict[PATH_DELIMITER.join(path)] = 1


def usage(argv):
    print ("Usage:%s -t TRACE-DIR") % argv[0]
    sys.exit(-1)


if __name__ == '__main__':
    sys.exit(main())
