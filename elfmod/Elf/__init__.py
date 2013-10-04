"""
Kenshoto's Elf parser

This package will let you use programatic ninja-fu
when trying to parse Elf binaries.  The API is based
around several objects representing constructs in the
Elf binary format.  The Elf object itself contains
parsed metadata and lists of things like section headers
and relocation entries.  Additionally, most of the
objects implement repr() in some form or another which
allows you a bunch of readelf-like functionality.

*Eventually* this API will allow you to modify Elf binaries
and spit them back out in working order (not complete, you
may notice some of the initial code).

Send bug reports to Invisigoth or Metr0.

"""
# Copyright (C) 2007 Invisigoth - See LICENSE file for details
import os
import sys
import struct
import traceback
import zlib

from stat import *
from Elf.elf_lookup import *
import vstruct
import vstruct.defs.elf as vs_elf

verbose = False

class ElfReloc:
    """
    Elf relocation entries consist mostly of "fixup" address which
    are taken care of by the loader at runtime.  Things like
    GOT entries, PLT jmp codes etc all have an Elf relocation
    entry.
    """

    def __init__(self, r_types):
        self.name = ""
        self.r_types = r_types

    def __repr__(self):
        return "%s %s <%s>" % (hex(self.r_offset),self.getName(),self.getTypeName())

    def setName(self, name):
        self.name = name

    def getName(self):
        return self.name

    def getType(self):
        return self.r_info & 0xff

    def getTypeName(self):
        return self.r_types.get(self.getType(),"")

class Elf32Reloc(ElfReloc, vs_elf.Elf32Reloc):
    def __init__(self, r_types):
        vs_elf.Elf32Reloc.__init__(self)
        ElfReloc.__init__(self, r_types)

    def getSymTabIndex(self):
        return self.r_info >> 8

class Elf32Reloca(ElfReloc, vs_elf.Elf32Reloca):
    def __init__(self, r_types):
        vs_elf.Elf32Reloca.__init__(self)
        ElfReloc.__init__(self, r_types)

    def getSymTabIndex(self):
        return self.r_info >> 8

class Elf64Reloc(ElfReloc, vs_elf.Elf64Reloc):
    def __init__(self, r_types):
        vs_elf.Elf64Reloc.__init__(self)
        ElfReloc.__init__(self, r_types)

    def getSymTabIndex(self):
        return self.r_info >> 32

class Elf64Reloca(ElfReloc, vs_elf.Elf64Reloca):
    def __init__(self, r_types):
        vs_elf.Elf64Reloca.__init__(self)
        ElfReloc.__init__(self, r_types)

    def getSymTabIndex(self):
        return self.r_info >> 32

class ElfDynamic:
    has_string = [DT_NEEDED,DT_SONAME]
    """
    An object to represent an Elf dynamic entry.
    (linker/loader directives)
    """

    def __init__(self, bytes=None):
        self.name = ""

    def __repr__(self):
        name = self.getName()
        if not name:
            name = hex(self.d_value)
        return "%s %s" % (name,self.getTypeName())

    def getName(self):
        return self.name

    def setName(self, name):
        self.name = name

    def getTypeName(self):
        return dt_types.get(self.d_tag,"Unknown: %s"%hex(self.d_tag))

class Elf32Dynamic(ElfDynamic, vs_elf.Elf32Dynamic):
    def __init__(self):
        vs_elf.Elf32Dynamic.__init__(self)
        ElfDynamic.__init__(self)

class Elf64Dynamic(ElfDynamic, vs_elf.Elf64Dynamic):
    def __init__(self):
        vs_elf.Elf64Dynamic.__init__(self)
        ElfDynamic.__init__(self)

class ElfSymbol:
    def __init__(self):
        self.name = ""

    def getInfoType(self):
        return self.st_info & 0xf

    def getInfoBind(self):
        return self.st_info >> 4

    def setStInfo(self, bind, typ):
        self.st_info &= 0
        self.st_info |= ((bind << 4) & 0xf0)
        self.st_info |= (typ & 0xf)

    def setStOther(self, val):
        self.st_other &= 0
        self.st_other |= (val & 0x3)

    def __cmp__(self, other):
        if self.st_value > other.st_value:
            return 1
        return -1

    def setName(self,name):
        self.name = name

    def getName(self):
        return self.name

    def __repr__(self):
        return "0x%.8x %d %s" % (self.st_value, self.st_size, self.name)

