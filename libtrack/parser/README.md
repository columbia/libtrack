Telesphorus 
****

Description
===========

In Greek mythology, Telesphorus (or Telesphoros) was the demi-god of convalescence, who "brought to fulfillment" recuperation from illness or injury.
In our case Telesphorus is a software to parse modern OS trace logs and store them into graphs in order to plot them and gain
an analytic perspective on how system calls of modern mobile and desktop OSes interact. We would like to identify common access patterns among system calls,
and recuperate from missing abstractions. 


Installation and maintenance
============================

installing the package:

$sudo python install setup.py

Place your log files and your configuration file in the directory /etc/telesphorus/

$cp conf/main.conf /etc/telesphorus/main.conf

and execute:

$telesphorus


Testing
==================
Run all tests using  the local source files and not the installed:

vatlidak@vaggpc:~/Repos/telesphorus(master)> sudo python setup.py test


or run single test using the installed package:

python trace_graphs.py FullTraceGraphTest


Authors
=======

  *  Vaggelis Atlidakis <vatlidak@cs.columbia.edu>

License
=======

See LICENSE
