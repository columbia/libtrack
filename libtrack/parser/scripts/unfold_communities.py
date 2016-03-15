#!/usr/bin/env python
"""
This is a handly script taking as input a text file
whose lines represent weighted edges of a graph. It
applies the louvain method for community detection,
and produces the following outputs:

1) square vector of communities interconnection,
    appropriate for d3 javascript

2) communities

3) Obscurity ratio per community

Nodes can be filtered out if their degree-in is less
than a threashold.
"""
from __future__ import division
import networkx as nx
import numpy as nm
import pydot
import community
import sys
from math import log
import matplotlib.pyplot as plt


def main(argv=sys.argv):
    """General graph statistics"""
    if len(argv) not in [2, 3, 4, 5, 6, 7, 8]:
        usage(argv)
    if argv[1] in ["-h"]:
        usage(argv)
    _plot_graph = _adj_matrix = _community_metrics = None
    fullpaths = "this_will_never_exist"
    graph_file = "this_will_never_exist"
    for i in range(len(argv)):
        if argv[i] == "--ADJ-MATRIX":
            _adj_matrix = True
        if argv[i] == "--PLOT-GRAPH":
            _plot_graph = True
        if argv[i] == "--COMMUNITY-METRICS":
            _community_metrics = True
        if argv[i] == "-p":
            fullpaths = argv[i + 1]
        if argv[i] == "-g":
            graph_file = argv[i + 1]

    G = nx.DiGraph()
    f = open(graph_file, "r")
    for line in f:
        try:
            a, b, weight = line.split(',')[0],\
                           line.split(',')[1],\
                           int(line.split(',')[2][:-1])
        except Exception, error:
            print >> sys.stderr, "Error:", error, "\nDrop corrupted line:", line
            continue
        G.add_weighted_edges_from([(a, b, weight)])
    f.close()

    partition = louvain_method(G.to_undirected())

    if _community_metrics:
        community_metrics(G, partition, fullpaths)

    if _adj_matrix:
        print "ADJ-MATRIX:"
        vector = adjacency_matrix(G, partition)
        for i in range(len(vector)):
            print list(vector[i]), ','
        print "\n"

    if _plot_graph:
        plot_graph(G, partition, fullpaths)


def louvain_method(G):
    partition = community.best_partition(G)
    print "Graph nodes:", len(G.nodes()), "egdes:", len(G.edges())
    print "Partitions:", len(set(partition.values())),\
          "Modularity:", community.modularity(partition, G.to_undirected())
    print "\n\n"
    return partition


def adjacency_matrix(G, partition):
        all_communities = []
        for com in set(partition.values()):
            local_non_posix = [node for node in partition.keys()
                               if partition[node] == com
                               and G.out_edges(node)]
            if local_non_posix:
                all_communities.append(local_non_posix)

            local_posix = [node for node in partition.keys()
                           if partition[node] == com
                           and not G.out_edges(node)]
            if local_posix:
                all_communities.append(local_posix)

        vector = nm.zeros((len(all_communities),
                           len(all_communities)),
                           dtype=nm.int)

        # for each community, iterate all edges starting from it
        # add the weight in respective column of current community's line.
        # caution: Do not add twice edges - if DiGraph that is no problem.
        for i in range(len(all_communities)):
            c = all_communities[i]
            # for each node of a community
            for node in c:
                # for each edge of the node
                for edge in G.edges(node, data=True):
                    # search to which community edge leads
                    for ii in range(len(all_communities)):
                        if edge[1] in all_communities[ii]:
                            vector[i][ii] += edge[2]['weight']
        return vector


