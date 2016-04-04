LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := lockotron
LOCAL_SRC_FILES := lockotron.c
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_SRC_FILES += asm/arm7/statistics.s
else
    LOCAL_SRC_FILES += src/statistics.c
endif
