from __future__ import division
import os
import sys
from stat import *

bytes_processed = 0


def walktree(top, callback):
    """recursively descend the directory tree rooted at top,
       calling the callback function for each regular file"""
    global bytes_processed
    for f in os.listdir(top):
        pathname = os.path.join(top, f)
        mode = os.stat(pathname).st_mode
        if S_ISDIR(mode):
            walktree(pathname, callback)
        elif S_ISREG(mode):
            callback(pathname)
            bytes_processed += os.path.getsize(pathname)
            sys.stderr.write("Processed: %.2f GB . . . . .\r" %
                            (bytes_processed / (1024 * 1024 * 1024)))
        else:
            print "Skipping %s", pathname


def filter_calls(filter_file):
    """create a filter in order to exclude traces wrapped at
       calls not belonging to a specific group """
    if not filter_file:
        return []
    temp = []
    f = open(filter_file, "r")
    for line in f:
        temp.append(line.split('\n')[0] + ':' + 'libc.so')
    return temp
