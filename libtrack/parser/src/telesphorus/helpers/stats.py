"""
Module documenation
goes here
"""

from __future__ import division
from telesphorus.helpers import dict_utils

PATH_DELIMITER = '->'


def libs(trace_graph):
    """Generate per lib stats"""
    stats = {}
    for lib_call in trace_graph.native_calls:
        lib_name = lib_call.split(':')[1]
        if not lib_name in stats:
            stats[lib_name] = trace_graph.native_calls[lib_call]
        else:
            stats[lib_name] = dict_utils.merge(
                stats[lib_name],
                trace_graph.native_calls[lib_call])
    for lib in stats:
        yield lib, stats[lib]


def lib_calls(trace_graph):
    """Generate "who I called" stats per library function call"""
    for lib_call in trace_graph.native_calls:
        yield lib_call, trace_graph.native_calls[lib_call]


def stack_depth(trace_graph):
    """Generate stack depth stats"""
    for depth in trace_graph.stack_depth:
        yield depth, trace_graph.stack_depth[depth]


def posix_timing(trace_graph):
    """Generate timing stats"""
    for posix_call in trace_graph.timing_info:
        yield posix_call, trace_graph.timing_info[posix_call]


def posix_calls(trace_graph):
    """Generate  "who called me" stats per posix system call"""
    for posix_call in trace_graph.posix_calls:
        yield posix_call, trace_graph.posix_calls[posix_call]


def posix_calls_per_lib(trace_graph):
    """Generate  "who called me" stats per posix system call"""
    for posix_call in trace_graph.posix_calls_per_lib:
        yield posix_call, trace_graph.posix_calls_per_lib[posix_call]


def posix_invocations(trace_graph):
    """Return number of total POSIX API invokations"""
    return sum(map(lambda x: x[1], trace_graph.full_paths_dict.items()))


def average_libs_per_path(trace_graph):
    """Return average number of libraries of full paths"""
    items = posix_invocations(trace_graph)
    total = 0
    for path in trace_graph.full_paths_dict:
        occur = int(trace_graph.full_paths_dict[path])
        path = path.split(PATH_DELIMITER)
        path = list(set(map(lambda s: s.split(':')[1], path)))
        total += len(path) * occur
    if items == 0:
        return 0
    return total / items


def average_full_path_len(trace_graph):
    """Return average lenght of full paths"""
    items = posix_invocations(trace_graph)
    total_len = 0
    for path in trace_graph.full_paths_dict:
        total_len += len(path.split(PATH_DELIMITER)) * \
            int(trace_graph.full_paths_dict[path])
    if items == 0:
        return 0
    return total_len / items


def full_paths(trace_graph):
    """Generate all full paths stored"""
    for full_path in trace_graph.full_paths_dict:
        yield full_path, trace_graph.full_paths_dict[full_path]
