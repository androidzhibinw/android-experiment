LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := setscheduler.c
LOCAL_MODULE := setscheduler

include $(BUILD_EXECUTABLE)

