#
# Makefile for Columbia systrace iOS wrapper library
# Copyright (C) 2013 Jeremy C. Andrus
#

#
# Configuration / Setup variables
#
#
TARGET = libsystem_kernel_wrapped

ABI_VERSION=1.0.0
ABI_COMPAT_VERSION=1.0.0

IOS_VER=7.0
DEVELOPER_IDENTITY ?= iPhone Developer

# This is always going to be an ARM-specific build :-)
ARCH_NAME = arm
ARCH_CFLAGS = -arch armv7

INCLUDES = arch/$(ARCH_NAME)/include

SRC = libsystem_kernel.S \
      wrap_lib.c

LDFLAGS = -ldl

# iOS frameworks to link with "-framework FOO"
FRAMEWORKS =

# iOS frameworks directories (relative to SDK)
FRAMEWORKS_PATHS = /System/Library/PrivateFrameworks

# explicitly exported symbols
# (others will be hidden)
#EXPORT_SYMBOLS=^_pthread_workqueue

#
# initial set of flags for the compiler
#
BASIC_FLAGS =

#
# Try not to edit below this line (it's automated stuff)
# ----------------------------------------------------------------------
#
#

# deal with newer XCode installation paths
DEVROOT := /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer
SDKPATH := SDKs/iPhoneOS$(IOS_VER).sdk
ifeq ($(wildcard $(DEVROOT)/$(SDKPATH)/SDKSettings.plist),)
  DEVROOT := /Developer/Platforms/iPhoneOS.platform/Developer
endif
ifeq ($(wildcard $(DEVROOT)/$(SDKPATH)/SDKSettings.plist),)
  $(error "You don't seem to have the iOS SDK installed in a normal place")
endif
SDKROOT := $(DEVROOT)/$(SDKPATH)

HEADERS = $(foreach dir,$(INCLUDES),\
	            $(shell find "$(dir)" -type f -name *.h | tr '\n' ' '))

BASIC_FLAGS += -isysroot $(SDKROOT) -Wall -Werror \
               -D_XOPEN_SOURCE=600 -D_BSD_SOURCE -D_DARWIN_C_SOURCE -D__APPLE__ \
               -I./ $(INCLUDES:%=-I%) \
               $(ARCH_CFLAGS)

OPTFLAGS_RELEASE = -g -O3 -DLINKER_DEBUG=0
OPTFLAGS_DEBUG   = -g -O0 -DLINKER_DEBUG=1 -DTRACE_BRIDGE_CALLS

# Linker-specific args...
BASIC_FLAGS += \
               -pipe \
               -miphoneos-version-min=$(IOS_VER)

CFLAGS = -std=gnu99

OBJC_FLAGS = -x objective-c \
             -fpascal-strings

CXXFLAGS = -x c++

CFLAGS_SHARED =
CFLAGS_TEST =

LDFLAGS += $(FRAMEWORKS_PATHS:%=-F$(SDKROOT)%)
LDFLAGS += -isysroot $(SDKROOT) $(ARCH_CFLAGS) $(FRAMEWORKS:%=-framework %)

LDFLAGS_SHARED = -dynamiclib -lSystem \
		 -compatibility_version $(ABI_COMPAT_VERSION) \
		 -current_version $(ABI_VERSION)

LDFLAGS_TEST =

#CC=$(DEVROOT)/usr/bin/gcc
CC=/usr/bin/gcc
STRIP=$(DEVROOT)/usr/bin/strip
NM=$(DEVROOT)/usr/bin/nm
CODESIGN=codesign

OBJDIR = obj
RELEASE_OBJDIR = $(OBJDIR)/release
DEBUG_OBJDIR = $(OBJDIR)/debug
TGT = $(TARGET).dylib

default: debug

%.S.o: CFLAGS += -D__ASSEMBLY__

debug: BASIC_FLAGS += $(OPTFLAGS_DEBUG) $(CFLAGS_SHARED)
debug: DEBUG_OBJ  = $(patsubst %.c,$(DEBUG_OBJDIR)/%.o,$(filter %.c, $(SRC)))
debug: DEBUG_OBJ += $(patsubst %.cpp,$(DEBUG_OBJDIR)/%.cxx.o,$(filter %.cpp, $(SRC)))
debug: DEBUG_OBJ += $(patsubst %.S,$(DEBUG_OBJDIR)/%.S.o,$(filter %.S, $(SRC)))
debug: DEBUG_OBJ += $(patsubst %.m,$(DEBUG_OBJDIR)/%.m.o,$(filter %.m, $(SRC)))
debug: $(OBJDIR)/$(TGT).DEBUG

