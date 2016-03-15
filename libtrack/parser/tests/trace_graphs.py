"""
Moldule documenatation
goes here
"""

import unittest
from telesphorus import trace_graphs
from telesphorus import abstractions
from telesphorus.helpers import stats

CONFIG_FILE_PATH = "/etc/telesphorus/main.conf"


class FullTraceGraphTest(unittest.TestCase):
    """doc goes here"""

    def setUp(self):
        self.trace_dir = \
            "/home/vatlidak/Repos/telesphorus/LOGS/TEST_WITH_FULL_TRACES/"

    def test_posix_invocations_num(self):
        test_graph = trace_graphs.TraceGraph.parse_traces(self.trace_dir)
        self.assertEqual(stats.posix_invocations(test_graph), 12)

    def test_average_full_path_len(self):
        test_graph = trace_graphs.TraceGraph.parse_traces(self.trace_dir)
        self.assertEqual(int(stats.average_full_path_len(test_graph)), 2)

    # this is broken
    # will be fixed when I decide how to split native,  posix, and dvm.
    #def test_posix_invocations(self):
    #    self.assertEqual(stats.posix_invocations(self.test_graph), 15)

    def test_full_paths(self):
        test_graph = trace_graphs.TraceGraph.parse_traces(self.trace_dir)
        correct_paths = [
            '1native_c:libutils.so->1native_b:libutils.so->1native_a:libc.so',
            '2native_e:\n->2native_d:libdvm.so->2native_c:libutils.so->2nati'
            've_b:libutils.so->2native_a:libc.so',
            '3native_a:libdvm.so->3native_b:libdvm'
            '.so->3native_c:libdvm.so->3native_d:libc.so',
            '4java_b:DVM->4java_a:DVM', '5native_a:libandroidfw'
            '.so->5native_b:libutils.so->5native_c:libc.so',
            '4java_b:DVM->4java_a:DVM',
            '6native_a:libdvm.so->6native_b:libdvm.so->6native_c:libc.so',
            '7java_a:DVM->7java_b:DVM',
            '6native_a:libdvm.so->6native_b:libdvm.so->6native_c:libc.so',
            '7java_a:DVM->7java_b:DVM',
            '8native_a:libdvm.so->8native_b:libdvm.so->8native_c:'
            'libdvm.so->8native_d:libc.so',
            '7java_a:DVM->7java_b:DVM', '']
        self.assertEqual(test_graph.full_paths_list, correct_paths)


class WithoutDalvikTraceGraphTest(unittest.TestCase):
    """doc goes  here"""

    def setUp(self):
        self.trace_dir = \
            "/home/vatlidak/Repos/telesphorus/LOGS/TEST_WITHOUT_DVM_TRACES/"

    def test_posix_invocations(self):
        test_graph = trace_graphs.TraceGraph.parse_traces(self.trace_dir)
        self.assertEqual(stats.posix_invocations(test_graph), 8)

    def test_average_full_path_len(self):
        test_graph = trace_graphs.TraceGraph.parse_traces(self.trace_dir)
        self.assertEqual(int(stats.average_full_path_len(test_graph)), 6)

    def test_full_paths(self):
        test_graph = trace_graphs.TraceGraph.parse_traces(self.trace_dir)
        correct_paths = ['__libc_init:libc.so->__libc_init:_ibc_so->??'
                         ':/system/bin/servicemanager->??:/system/bin/'
                         'servicemanager->??:/system/bin/'
                         'servicemanager->??:/system/bin/servicemanager'
                         '->??:/system/bin/servicemanager'
                         '->ioctl:libc.so', '__libc_init:libc.so->__libc_init'
                         ':_ibc_so->??:/system/bin/'
                         'servicemanager->??:/system/bin/servicemanager->'
                         'ioctl:libc.so',
                         '__libc_init:libc.so->__libc_init:_ibc_so->??:'
                         '/system/bin/servicemanager->??:'
                         '/system/bin/servicemanager->??:/system/bin/'
                         'servicemanager->??:/system/bin/'
                         'servicemanager->??:/system/bin/servicemanager'
                         '->ioctl:libc.so',
                         '__libc_init:libc.so->__libc_init:_ibc_so->??:'
                         '/system/bin/servicemanager->??:/'
                         'system/bin/servicemanager->??:'
                         '/system/bin/servicemanager->'
                         '??:/system/bin/servicemanager'
                         '->??:/system/bin/servicemanager->ioctl:libc.so',
                         '__libc_init:libc.so->__libc_init:_ibc_so->??:'
                         '/system/bin/servicemanager->??:/system/bin/'
                         'servicemanager->ioctl:libc.so',
                         '__libc_init:libc.so->__libc_init:_ibc_so->??:/'
                         'system/bin/servicemanager->??:/system/bin/'
                         'servicemanager->??:/system/bin/servicemanager->??'
                         ':/system/bin/servicemanager->??:/system/'
                         'bin/servicemanager->ioctl:libc.so',
                         '__libc_init:libc.so->__libc_init:_ibc_so->??'
                         ':/system/bin/servicemanager->??:/system/bin/'
                         'servicemanager->??:/system/bin/servicemanager->'
                         '??:/system/bin/servicemanager->??:/system/'
                         'bin/servicemanager->ioctl:libc.so',
                         '__libc_init:libc.so->__libc_init:_ibc_so->??:'
                         '/system/bin/servicemanager->??:/system/bin/'
                         'servicemanager->ioctl:libc.so', '']
        self.assertEqual(test_graph.full_paths_list, correct_paths)


class BrokenTraceGraphTest(unittest.TestCase):
    """doc goes here"""

    def setUp(self):
        self.trace_dir = \
            "/home/vatlidak/Repos/telesphorus/LOGS/TEST_WITH_BROKEN_TRACES/"

    def test_posix_invocations(self):
        test_graph = trace_graphs.TraceGraph.parse_traces(self.trace_dir)
        self.assertEqual(stats.posix_invocations(test_graph), 1)

    def test_average_full_path_len(self):
        test_graph = trace_graphs.TraceGraph.parse_traces(self.trace_dir)
        self.assertEqual(int(stats.average_full_path_len(test_graph)), 3)

    def test_full_paths(self):
        test_graph = trace_graphs.TraceGraph.parse_traces(self.trace_dir)
        correct_paths = ['1native_c:libutils.so->1native_b:libutils.so'
                         '->1native_a:libc.so', '']
        self.assertEqual(test_graph.full_paths_list, correct_paths)


#class AbstarctionsTest(unittest.TestCase):
#    def setUp(self):
#        self.test_graph = trace_graphs.TraceGraph.parse_traces(TRACEDIR)
#
#    def test_hidden_abstraction(self):
#        pass
#
#    def test_obsolete_abstraction(self):
#        pass
#
#    def test_missing_abstraction(self):
#        pass


if __name__ == '__main__':
    unittest.main()
