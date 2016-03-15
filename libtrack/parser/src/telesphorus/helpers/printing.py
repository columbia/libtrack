"""
module documentation
goes here
"""
from __future__ import division
import community
import networkx as nx
import matplotlib.pyplot as plt
from telesphorus.helpers import stats
from telesphorus import abstractions
from telesphorus import obscurity

PATH_DELIMITER = '->'


def graph_stats(trace_graph):
    """General graph statistics"""
    print "\nA graph with %d nodes and %d edges created." % \
        (trace_graph.order(), trace_graph.size())
    print "Total POSIX API invokations: %d" % \
        stats.posix_invocations(trace_graph)
#    print "Average path length: %d\n\n" % \
#        stats.average_full_path_len(trace_graph)
#    print "Average libraries per path: %d\n\n" % \
#        stats.average_libs_per_path(trace_graph)
#    G = trace_graph.to_undirected()
#    partition = community.best_partition(G)
#    print "Modularity:", community.modularity(partition, G)
#    print "Partitions: ", len(set(partition.values()))
#    print "\n\n"
#    for com in set(partition.values()):
#        list_nodes = [nodes for nodes in partition.keys() if partition[nodes] == com]
#        print list_nodes
#        print ""


def lib_stats(trace_graph, settings):
    """For each lib print :
        1) The amount of times each POSIX call invoked by the above lib.
        2) Total POSIX invokations the above lib accounted for.
    """
    threashold = settings.LIB_THREASHOLD
    posix_total = stats.posix_invocations(trace_graph)
    for (lib_name, metadata) in stats.libs(trace_graph):
        total = sum(map(lambda x: x[1], metadata.items()))
        for posix_call in sorted(metadata, key=metadata.get, reverse=True):
            #if 100*metadata[posix_call]/total >= threashold:
            if metadata[posix_call] >= threashold:
                print ("Lib: %s invoked POSIX call: %s %.2f %% of "
                       "times (%d).") % (lib_name, posix_call,
                                         100 * metadata[posix_call] / total,
                                         metadata[posix_call])
    print '------'
    # comment
    for (lib_name, metadata) in stats.libs(trace_graph):
        total = sum(map(lambda x: x[1], metadata.items()))
        if 100 * total / posix_total > 0.0:
            print ("Lib: %s accounted for %.2f %% (%d) of "
                   "total POSIX invocations.") % (lib_name,
                                                 100 * total / posix_total,
                                                 total)


def lib_call_stats(trace_graph, settings):
    """For each library call, print all POXIX calls invoked"""
    threashold = settings.LIB_CALL_THREASHOLD
    #why I had the generator on sorted??
    for (lib_call, metadata) in stats.lib_calls(trace_graph):
        total = sum(map(lambda x: x[1], metadata.items()))
        for posix_call in sorted(metadata, key=metadata.get, reverse=True):
            #if 100*metadata[posix_call]/total >= threashold:
            if metadata[posix_call] >= threashold:
                print "Lib call: %s invoked POSIX call: %s %.2f %% " \
                    "of times (%d)" % (lib_call, posix_call,
                                       100 * metadata[posix_call] / total,
                                       metadata[posix_call])


def stack_depth_stats(trace_graph, settings):
    """print timing info"""
    for (depth, metadata) in stats.stack_depth(trace_graph):
        print ("STACK-DEPTH: %s %d") % (depth, metadata)


def posix_timing_stats(trace_graph, settings):
    """print timing info"""
    total = 0
    for (posix_call, metadata) in stats.posix_timing(trace_graph):
        total += sum(metadata)

    import statistics
    nl = 0
    print "#call,ptime,ttime,min,max,mean,stdev,nl(time,in,nanoseconds)"
    for (posix_call, metadata) in stats.posix_timing(trace_graph):
        nl += 1
        perc = 100*float(sum(metadata))/total
        if perc == 0.0:
            perc = 0.0000001
        elif perc <= 0.1:
            perc = 0.1000000

        if len(metadata) >= 2:
            stdev = statistics.stdev(metadata)
        else:
            stdev = 0.0
        print ("%s,%.7f,%d,%d,%d,%.2f,%.2f,%d") % (posix_call.split(':')[0], \
                perc, sum(metadata), min(metadata), max(metadata), int(sum(metadata)/len(metadata)),stdev, nl)
 
    print ("Total Time: %d") % total


