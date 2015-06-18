LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_STATIC_LIBRARIES := \
    libc

LOCAL_C_INCLUDES := \
    bionic/libc/bionic \
    system/core/init

LOCAL_CFLAGS := \
    -Wall \
    -DANDROID_TARGET=\"$(TARGET_BOARD_PLATFORM)\"

LOCAL_SRC_FILES := init_otter.c

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libinit_otter
include $(BUILD_STATIC_LIBRARY)