class Elf32Symbol(ElfSymbol, vs_elf.Elf32Symbol):
    def __init__(self):
        vs_elf.Elf32Symbol.__init__(self)
        ElfSymbol.__init__(self)

class Elf64Symbol(ElfSymbol, vs_elf.Elf64Symbol):
    def __init__(self):
        vs_elf.Elf64Symbol.__init__(self)
        ElfSymbol.__init__(self)

class ElfPheader:

    def __init__(self):
        pass

    def getTypeName(self):
        return ph_types.get(self.p_type, "Unknown")

    def __repr__(self):
        return '[%35s] VMA: 0x%.8x  offset: %8d  memsize: %8d  align: %8d  (filesz: %8d)  flags: %x' % (
            self.getTypeName(),
            self.p_vaddr,
            self.p_offset,
            self.p_memsz,
            self.p_align,
            self.p_filesz,
            self.p_flags)

class Elf32Pheader(ElfPheader, vs_elf.Elf32Pheader):
    def __init__(self):
        vs_elf.Elf32Pheader.__init__(self)
        ElfPheader.__init__(self)

class Elf64Pheader(ElfPheader, vs_elf.Elf64Pheader):
    def __init__(self):
        vs_elf.Elf64Pheader.__init__(self)
        ElfPheader.__init__(self)

class ElfSection:
    def __init__(self):
        self.name = ''

    def setName(self, name):
        self.name = name

    def getName(self):
        return self.name

    def __repr__(self):
        return 'Elf Section: [%20s] VMA: 0x%.8x  offset: %8d  ent/size: %8d/%8d  align: %8d' % (
                self.name,
                self.sh_addr,
                self.sh_offset,
                self.sh_entsize,
                self.sh_size,
                self.sh_addralign)
    
class Elf32Section(ElfSection, vs_elf.Elf32Section):
    def __init__(self):
        vs_elf.Elf32Section.__init__(self)
        ElfSection.__init__(self)

class Elf64Section(ElfSection, vs_elf.Elf64Section):
    def __init__(self):
        vs_elf.Elf64Section.__init__(self)
        ElfSection.__init__(self)

