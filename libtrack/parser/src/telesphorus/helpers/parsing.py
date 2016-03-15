"""
module documentation
goees here
"""
from __future__ import division
import sys
import re

def yield_paths(filename, timing_info=None, filter_calls=[]):
    """Retrieves full paths from a trace file

    For input a trace file returns all full  paths ending
    in a POSIX call, until the end of the file. Full paths are
    returned as lists of elements function calls along with the
    respective library name.
    For example, "__libc_init:libc.so" is the signature for
    the call "__libc_init" bellonging to lib "libc.so"

    Args:
        filename

    Returns:
        fullpath as a list

    Raises:
        Exception: if log file is corrupted
    """
    try:
        f = open(filename)
    except IOError, error:
        print >> sys.stderr, "I/O error while opening file: %s" % error
        return

    cache = Cache()
    for line in f:
        try:
            labels = line.split(':')[:3]
        except Exception, error:
            print >> sys.stderr, "Unhandled Exception:", error, filename
            continue
            #return
        if labels[1:] in [['BT', 'REPEAT']]:
            try:
                cache.repeat_next = int(line.split(':')[3])
            except Exception, error:
                #print >> sys.stderr, "Unhandled Exception:", error, filename
                continue
                #return

        elif labels[1:] in [['BT', 'START']]:
           # flush the bloody cache
            if cache.dirty_native_path:
                if cache.native_path[-1] in filter_calls:
                    cache.dirty_native_path = False
                    cache.dirty_dalvik_path = False
                    cache.repeat_current = cache.repeat_next
                    cache.repeat_next = 1
                    continue
                # seperately retrieve fd type for open
                if cache.native_path[-1] == 'open:libc.so':
                    cache.native_path[-1] = 'open_' + cache.fd_buff + ':libc.so'
                for _ in range(cache.repeat_current):
                    #yield cache.native_path
                    if cache.dirty_dalvik_path:
                        yield cache.dalvik_path + cache.native_path 
                    else:
                        yield cache.native_path
                cache.dirty_native_path = False
                cache.dirty_dalvik_path = False
                cache.repeat_current = cache.repeat_next
                cache.repeat_next = 1
            try:
                frames = int(line.split(':')[3])
                cache.set_native(f, frames)
            except (ValueError, IndexError), error:
                #print >>  sys.stderr, "Error:", error, "in file:", filename
                continue
                #return
            except StopIteration, error:
                #print >> sys.stderr, "Error:", error, "unexpected end in File:", filename
                continue
                #return
            except Exception as error:
                #print >> sys.stderr, "Unhandled Exception:", error, "in file:", filename
                continue
                #return

        elif labels[1:] in [['DVM', 'BT_START']]:
            try:
                frames = int(line.split(':')[3])
                cache.set_dalvik(f, frames)
            except (ValueError, IndexError), error:
                #print >> sys.stderr, "Error:", error, "in file:", filename
                continue
                #return
            except StopIteration, error:
                #print >> sys.stderr, "Error:", error, "unexpected end in File:", filename
                continue
                #return
            except Exception, error:
                #print >> sys.stderr, "Unhandled Exception:", error, "in file:", filename
                continue
                #return

        elif labels[1:] in [['LOG', 'I']]:
            try:
                cache.set_fd_buff(line)
            except (ValueError, IndexError), error:
                #print >> sys.stderr, "Error:", error, "in file:", filename
                continue
                #return
            except StopIteration, error:
                #print >> sys.stderr, "Error:", error, "unexpected end in File:", filename
                continue
                #return
            except Exception, error:
                #print >> sys.stderr, "Unhandled Exception:", error, "in file:", filename
                continue
                #return

        elif labels[1:] in [['BT_REPEAT', '1']]:
            cache.dirty_dalvik_path = True

        elif labels[1:2] in [['CALL']]:
            if len(line.split('.')) > 2:
                continue
            try:
                yield ["NO_BACKTRACE:NO_BACKTRACE", labels[2].split('\n')[0] + ':libc.so']
            except Exception, error:
                #print >> sys.stderr, "Unhandled Exception:", error, "in file:", filename
                continue
                #return

        elif labels[1:] in [['LOG', 'T']]:
            if timing_info == None:
                continue
            # nothing else I can do now for this kind of corrupted logs     
            #if len(line.split(':')) != 5:
            #    continue
            try:
                call = line.split(':')[3] + ":libc.so"
                if call in filter_calls:
                    continue
                time = line.split(':')[4].split('\n')[0]
                nsec = 1000000000*int(time.split('.')[0]) + int(time.split('.')[1])
            except Exception, error:
                print >> sys.stderr, "Unhandled Exception:", error, "in file:", filename
                continue
                #return
            # special handling of epoll - it should go to cache later
            if call[:11] == "epoll_wait_":
                call = "epoll_wait_:libc.so"
            else:
                # this regexec makes things sooooo slow
                call = re.sub(r'_B:|_D:|_E:|_F:|_f:|_K:|_k:|_P:|_p:|_S:|_U:', ':', call)

            if call not in timing_info:
                timing_info[call] = [nsec]
            else:
                timing_info[call].append(nsec)

        else:
            continue

    # flush cache
    if cache.dirty_native_path:
        # seperately retrieve fd type for open
        if cache.native_path[-1] == 'open:libc.so':
            cache.native_path[-1] = 'open_' + cache.fd_buff + ':libc.so'
        for _ in range(cache.repeat_current):
            #yield cache.native_path
            if cache.dirty_dalvik_path:
                yield cache.dalvik_path + cache.native_path
            else:
                yield cache.native_path
    f.close()

class Cache():
    """class documentation"""

    def __init__(self):
        """doc"""
        self.fd_buff = ""
        self.native_path = []
        self.dalvik_path = []
        self.repeat_next = 1
        self.repeat_current = 1
        self.dirty_dalvik_path = False
        self.dirty_native_path = False

    def set_fd_buff(self, line):
        fd_type = line.split(':')[3][-2]
        if fd_type in ['B','D','E','F','k','K','p','P','S','U']:
            self.fd_buff = fd_type
        else:
            self.fd_buff = ""

    def set_dalvik(self, f, frames):
        """doc"""
        path = []
        for _ in range(frames):
            line = f.next()
            name = line.split(':')[3]
            call = name + ':' + 'DVM'
            path.insert(0, call)
        self.dalvik_path = path
        self.dirty_dalvik_path = True

    def set_native(self, f, frames):
        """In this method we parse lines corresponding
        to stack frames. For each frame retrieve symbol
        and library -- Special handling for epoll_wait
        """
        path = []
        for _ in range(frames):
            line = f.next()
            lib = line.split(':')[6]
            name = line.split(':')[4]
            if lib.split('(')[0] == '_ibc_so':
                continue
            if name == '??':  # if no symbol, just keep offset
                name = line.split(':')[4]
            if name[:11] == "epoll_wait_":
                name = "epoll_wait_"
            call = name + ':' + lib.split('(')[0]
            path.insert(0, call)
        self.native_path = path
        self.dirty_native_path = True
