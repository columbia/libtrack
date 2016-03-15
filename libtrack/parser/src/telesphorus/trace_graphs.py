"""
module documentation
goes here
"""

import os
from networkx import DiGraph
from telesphorus.helpers import parsing
from telesphorus.helpers import path_utils
import re

PATH_DELIMITER = '->'


class TraceGraph(DiGraph):
    """class documentation """

    def __init__(self):
        """doc"""
        DiGraph.__init__(self)
        self.posix_calls = {}
        self.posix_calls_per_lib = {}
        self.posix_calls_list = []
        self.native_calls = {}
        self.java_calls = {}
        self.full_paths_dict = {}
        self.filter_calls = []
        self.timing_info = {}
        self.stack_depth = {}

    @classmethod
    def parse_traces(cls, trace_dir, settings, filter_file):
        """doc"""
        trace_graph = cls()
        os.chdir(trace_dir)
        trace_graph.filter_calls = path_utils.filter_calls(filter_file)
        path_utils.walktree(trace_dir, trace_graph.build_from_file)
        return trace_graph


    def build_from_file(self, filename):
        """doc"""
        # disable timing
        # self.timing_info = None
        for path in parsing.yield_paths(filename, self.timing_info, self.filter_calls):
            path[-1] = re.sub(r'_B:|_D:|_E:|_F:|_f:|_K:|_k:|_P:|_p:|_?:|_S:|_U:',':',path[-1])
            if path[-1] in self.filter_calls:
                continue
            if len(path) < 2:  # until now, no need keeping single call paths
                continue
            # keep a dict of stack depth of native calls
            for depth in range(len(path)):
                if path[-1 - depth].split(':')[1] == 'DVM':
                    break
            depth += 1
            # drop calls with no backtraces from stack_depth
            if  path[-2] != 'NO_BACKTRACE:NO_BACKTRACE':
                if depth > 128: 
                    depth = 128
                if depth not in self.stack_depth:
                    self.stack_depth[depth] = 1
                else:
                    self.stack_depth[depth] += 1
            # keep a list of all posix calls ordered ( callers prepended )
            # the following comment prevent any ppattern...
            # self.posix_calls_list.append(path[-2] + ':' + path[-1])
            # for each libc call, keep a "who called me" dict
            if path[-1] in self.posix_calls:
                if path[-2] in self.posix_calls[path[-1]]:
                    self.posix_calls[path[-1]][path[-2]] += 1
                else:
                    self.posix_calls[path[-1]][path[-2]] = 1
            else:
                self.posix_calls[path[-1]] = {}
                self.posix_calls[path[-1]][path[-2]] = 1

            # for each libc call, keep a "which lib called me" dict
            if path[-1] in self.posix_calls_per_lib:
                if path[-2].split(':')[1] in self.posix_calls_per_lib[path[-1]]:
                    self.posix_calls_per_lib[path[-1]][path[-2].split(':')[1]] += 1
                else:
                    self.posix_calls_per_lib[path[-1]][path[-2].split(':')[1]] = 1
            else:
                self.posix_calls_per_lib[path[-1]] = {}
                self.posix_calls_per_lib[path[-1]][path[-2].split(':')[1]] = 1

           # for each native library call, keep a "who I called" dict
            if path[-2] in self.native_calls:
                if path[-1] in self.native_calls[path[-2]]:
                    self.native_calls[path[-2]][path[-1]] += 1
                else:
                    self.native_calls[path[-2]][path[-1]] = 1
            else:
                self.native_calls[path[-2]] = {}
                self.native_calls[path[-2]][path[-1]] = 1

            # keep all full paths and occurencies
            if PATH_DELIMITER.join(path) in self.full_paths_dict:
                self.full_paths_dict[PATH_DELIMITER.join(path)] += 1
            else:
                self.full_paths_dict[PATH_DELIMITER.join(path)] = 1
            if len(path) == 1:
                self.add_node(*path)
                return
            # add edges
            for edge in zip(path, path[1:]):
#                if edge[0] == edge[1]:
#                    continue
                if self.has_edge(*edge):
                    self[edge[0]][edge[1]]['weight'] += 1
                else:
                    self.add_edge(*edge, weight=1)