class Elf(vs_elf.Elf32, vs_elf.Elf64):

    def __init__(self, fd, inmem=False):

        # Grab a 32bit header to use to check for other
        # machine types...
        e = vs_elf.Elf32()
        fd.seek(0)
        bytes = fd.read(len(e))
        e.vsParse(bytes)
        if e.e_machine in e_machine_32:
            vs_elf.Elf32.__init__(self)
            self.bits = 32
            self.psize = 4
        elif e.e_machine in e_machine_64:
            vs_elf.Elf64.__init__(self)
            self.bits = 64
            self.psize = 8
        else:
            raise Exception('Unrecognized e_machine: %d' % e.e_machine)

        self.fd = fd

        bytes = self.readAtOffset(0, len(self))
        self.vsParse(bytes)

        if self.e_machine == EM_386:
            self.r_types = r_types_386
        elif self.e_machine == EM_X86_64:
            self.r_types = r_types_amd64
        else:
            self.r_types = {}

        self.pheaders = []
        self.sections = []
        self.secnames = {}
        self.symbols  = []
        self.relocs   = []
        self.symbols_by_name = {}
        self.symbols_by_addr = {}
        self.dynamics = []
        self.dynamic_symbols = []

        self._parsePheaders()
        self._parseSections()
        self._parseSymbols()
        self._parseDynamic()
        self._parseRelocs()

    def getRelocTypeName(self, rtype):
        '''
        Because relocation type names are decided based on the
        arch, only the Elf knows for sure...
        '''
        return self.r_types.get(rtype)

    def _parsePheaders(self):
        # Load up any program headers we find
        if self.e_phoff:
            pbase = self.e_phoff
            plen = self.e_phentsize
            for i in range(self.e_phnum):
                if self.bits == 32:
                    pgm = Elf32Pheader()
                elif self.bits == 64:
                    pgm = Elf64Pheader()
                else:
                    raise Exception('Platform not supported: %d' % (self.bits))

                bytes = self.readAtOffset(pbase, plen)
                pgm.vsParse(bytes)

                self.pheaders.append(pgm)
                pbase += plen

    def _parseSections(self):
        # Load up all the section headers
        if self.e_shoff:
            # Load up the sections
            sbase = self.e_shoff
            # FIXME this assumes static sized section headers
            slen = self.e_shentsize
            for i in range(self.e_shnum):
                if self.bits == 32:
                    sec = Elf32Section()
                elif self.bits == 64:
                    sec = Elf64Section()
                else:
                    raise Exception('Platform not supported: %d' % (self.bits))
                bytes = self.readAtOffset(sbase, slen)
                sec.vsParse(bytes)
                self.sections.append(sec)
                sbase += slen

            # Populate the section names
            strsec = self.sections[self.e_shstrndx]
            names = self.readAtOffset(strsec.sh_offset,strsec.sh_size)
            for sec in self.sections:
                name = names[sec.sh_name:].split("\x00")[0]
                if len(name) > 0:
                    sec.setName(name)
                    self.secnames[name] = sec

    def _parseSymbols(self):
        """
        Parse out the symbols that this elf binary has for us.
        """
        for sec in self.sections:
            if sec.sh_type == SHT_SYMTAB:
                symtab = self.readAtOffset(sec.sh_offset, sec.sh_size)
                while symtab:
                    if self.bits == 32:
                        newsym = Elf32Symbol()
                    elif self.bits == 64:
                        newsym = Elf64Symbol()
                    else:
                        raise Exception('Platform not supported: %d' % (self.bits))

                    newsym.vsParse(symtab)

                    if newsym.st_name:
                        name = self.getStrtabString(newsym.st_name, ".strtab")
                        newsym.setName(name)
                    self.addSymbol(newsym)
                    symtab = symtab[len(newsym):]

    def _parseDynamic(self):
        symtab = self.getSectionBytes('.dynsym')
        if symtab == None:
            return

        while symtab:
            if self.bits == 32:
                newsym = Elf32Symbol()
            elif self.bits == 64:
                newsym = Elf64Symbol()
            else:
                raise Exception('Platform not supported: %d' % (self.bits))
            newsym.vsParse(symtab)
            if newsym.st_name:
                name = self.getStrtabString(newsym.st_name, ".dynstr")
                newsym.setName(name)
            self.dynamic_symbols.append(newsym)
            symtab = symtab[len(newsym):]

        dynbytes = self.getSectionBytes('.dynamic')
        while dynbytes:
            if self.bits == 32:
                dyn = Elf32Dynamic()
            elif self.bits == 64:
                dyn = Elf64Dynamic()
            else:
                raise Exception('Platform not supported: %d' % (self.bits))
            dyn.vsParse(dynbytes)
            if dyn.d_tag in Elf32Dynamic.has_string:
                name = self.getStrtabString(dyn.d_value, ".dynstr")
                dyn.setName(name)

            self.dynamics.append(dyn)
            if dyn.d_tag == DT_NULL: # Represents the end
                break
            dynbytes = dynbytes[len(dyn):]

    def _parseRelocs(self):
        """
        Parse all the relocation entries out of any sections with
        sh_type == SHT_REL
        """
        for sec in self.sections:
            if sec.sh_type == SHT_REL:
                bytes = self.readAtOffset(sec.sh_offset, sec.sh_size)
                while bytes:
                    if self.bits == 32:
                        reloc = Elf32Reloc(self.r_types)
                    elif self.bits == 64:
                        reloc = Elf64Reloc(self.r_types)
                    else:
                        raise Exception('Platform not supported: %d' % (self.bits))
                    reloc.vsParse(bytes)
                    index = reloc.getSymTabIndex()
                    try:
                        sym = self.dynamic_symbols[index]
                        reloc.setName(sym.getName())
                    except:
                        traceback.print_exc()
                    self.relocs.append(reloc)
                    bytes = bytes[len(reloc):]

            elif sec.sh_type == SHT_RELA:
                bytes = self.readAtOffset(sec.sh_offset, sec.sh_size)
                while bytes:
                    if self.bits == 32:
                        reloc = Elf32Reloca(self.r_types)
                    elif self.bits == 64:
                        reloc = Elf64Reloca(self.r_types)
                    else:
                        raise Exception('Platform not supported: %d' % (self.bits))
                    reloc.vsParse(bytes)
                    index = reloc.getSymTabIndex()
                    try:
                        sym = self.dynamic_symbols[index]
                        reloc.setName(sym.getName())
                    except:
                        traceback.print_exc()
                    self.relocs.append(reloc)
                    bytes = bytes[len(reloc):]

    def getBaseAddress(self):
        """
        For prelinked and main-exe elf binaries, return the
        value for the loaded base address...
        """
        shrd = self.isSharedObject()
        plnk = self.isPreLinked()

        # If it's a shared object and *not* prelinked,
        # we need to select a base address for it
        # FIXME find non-coliding addr in workspace
        if shrd and not plnk:
            return 0x02000000

        # Find the best base address from the list of
        # section addresses...
        base = None
        for pgm in self.getPheaders():

            if pgm.p_vaddr == 0:
                continue

            if base == None:
                base = pgm.p_vaddr
                continue

            if pgm.p_vaddr < base:
                base = pgm.p_vaddr

        base &= 0xfffff000

        return base

    def writeDynamic(self):
        secsize = self.setFdAtSection('.dynsym')

        if self.bits == 32:
            sym = Elf32Symbol()
        elif self.bits == 64:
            sym = Elf64Symbol()
        else:
            raise Exception('Platform not supported: %d' % (self.bits))

        dsize = len(sym) * len(self.dynamic_symbols)
        if dsize != secsize:
            raise Exception("Can't write out symbol table of different size (%d != %d)" % (dsize, secsize))

        for sym in self.dynamic_symbols:
            symbytes = sym.vsEmit()
            self.fd.write(symbytes)

    def modStrtabString(self, offset, newstr, section=".strtab"):
        oldstr = self.getStrtabString(offset, section)
        if len(newstr) > len(oldstr):
            raise Exception("Can't replace %d byte string with %d bytes! "
                            "(must be equal or less than original)" % (len(oldstr), len(newstr)))
        self.setFdAtSection(section, offset)
        self.fd.write(newstr)
        return None

    def setSoname(self, name):
        for dyn in self.dynamics:
            if dyn.d_tag == DT_SONAME:
                self.modStrtabString(dyn.d_value, name, ".dynstr")
                break

    def readAtRva(self, rva, size):
        '''
        Calculate the file offset for the given RVA and
        read from it...
        '''
        return self.readAtOffset(self.rvaToOffset(rva), size)

    def rvaToOffset(self, rva):
        '''
        Convert an RVA for this ELF binary to a file offset.
        '''
        baseaddr = 0
        #if self.isPreLinked() or not self.isSharedObject():
        #if not self.isSharedObject():
            #print 'SUBTRACTING CALCULATED BASE'
            #baseaddr = self.getBaseAddress()

        for pgm in self.pheaders:
            if pgm.p_type != PT_LOAD:
                continue
            phrva = pgm.p_vaddr - baseaddr
            if rva < phrva:
                continue
            if rva >= phrva+pgm.p_memsz:
                continue
            print 'pgm',hex(pgm.p_vaddr),hex(phrva),hex(rva)
            # We are inside this pgrm header!
            rvaoff = rva - phrva
            return pgm.p_offset + rvaoff

        raise 'omg',hex(rva)
        return None

    def readAtOffset(self, off, size):
        '''
        Read from the given file offset.
        '''
        self.fd.seek(off)
        return self.fd.read(size)

    def getSection(self, secname):
        return self.secnames.get(secname,None)

    def getSections(self):
        """
        Return the array of sections for this Elf
        """
        return list(self.sections)

    def getSectionBytes(self, secname):
        sec = self.getSection(secname)
        if sec == None:
            return None
        return self.readAtOffset(sec.sh_offset, sec.sh_size)

    def setFdOffset(self, off):
        '''
        Position the file at the given offset
        '''
        self.fd.seek(off)
        return None

    def setFdAtSection(self, secname, offset=0):
        sec = self.getSection(secname)
        if sec == None:
            return 0
        self.setFdOffset(sec.sh_offset + offset)
        return sec.sh_size

    def getStrtabString(self, offset, section=".strtab"):
        sec = self.getSection(section)
        bytes = self.readAtOffset(sec.sh_offset, sec.sh_size)
        index = bytes.find("\x00", offset)
        return bytes[offset:index]

    def getDynamics(self):
        '''
        Return a list of the dynamics.
        '''
        return list(self.dynamics)

    def getDynSyms(self):
        '''
        Return a list of dynamic symbol objects.
        '''
        return self.dynamic_symbols

    def getRelocs(self):
        '''
        Get the list of relocations.
        '''
        return list(self.relocs)

    def isPreLinked(self):
        '''
        Returns True if the Elf binary is prelinked.
        '''
        for dyn in self.dynamics:
            #print repr(dyn)
            if dyn.d_tag == DT_GNU_PRELINKED:
                return True
            # FIXME check for exe vs .so
            if dyn.d_tag == DT_GNU_CONFLICTSZ:
                return True
        return False

    def isSharedObject(self):
        '''
        Returns true if the given Elf binary is a dynamically shared
        object.
        '''
        if self.e_type == ET_DYN:
            return True
        return False

    def __repr__(self, verbose=False):
        """  Returns a string summary of this ELF.  If (verbose) the summary will include Symbols, Relocs, Dynamics and Dynamic Symbol tables"""
        mystr = 'Elf Binary:'
        mystr+= "\n= Intimate Details:"
        mystr+= "\n==Magic:\t\t\t\t"       + self.e_ident
        mystr+= "\n==Type:\t\t\t\t\t"        + e_types.get(self.e_type)
        mystr+= "\n==Machine Arch:\t\t\t\t"  + e_machine_types.get(self.e_machine)
        mystr+= "\n==Version:\t\t\t\t%d"     % (self.e_version)
        mystr+= "\n==Entry:\t\t\t\t0x%.8x"      % (self.e_entry)
        mystr+= "\n==Program Headers(offset):\t\t%d (0x%x) bytes" % (self.e_phoff, self.e_phoff)
        mystr+= "\n==Section Headers(offset):\t\t%d (0x%x) bytes" % (self.e_shoff, self.e_shoff)
        mystr+= "\n==Flags:\t\t\t\t" + repr(self.e_flags) + " "
        mystr+= "\n==Elf Header Size:\t\t\t" + repr(self.e_ehsize) + " (" + hex(self.e_ehsize) + " bytes)"
        mystr+= "\n==Program Header Size:\t\t\t" + repr(self.e_phentsize) + " (" + hex(self.e_phentsize) + " bytes)"
        mystr+= "\n==Program Header Count:\t\t\t" + repr(self.e_phnum) + " (" + hex(self.e_phnum)+ ")"
        mystr+= "\n==Section Header Size:\t\t\t" + repr(self.e_shentsize) + " (" + hex(self.e_shentsize) + " bytes)"
        mystr+= "\n==Section Header Count:\t\t\t" + repr(self.e_shnum) + " (" + hex(self.e_shnum) + ")"
        mystr+= "\n==Section Header String Index\t\t" + repr(self.e_shstrndx) + " (" + hex(self.e_shstrndx) + " bytes)"

        mystr+= "\n\n= Sections:"
        for sec in self.sections:
            mystr+= "\n"+repr(sec)

        mystr+= "\n\n= Program Headers:"
        for ph in self.pheaders:
            mystr+= "\n"+repr(ph)

        return mystr

    def verbrepr(self):
        mystr = repr(self)

        mystr+= "\n\n= Symbols table:"
        for sym in self.symbols:
            mystr+= "\n"+repr(sym)

        mystr+= "\n\n= Relocation table:"
        for reloc in self.relocs:
            mystr+= "\n"+repr(reloc)

        mystr+= "\n\n= Dynamics table:"
        for dyn in self.dynamics:
            mystr+= "\n"+repr(dyn)

        mystr+= "\n\n= Dynamic Symbols table:"
        for dyn in self.dynamic_symbols:
            mystr+= "\n"+repr(dyn)

        return mystr
 
    def lookupSymbolName(self, name):
        """
        Lookup symbol entries in this elf binary by name.  The result is
        a long representing the address for the given symbol. Or None if
        it's not found.
        """
        return self.symbols_by_name.get(name, None)

    def lookupSymbolAddr(self, address):
        """
        lookup symbols from this elf binary by address.
        This returns the name for the given symbol or None for not found
        """
        return self.symbols_by_addr.get(address, None)

    def getPheaders(self):
        """
        Return a list of the program headers for this elf
        """
        return list(self.pheaders)

    def addSymbol(self, symbol):
        self.symbols.append(symbol)
        self.symbols_by_name[symbol.getName()] = symbol
        self.symbols_by_addr[symbol.st_value] = symbol

    def getSymbols(self):
        return self.symbols

def getRelocType(val):
    return val & 0xff

def getRelocSymTabIndex(val):
    return val >> 8

