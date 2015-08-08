LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := luasdl

LOCAL_C_INCLUDES := 
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../sdl/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../sdl_image
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../sdl_mixer
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../sdl_ttf
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../lua-5.1.4/src
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../tolua++-1.0.92/include
LOCAL_C_INCLUDES += $(LOCAL_PATH) $(LOCAL_PATH)/src $(LOCAL_PATH)/src/autogen

LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)

LOCAL_CPP_EXTENSION := .cpp

LOCAL_SRC_FILES += src/DejaVu-Sans-Mono-13.c
LOCAL_SRC_FILES += src/sdllib.c
LOCAL_SRC_FILES += src/autogen/SDL_bind.c

LOCAL_STATIC_LIBRARIES := tolua lua

#LOCAL_SHARED_LIBRARIES := sdl

#LOCAL_LDLIBS := -lz

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/src

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
