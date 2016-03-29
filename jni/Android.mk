LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := TestJni
LOCAL_SRC_FILES := com_testjni_test_Student.c
LOCAL_LDLIBS:=-L$(SYSROOT)/usr/lib -llog

include $(BUILD_SHARED_LIBRARY)
