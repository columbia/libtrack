#!/usr/bin/python
#

"""
Elf modification tool
Copyright (C) 2013 Jeremy C. Andrus

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Based on Kenshoto's Elf parser

"""

import os
import sys
import argparse
from Elf import Elf
from Elf.elf_lookup import *

PROGRAM="elfmod"
VERSION="0.1a"

def hidesyms(args):
    #print "Loading", args.elf
    elf = Elf(file(args.elf, "r+b"))
    #print "Loading symbols from", args.syms
    with open(args.syms) as sf:
        hidden_syms = sf.read().splitlines()
    #print elf
    for dsym in elf.getDynSyms():
        if dsym.name in hidden_syms:
            print 'SYM(0x%x,%s)' % (dsym.st_value, dsym.name)
            dsym.setStInfo(STB_LOCAL, dsym.getInfoType())
            dsym.setStOther(STV_HIDDEN)
    elf.writeDynamic()

def soname(args):
    print "\tSetting soname to '%s' in %s" % (args.name, args.elf)
    elf = Elf(file(args.elf, "r+b"))
    elf.setSoname(args.name)

parser = argparse.ArgumentParser(prog=PROGRAM, description="Modify an ELF library in-place")
subparsers = parser.add_subparsers(title='Mode', help='ELF modification mode')

# The "hidesyms" command
parser_hs = subparsers.add_parser('hidesyms', help="Hide ELF symbols by re-writing the .dynsym table in-place")
parser_hs.add_argument('elf', help="Path to ELF shared-object file")
parser_hs.add_argument('syms', help="File containing symbols to hide (one per line)")
parser_hs.set_defaults(func=hidesyms)

# The "soname" command
parser_sonm = subparsers.add_parser('soname', help="Modify the ELF soname")
parser_sonm.add_argument('elf', help="Path to ELF shared-object file")
parser_sonm.add_argument('name', help="New SONAME (length must be less than or equal to original length)")
parser_sonm.set_defaults(func=soname)

args = parser.parse_args()
args.func(args)