release: BASIC_FLAGS += $(OPTFLAGS_RELEASE) $(CFLAGS_SHARED)
release: RELEASE_OBJ  = $(patsubst %.c,$(RELEASE_OBJDIR)/%.o,$(filter %.c, $(SRC)))
release: RELEASE_OBJ += $(patsubst %.cpp,$(RELEASE_OBJDIR)/%.cxx.o,$(filter %.cpp, $(SRC)))
release: RELEASE_OBJ += $(patsubst %.S,$(RELEASE_OBJDIR)/%.S.o,$(filter %.S, $(SRC)))
release: RELEASE_OBJ += $(patsubst %.m,$(RELEASE_OBJDIR)/%.m.o,$(filter %.m, $(SRC)))
release: $(OBJDIR)/$(TGT).RELEASE

# prevent make from deleting my objects
.SECONDARY: $(DEBUG_OBJ) $(RELEASE_OBJ)

%/.exists:
	@if [ ! -d "$*" ]; then mkdir -p "$*"; fi
	@touch "$*/.exists"

$(DEBUG_OBJDIR)/%.m.o $(RELEASE_OBJDIR)/%.m.o: %.m
	@echo "[OBJC] $<"
	@mkdir -p $(@D) > /dev/null
	@$(CC) $(BASIC_FLAGS) $(OBJC_FLAGS) -c -o $@ $<

$(DEBUG_OBJDIR)/%.S.o $(RELEASE_OBJDIR)/%.S.o: %.S
	@echo "[ASM ] $<"
	@mkdir -p $(@D) > /dev/null
	@$(CC) $(BASIC_FLAGS) $(CFLAGS) -c -o $@ $<

$(DEBUG_OBJDIR)/%.o $(RELEASE_OBJDIR)/%.o: %.c
	@echo "[CC  ] $<"
	@mkdir -p $(@D) > /dev/null
	@$(CC) $(BASIC_FLAGS) $(CFLAGS) -c -o $@ $<

$(DEBUG_OBJDIR)/%.cxx.o $(RELEASE_OBJDIR)/%.cxx.o: %.cpp
	@echo "[CXX ] $<"
	@mkdir -p $(@D) > /dev/null
	@$(CC) $(BASIC_FLAGS) $(CXXFLAGS) -c -o $@ $<

# second expansion here allows me to expand variables in the dependencies
# which would otherwise not be expanded properly
.SECONDEXPANSION:
$(OBJDIR)/$(TGT).%: $$($$*_OBJDIR)/.exists $$($$*_OBJ) Makefile
	@echo "[LINK][$*] $(TGT)"
	@$(CC) $(LDFLAGS) $(LDFLAGS_SHARED) -o $($*_OBJDIR)/$(TGT) $($*_OBJ)
	@if [ ! -z "$(EXPORT_SYMBOLS)" ]; then \
		echo "[STRIP] $($*_OBJDIR)/$(TGT)"; \
		$(NM) $($*_OBJDIR)/$(TGT) | cut -d ' ' -f 3 | \
			grep $(EXPORT_SYMBOLS) > $($*_OBJDIR)/$(TGT).syms; \
		$(STRIP) -arch all -s $($*_OBJDIR)/$(TGT).syms \
			 -u $($*_OBJDIR)/$(TGT) || rm $($*_OBJDIR)/$(TGT); \
	fi
	@echo "[SIGN] $($*_OBJDIR)/$(TGT) "
	@$(CODESIGN) -fv -s "$(DEVELOPER_IDENTITY)" $($*_OBJDIR)/$(TGT)
	@cp -f $($*_OBJDIR)/$(TGT) $@
	@cp -f $($*_OBJDIR)/$(TGT) $(TGT)

clean:
	@echo "[CLEAN]"
	@rm -rf "$(OBJDIR)"
	@rm -f *.syms

moreclean: clean
	@echo "[MORE CLEAN]"
	@rm -f $(TGT) 2>/dev/null || true

distclean: moreclean
	@echo "[DIST CLEAN]"
	@rm -f cscope.* tags

tags: $(SRC) $(HEADERS)
	@echo "[CTAGS]"
	@ctags -dt $(SRC) $(HEADERS)

cscope: tags
	@echo "[CSCOPE]"
	@cscope -b -R $(SRC) $(HEADERS)

.PHONY: clean moreclean distclean tags cscope

