"""
Doc string of module
goes here
"""

from __future__ import division
from telesphorus.helpers import stats

PATH_DELIMITER = '->'


def hidden_abstraction(trace_graph, settings):
    """
    Identify hidden abstractions and print those
    that occured with a percentage more than "threashold".
    """
    threashold = settings.HIDDEN_ABSTR_THREASHOLD
    for posix_call, stat in trace_graph.posix_calls.items():
        total = sum(map(lambda x: x[1], stat.items()))
        # group stats by libraries
        local_stat = {}
        for call, count in stat.items():
            lib = call.split(':')[1]
            if lib in local_stat:
                local_stat[lib] += count
            else:
                local_stat[lib] = count
        # in case you want to check function callers, instead of
        # library callers, uncomment the following line.
        #local_stat = stat
        for lib in sorted(local_stat, key=local_stat.get, reverse=True):
            if 100 * local_stat[lib] / total >= threashold:
                yield posix_call, lib, local_stat[lib], total


def obsolete_abstraction(trace_graph, settings):
    """
    Identify obsolete abstractions and print those
    that occured with paercentage less than "threashold".
    """
    threashold = settings.OBSOLETE_ABSTR_THREASHOLD
    posix_total = stats.posix_invocations(trace_graph)
    for posix_call, stat in trace_graph.posix_calls.items():
        call_total = sum(map(lambda x: x[1], stat.items()))
        if 100 * call_total / posix_total <= threashold:
            yield posix_call, call_total, posix_total


def missing_abstractions(trace_graph, settings):
    """
    Identify missing abstration of frequently occuring
    patterns and print them.
    """
    posix_calls_list = trace_graph.posix_calls_list
    max_window_size = settings.MISSING_ABSTR_MAX_WINDOW_SIZE
    threashold = settings.MISSING_ABSTR_SAMPLES
    for window_size in range(3, max_window_size + 1):
        patterns = {}
        for i in range(0, len(posix_calls_list) - window_size):
            local = posix_calls_list[i: i + window_size]
            # the following will remove circles
            if sorted([local.count(i) for i in local])[-1] > 1:
                continue
            #current = '->'.join(map(lambda s: s.split(':')[2], local))
            current = '->'.join(local)
            if current in patterns:
                patterns[current] += 1
            else:
                patterns[current] = 1
        for pattern in \
            sorted(patterns, key=patterns.get, reverse=True)[:threashold]:
            yield pattern, patterns[pattern]
        print "\n"


def circular_abstractions(trace_graph, settings):
    """doc goes here"""
    threashold = settings.CIRCULAR_ABSTR_SAMPLES
    patterns = {}
    for path, counter in stats.full_paths(trace_graph):
        path = map(lambda s: s.split(':')[1], path.split('->')[:])
        item = None
        merged_path = []
        for i in range(len(path)):
            if item == path[i]:
                continue
            else:
                merged_path.append(path[i])
            item = path[i]
        merged_path = filter(('_ibc_so').__ne__, merged_path)

        for i in range(len(merged_path) - 2):
            for j in range(i + 2, len(merged_path)):
                if merged_path[i] == merged_path[j]:
                    hashable = "->".join(merged_path[i: j + 1])
                    if hashable in patterns:
                        patterns[hashable] += counter
                    else:
                        patterns[hashable] = counter

    for pattern in \
        sorted(patterns, key=patterns.get, reverse=True)[:threashold]:
        yield pattern, patterns[pattern]