def community_metrics(G, partition, fullpaths):
    paths, counters = {}, {}
    obsc, recall = __obsc_recall_dict(G, partition, fullpaths)
    i = 0
    for com in set(partition.values()):
        local_non_posix = [node for node in partition.keys()
                           if partition[node] == com
                           and G.out_edges(node)]
        local_posix = [node for node in partition.keys()
                       if partition[node] == com
                       and not G.out_edges(node)]

        posix_invocations = 0
        for node in local_posix:
            for edge in G.in_edges(node, data=True):
                posix_invocations += edge[2]['weight']

        if local_posix:
            print "Subcommunity:", i,\
                  "Obscurity ratio:", obsc[str(i)],\
                  "Recall:", recall[str(i)], '\n',\
                  "for POSIX subcommunity:", i + 1,\
                  "with POSIX in:", posix_invocations, '\n'
        print "Subcommunity:", i
        print "-----------------------------------"
        print "Libraries:"
        print_sorted(G, local_non_posix, prune=True)
        i += 1

        if local_posix:
            print "\nPOSIX Subcommunity:", i, "part of:", i - 1
            print "POSIX in:", posix_invocations, '\n'
            print "\nPOSIX:"
            print_sorted(G, local_posix)
            print "-----------------------------------"
            i += 1
        print "###################################\n\n\n"


def print_sorted_temp(G, nodes_list, prune=False):
    nodes_dict_out = {}
    nodes_dict_in = {}
    for node in nodes_list:
        w = 0
        for edge in G.out_edges(node, data=True):
            w += edge[2]['weight']
        nodes_dict_out[node] = w

    for node in nodes_list:
        w = 0
        for edge in G.in_edges(node, data=True):
            w += edge[2]['weight']
        nodes_dict_in[node] = w

    myset = []
    sorted_keys = sorted(nodes_dict_in, key=nodes_dict_in.get, reverse=True)
    threashold = nodes_dict_in[sorted_keys[0]]
    for node in sorted_keys:
        if prune and nodes_dict_in[node] < threashold / 10:
                break
        if node.split(':')[1] not in myset:
            myset.append(node.split(':')[1])
            
    for node in myset:
        print node


def print_sorted(G, nodes_list, prune=False):
    nodes_dict_out = {}
    nodes_dict_in = {}
    for node in nodes_list:
        w = 0
        for edge in G.out_edges(node, data=True):
            w += edge[2]['weight']
        nodes_dict_out[node] = w

    for node in nodes_list:
        w = 0
        for edge in G.in_edges(node, data=True):
            w += edge[2]['weight']
        nodes_dict_in[node] = w

    sorted_keys = sorted(nodes_dict_in, key=nodes_dict_in.get, reverse=True)
    threashold = nodes_dict_in[sorted_keys[0]]
    for node in sorted_keys:
        if prune and nodes_dict_in[node] < threashold / 10:
                break
        print node, nodes_dict_in[node]


def plot_graph(G, partition, fullpaths):
    obsc, _ = __obsc_recall_dict(G, partition, fullpaths)

    vector = adjacency_matrix(G, partition)
    AA = nm.matrix(vector)
    GG = nx.from_numpy_matrix(AA, create_using=nx.DiGraph())
    nx.write_dot(GG, './graph.dot')
    GG = pydot.graph_from_dot_file('./graph.dot')
    degree_in, degree_out, edges_in, edges_out = {}, {}, {}, {}
    for i in range(len(vector)):
        GG.add_node(pydot.Node(str(i)))
        degree_in[str(i)] = degree_out[str(i)] = 0
        edges_out[str(i)] = edges_in[str(i)] = 0

    for e in GG.get_edges():
        weight = int(e.get_attributes()['weight'])
        # do not consider circles for degree_in/out, edges_in/out
        if not e.get_destination() == e.get_source():
            degree_in[str(e.get_destination())] += weight
            edges_in[str(e.get_destination())] += 1
            degree_out[str(e.get_source())] += weight
            edges_out[str(e.get_source())] += 1
        if e.get_destination() == e.get_source():
            e.set_style('dotted')
        if weight > 200000:
            e.set_color('red')
            w = "%.1f" % (weight / 10 ** 6)
            e.set_label(w)
        elif weight > 100000:
            e.set_color('blue')
        elif weight > 10000:
            e.set_color('green')
