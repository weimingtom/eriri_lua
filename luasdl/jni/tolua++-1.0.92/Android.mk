LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := tolua

LOCAL_C_INCLUDES := $(LOCAL_PATH) $(LOCAL_PATH)/include $(LOCAL_PATH)/src/lib

LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)

LOCAL_CPP_EXTENSION := .cpp

LOCAL_SRC_FILES += src/lib/tolua_event.c
LOCAL_SRC_FILES += src/lib/tolua_is.c
LOCAL_SRC_FILES += src/lib/tolua_map.c
LOCAL_SRC_FILES += src/lib/tolua_push.c
LOCAL_SRC_FILES += src/lib/tolua_to.c

LOCAL_STATIC_LIBRARIES := lua

#LOCAL_SHARED_LIBRARIES := sdl

#LOCAL_LDLIBS := -lz

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
