LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := sdl

# The namespace in Java file, with dots replaced with underscores
SDL_JAVA_PACKAGE_PATH := jp_ogapee_onscripter

# Path to files with application data - they should be downloaded from Internet on first app run inside
# Java sources, or unpacked from resources (TODO)
# Typically /sdcard/alienblaster 
# Or /data/data/de.schwardtnet.alienblaster/files if you're planning to unpack data in application private folder
# Your application will just set current directory there
SDL_CURDIR_PATH := /sdcard/ons

# Android Dev Phone G1 has trackball instead of cursor keys, and 
# sends trackball movement events as rapid KeyDown/KeyUp events,
# this will make Up/Down/Left/Right key up events with X frames delay,
# so if application expects you to press and hold button it will process the event correctly.
# TODO: create a libsdl config file for that option and for key mapping/on-screen keyboard
SDL_TRACKBALL_KEYUP_DELAY := 1

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_CFLAGS := 
LOCAL_CFLAGS += -DSDL_JAVA_PACKAGE_PATH=$(SDL_JAVA_PACKAGE_PATH)
LOCAL_CFLAGS += -DSDL_CURDIR_PATH=\"$(SDL_CURDIR_PATH)\"
LOCAL_CFLAGS += -DSDL_TRACKBALL_KEYUP_DELAY=$(SDL_TRACKBALL_KEYUP_DELAY)
LOCAL_EXPORT_CFLAGS := -DSDL_JAVA_PACKAGE_PATH=$(SDL_JAVA_PACKAGE_PATH)

LOCAL_CPP_EXTENSION := .cpp

LOCAL_SRC_FILES := 
LOCAL_SRC_FILES += src/SDL.c src/SDL_assert.c src/SDL_compat.c
LOCAL_SRC_FILES += src/SDL_error.c src/SDL_fatal.c

LOCAL_SRC_FILES += src/audio/SDL_audio.c src/audio/SDL_audiocvt.c
LOCAL_SRC_FILES += src/audio/SDL_audiodev.c src/audio/SDL_audiotypecvt.c
LOCAL_SRC_FILES += src/audio/SDL_mixer.c src/audio/SDL_mixer_m68k.c
LOCAL_SRC_FILES += src/audio/SDL_mixer_MMX.c src/audio/SDL_mixer_MMX_VC.c
LOCAL_SRC_FILES += src/audio/SDL_wave.c
LOCAL_SRC_FILES += src/audio/android/SDL_androidaudio.c

LOCAL_SRC_FILES += src/cpuinfo/SDL_cpuinfo.c

LOCAL_SRC_FILES += src/events/SDL_events.c src/events/SDL_keyboard.c
LOCAL_SRC_FILES += src/events/SDL_mouse.c src/events/SDL_quit.c
LOCAL_SRC_FILES += src/events/SDL_windowevents.c

LOCAL_SRC_FILES += src/file/SDL_rwops.c

LOCAL_SRC_FILES += src/haptic/SDL_haptic.c
LOCAL_SRC_FILES += src/haptic/dummy/SDL_syshaptic.c

LOCAL_SRC_FILES += src/joystick/SDL_joystick.c
LOCAL_SRC_FILES += src/joystick/dummy/SDL_sysjoystick.c

LOCAL_SRC_FILES += src/stdlib/SDL_getenv.c
LOCAL_SRC_FILES += src/stdlib/SDL_iconv.c src/stdlib/SDL_malloc.c
LOCAL_SRC_FILES += src/stdlib/SDL_qsort.c src/stdlib/SDL_stdlib.c
LOCAL_SRC_FILES += src/stdlib/SDL_string.c

LOCAL_SRC_FILES += src/thread/SDL_thread.c
LOCAL_SRC_FILES += src/thread/pthread/SDL_syscond.c
LOCAL_SRC_FILES += src/thread/pthread/SDL_sysmutex.c
LOCAL_SRC_FILES += src/thread/pthread/SDL_syssem.c
LOCAL_SRC_FILES += src/thread/pthread/SDL_systhread.c

LOCAL_SRC_FILES += src/timer/SDL_timer.c
LOCAL_SRC_FILES += src/timer/unix/SDL_systimer.c

LOCAL_SRC_FILES += src/video/SDL_alphamult.c src/video/SDL_blendfillrect.c
LOCAL_SRC_FILES += src/video/SDL_blendline.c src/video/SDL_blendpoint.c
LOCAL_SRC_FILES += src/video/SDL_blendrect.c src/video/SDL_blit.c
LOCAL_SRC_FILES += src/video/SDL_blit_0.c src/video/SDL_blit_1.c
LOCAL_SRC_FILES += src/video/SDL_blit_A.c src/video/SDL_blit_auto.c
LOCAL_SRC_FILES += src/video/SDL_blit_copy.c src/video/SDL_blit_N.c
LOCAL_SRC_FILES += src/video/SDL_blit_slow.c src/video/SDL_bmp.c
LOCAL_SRC_FILES += src/video/SDL_drawline.c src/video/SDL_drawpoint.c
LOCAL_SRC_FILES += src/video/SDL_drawrect.c src/video/SDL_fillrect.c
LOCAL_SRC_FILES += src/video/SDL_gamma.c src/video/SDL_pixels.c
LOCAL_SRC_FILES += src/video/SDL_rect.c src/video/SDL_renderer_gl.c
LOCAL_SRC_FILES += src/video/SDL_renderer_gles.c src/video/SDL_renderer_sw.c
LOCAL_SRC_FILES += src/video/SDL_RLEaccel.c src/video/SDL_stretch.c
LOCAL_SRC_FILES += src/video/SDL_surface.c src/video/SDL_video.c
LOCAL_SRC_FILES += src/video/SDL_yuv_mmx.c src/video/SDL_yuv_sw.c
LOCAL_SRC_FILES += src/video/android/SDL_androidinput.c
LOCAL_SRC_FILES += src/video/android/SDL_androidvideo.c

# LOCAL_SRC_FILES += src/main/

LOCAL_SRC_FILES += src/power/SDL_power.c

LOCAL_SRC_FILES += src/loadso/dlopen/SDL_sysloadso.c

LOCAL_SRC_FILES += src/atomic/dummy/SDL_atomic.c

LOCAL_LDLIBS := -lGLESv1_CM -llog
LOCAL_EXPORT_LDLIBS := -lGLESv1_CM -llog
# -lGLESv1_CM -ldl -llog -lz

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