#        elif weight > 1000:
#            e.set_color('purple')
        else:
            GG.del_edge(e.get_source(), e.get_destination())
            e.set_color('black')

    max_in = (log(max(degree_in.values())))
    last = None
    clusters = []
    for n in GG.get_node_list():
        n.set_fixedsize(True)
        # no incoming edges
        if degree_in[n.get_name()] == 0:
            n.set_height(1)
            n.set_width(1)
            n.set_shape('box')
        # no outgoing edges -- There are POSIX
        elif degree_out[n.get_name()] == 0:
            n.set_height(1)
            n.set_width(1)
            n.set_shape('doublecircle')
            cluster = pydot.Cluster(n.get_name(),
                                    # Obscured by previous non-POSIX subcommunity
                                    label=obsc[str(int(n.get_name()) - 1)],
                                    style='dotted')
            cluster.add_node(n)
            cluster.add_node(pydot.Node(str(int(n.get_name()) - 1)))
            clusters.append(cluster)
        else:
            n.set_height(1 * (log(degree_in[n.get_name()])) / max_in)
            n.set_width(1 * (log(degree_in[n.get_name()])) / max_in)
        label = "{" + str(n.get_name()) + "}\n" +\
                str(edges_in[n.get_name()]) + "\:" +\
                str(edges_out[n.get_name()]) + "\n" +\
                str("%.1f" % (degree_in[n.get_name()] / 10 ** 6)) + "\:" +\
                str("%.1f" % (degree_out[n.get_name()] / 10 ** 6))
        n.set_label(label)
    for cluster in clusters:
            GG.add_subgraph(cluster)
    GG.write('./graph.pdf', format='pdf')


def __obsc_recall_dict(G, partition, fullpaths):
    paths, counters, o, r = {}, {}, {}, {}
    try:
        f = open(fullpaths, "r")
    except Exception, error:
        print >> sys.stderr, "Unhandled exception while openingg file:", error
        return
    for line in f:
        try:
            path = line.split(' ')[2].split('->')[:]
            count = int(line.split(' ')[4])
        except (IndexError, ValueError), error:
            print >> sys.stderr, "Error:", error, "\nDrop corrupted line:", line
            continue
        if path[-1] not in paths:
            paths[path[-1]] = []
        paths[path[-1]].append(path[:-1])
        counters['->'.join(path)] = count
    f.close()
    i = 0
    for com in set(partition.values()):
        local_non_posix = [node for node in partition.keys()
                           if partition[node] == com
                           and G.out_edges(node)]
        local_posix = [node for node in partition.keys()
                       if partition[node] == com
                       and not G.out_edges(node)]
        posix_invocations = 0
        obscurity_weight = recall_weight = 0
        for node in local_posix:
            for edge in G.in_edges(node, data=True):
                posix_invocations += edge[2]['weight']

        for node in local_posix:

            for edge in G.in_edges(node, data=True):
                # predecessor within community
                if edge[0] in local_non_posix:
                    recall_weight += edge[2]['weight']

            for path in paths[node]:
                # predecessor within community
                if partition[path[-1]] == com:
                    for nnn in path:
                        # any node in this path outside community
                        if partition[nnn] != com:
                            key = list(path)
                            key.append(node)
                            obscurity_weight += counters['->'.join(key)]
                            break
        if local_posix:
            o[str(i)] = "%.2f" % (obscurity_weight / posix_invocations)
            r[str(i)] = "%.2f" % (recall_weight / posix_invocations)
        i += 1
        if local_posix:
            i += 1
    return o, r


def usage(argv):
    print ("Usage:%s -g GRAPH-FILE [--COMMUNITY-METRICS -p FULLPATHS_FILE ]"
           "[--PLOT-GRAPH -p FULLPATHS_FILE ] [--ADJ-MATRIX]") % argv[0]
    sys.exit(-1)


if __name__ == '__main__':
    sys.exit(main())
