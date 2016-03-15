"""
Doc string of module
goes here
"""
from __future__ import division
from telesphorus.helpers import stats

PATH_DELIMITER = '->'


def obscurity_ratio(trace_graph, settings):
    threashold = settings.OBSCURITY_SAMPLES
    temp_dict = {}
    total = stats.posix_invocations(trace_graph)
    for node in trace_graph:
        for edge in trace_graph.out_edges(node, data=True):
            # skip circles returning to the same library
            if edge[0].split(':')[1] == edge[1].split(':')[1]:
                continue
            weight_out = edge[2]['weight']
            library = edge[0].split(':')[1]
            if library not in temp_dict:
                temp_dict[library] = weight_out
            else:
                temp_dict[library] += weight_out
    for data in sorted(temp_dict.items(), key=lambda s: s[1], reverse=True)[:threashold]:
        yield data[0], data[1] / total
