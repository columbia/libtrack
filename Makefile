#!/bin/bash

export CROSS_COMPILE=arm-linux-androideabi-
export IDIR=/system/lib
ADB=$(shell which adb)
ifeq ($(OUT),)
OUT=wrapped
endif

ifeq ($(LIB),)
LIB=droid/libc.so
endif

all: init_wrapper build_wrapper install_wraper

init_wrapper:
	@echo "Hidding symbols and initializing static lookup  table."
	./wraplib.sh --use-ndk --out $(OUT) --lib $(LIB) --type elf --arch arm



build_wrapper: init_wrapper
	@echo "Building wrapper"
	@cd ./$(OUT)/$(LIB)/jni/ && \
		make

install_wraper: build_wrapper
	@echo "Installing Wrapper"
	@echo "Reboot in recovery mode"
	@$(ADB) reboot recovery
	@echo "Wait 40sec before mounting system"
	@sleep 30
	@$(ADB) shell mount -o rw -t ext4 /dev/block/mmcblk0p3 /system
	@cd ./$(OUT)/$(LIB)/jni/ && \
		make install
	@$(ADB) reboot system

clean:
	rm -rf $(OUT)
