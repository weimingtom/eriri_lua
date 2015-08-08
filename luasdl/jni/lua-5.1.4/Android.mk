LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := lua

LOCAL_C_INCLUDES := $(LOCAL_PATH) $(LOCAL_PATH)/src

LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)

LOCAL_CPP_EXTENSION := .cpp

LOCAL_SRC_FILES += src/lapi.c
LOCAL_SRC_FILES += src/lauxlib.c
LOCAL_SRC_FILES += src/lbaselib.c
LOCAL_SRC_FILES += src/lcode.c
LOCAL_SRC_FILES += src/ldblib.c
LOCAL_SRC_FILES += src/ldebug.c
LOCAL_SRC_FILES += src/ldo.c
LOCAL_SRC_FILES += src/ldump.c
LOCAL_SRC_FILES += src/lfunc.c
LOCAL_SRC_FILES += src/lgc.c
LOCAL_SRC_FILES += src/linit.c
LOCAL_SRC_FILES += src/liolib.c
LOCAL_SRC_FILES += src/llex.c
LOCAL_SRC_FILES += src/lmathlib.c
LOCAL_SRC_FILES += src/lmem.c
LOCAL_SRC_FILES += src/loadlib.c
LOCAL_SRC_FILES += src/lobject.c
LOCAL_SRC_FILES += src/lopcodes.c
LOCAL_SRC_FILES += src/loslib.c
LOCAL_SRC_FILES += src/lparser.c
LOCAL_SRC_FILES += src/lstate.c
LOCAL_SRC_FILES += src/lstring.c
LOCAL_SRC_FILES += src/lstrlib.c
LOCAL_SRC_FILES += src/ltable.c
LOCAL_SRC_FILES += src/ltablib.c
LOCAL_SRC_FILES += src/ltm.c
LOCAL_SRC_FILES += src/lundump.c
LOCAL_SRC_FILES += src/lvm.c
LOCAL_SRC_FILES += src/lzio.c
LOCAL_SRC_FILES += src/print.c

LOCAL_STATIC_LIBRARIES :=

#LOCAL_SHARED_LIBRARIES := sdl

#LOCAL_LDLIBS := -lz

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/src

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
