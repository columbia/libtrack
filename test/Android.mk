
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS := -g3
LOCAL_CONLYFLAGS := -std=gnu99
LOCAL_CPPFLAGS := -std=c++0x
LOCAL_SRC_FILES := main.c
LOCAL_MODULE:= argtest

include $(BUILD_EXECUTABLE)
