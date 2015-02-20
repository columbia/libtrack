#!/bin/bash

export CROSS_COMPILE=arm-linux-androideabi-
export IDIR=/system/lib

ADB=$(shell which adb)
RESET_LIBS="/system/bin/reset_libs.sh"

ifeq ($(OUT),)
OUT=wrapped
endif

ifeq ($(LIB),)
LIB=droid
endif

all: init_wrappers install_wrappers

init_wrappers:
	@echo "Hidding symbols and initializing static lookup  table."
	./wraplib.sh --use-ndk --out $(OUT) --lib $(LIB) --type elf --arch arm \
		--wrap-all

install_wrappers: init_wrappers
	@echo "Installing Wrappers"
	@echo "Reboot in recovery mode"
	@$(ADB) reboot recovery

	@echo "Wait 40 seconds before mounting system"
	@sleep 40
	@$(ADB) shell mount -o rw -t ext4 /dev/block/mmcblk0p3 /system
	@for lib in `/bin/ls ./$(LIB)`; do\
		cd ./$(OUT)/$$lib/jni;\
		make;\
		make install;\
		cd ../../..;\
	done;
	@$(ADB) reboot

clean:
	rm -rf $(OUT)

reset_libs:
	@echo "Reboot in recovery mode"
	@$(ADB) reboot recovery
	@sleep 40
	@$(ADB) shell mount -o rw -t ext4 /dev/block/mmcblk0p3 /system
	@echo "Wait 40 seconds before mounting system"
	$(ADB) shell $(RESET_LIBS)
	@$(ADB) reboot