def posix_call_stats(trace_graph, settings):
    """For each POSIX call, print:
        1) All library function callers
        2) Aggregate results groupeing caller into libraries
    """
    threashold = settings.POSIX_CALL_THREASHOLD
    posix_total = stats.posix_invocations(trace_graph)
    # why I had sorted(trace_graph.posix_calls(trace_graph)))?
    for (posix_call, metadata) in stats.posix_calls(trace_graph):
        total = sum(map(lambda x: x[1], metadata.items()))
        # nasty workaround
        if  posix_call.split(':')[1] != 'libc.so':# or total == 1:
            continue
        print ("POSIX call: %s invoked in total: -> %d <- times that is %.2f"
               " %% of total POSIX invocations.") % (posix_call,
                                                     total,
                                                     100 * total / posix_total)
        for lib_call in sorted(metadata, key=metadata.get, reverse=True):
            if 100 * metadata[lib_call] / total >= threashold:
                print "POSIX call: %s invoked by Lib call: %s %.2f %%" \
                    " of times (%d)" % (posix_call, lib_call,
                                        100 * metadata[lib_call] / total,
                                        metadata[lib_call])

    for (posix_call, metadata) in stats.posix_calls_per_lib(trace_graph):
        total = sum(map(lambda x: x[1], metadata.items()))
        for lib in sorted(metadata, key=metadata.get, reverse=True):
            if 100 * metadata[lib] / total >= threashold:
                print "POSIX call: %s invoked by Library: %s %.2f %%" \
                    " of times (%d)" % (posix_call, lib,
                                        100 * metadata[lib] / total,
                                        metadata[lib])


def full_path_stats(trace_graph, settings):
    """Print fullpaths"""
    threashold = settings.FULL_PATH_THREASHOLD
    for (full_path, count) in stats.full_paths(trace_graph):
        if count > threashold:
            print "Full path: %s occured %d times." % (full_path, count)


def hidden_abstractions(trace_graph, settings):
    """doc goes here"""
    for (posix_call, lib_call, metadata, total) in \
            abstractions.hidden_abstraction(trace_graph, settings):
        print "<HIDDEN ABSTRACTION> POSIX call: %s invoked by Lib: " \
            "%s %.2f %% of times (%d)" % (posix_call, lib_call,
                                          100 * metadata / total, metadata)


def obsolete_abstractions(graph, settings):
    """doc goes here"""
    for (posix_call, call_total, posix_total) in \
            abstractions.obsolete_abstraction(graph, settings):
        print "<OBSOLETE ABSTRACTION> POSIX call: %s invoked %.2f %% of " \
            "times (%d)" % (posix_call, 100 * call_total / posix_total,
                            call_total)


def missing_abstractions(graph, settings):
    """doc goes here"""
    for pattern, count in abstractions.missing_abstractions(graph, settings):
        print "<MISSING ABSTRACTION> chain:",
        for item in pattern.split('->')[:]:
                print item.split(':')[2],
        print count


def circular_abstractions(graph, settings):
    """doc goes here"""
    for pattern, count in abstractions.circular_abstractions(graph, settings):
        print "<LIBRARY CIRCLE:> chain:", pattern, count


def obscurity_ratio(graph, settings):
    """doc goes here"""
    for lib, val in obscurity.obscurity_ratio(graph, settings):
        print "Library: %s Obscurity Ratio: %.2f" % (lib, val)
