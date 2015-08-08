PLAT := arm-linux-androideabi-

CC := $(PLAT)gcc 
CPP := $(PLAT)g++
LD := $(PLAT)ld
AR := $(PLAT)ar rcu 
RANLIB := $(PLAT)ranlib
STRIP := $(PLAT)strip
RM := rm -f

CFLAGS := -DANDROID
CFLAGS += -O2 
CFLAGS += -Wall -Wstrict-prototypes 
CFLAGS += -I./include
CFLAGS += -DSDL_JAVA_PACKAGE_PATH=jp_ogapee_onscripter
CFLAGS += -DSDL_CURDIR_PATH=\"/sdcard/ons\"
CFLAGS += -DSDL_TRACKBALL_KEYUP_DELAY=1

LDFLAGS += -lc -lm -lGLESv1_CM -ldl -llog

OBJECTS := 

OBJECTS += src/SDL.o src/SDL_assert.o src/SDL_compat.o
OBJECTS += src/SDL_error.o src/SDL_fatal.o

OBJECTS += src/audio/SDL_audio.o src/audio/SDL_audiocvt.o
OBJECTS += src/audio/SDL_audiodev.o src/audio/SDL_audiotypecvt.o
OBJECTS += src/audio/SDL_mixer.o src/audio/SDL_mixer_m68k.o
OBJECTS += src/audio/SDL_mixer_MMX.o src/audio/SDL_mixer_MMX_VC.o
OBJECTS += src/audio/SDL_wave.o
OBJECTS += src/audio/android/SDL_androidaudio.o

OBJECTS += src/cpuinfo/SDL_cpuinfo.o

OBJECTS += src/events/SDL_events.o src/events/SDL_keyboard.o
OBJECTS += src/events/SDL_mouse.o src/events/SDL_quit.o
OBJECTS += src/events/SDL_windowevents.o

OBJECTS += src/file/SDL_rwops.o

OBJECTS += src/haptic/SDL_haptic.o
OBJECTS += src/haptic/dummy/SDL_syshaptic.o

OBJECTS += src/joystick/SDL_joystick.o
OBJECTS += src/joystick/dummy/SDL_sysjoystick.o

OBJECTS += src/stdlib/SDL_getenv.o
OBJECTS += src/stdlib/SDL_iconv.o src/stdlib/SDL_malloc.o
OBJECTS += src/stdlib/SDL_qsort.o src/stdlib/SDL_stdlib.o
OBJECTS += src/stdlib/SDL_string.o

OBJECTS += src/thread/SDL_thread.o
OBJECTS += src/thread/pthread/SDL_syscond.o
OBJECTS += src/thread/pthread/SDL_sysmutex.o
OBJECTS += src/thread/pthread/SDL_syssem.o
OBJECTS += src/thread/pthread/SDL_systhread.o

OBJECTS += src/timer/SDL_timer.o
OBJECTS += src/timer/unix/SDL_systimer.o

OBJECTS += src/video/SDL_alphamult.o src/video/SDL_blendfillrect.o
OBJECTS += src/video/SDL_blendline.o src/video/SDL_blendpoint.o
OBJECTS += src/video/SDL_blendrect.o src/video/SDL_blit.o
OBJECTS += src/video/SDL_blit_0.o src/video/SDL_blit_1.o
OBJECTS += src/video/SDL_blit_A.o src/video/SDL_blit_auto.o
OBJECTS += src/video/SDL_blit_copy.o src/video/SDL_blit_N.o
OBJECTS += src/video/SDL_blit_slow.o src/video/SDL_bmp.o
OBJECTS += src/video/SDL_drawline.o src/video/SDL_drawpoint.o
OBJECTS += src/video/SDL_drawrect.o src/video/SDL_fillrect.o
OBJECTS += src/video/SDL_gamma.o src/video/SDL_pixels.o
OBJECTS += src/video/SDL_rect.o src/video/SDL_renderer_gl.o
OBJECTS += src/video/SDL_renderer_gles.o src/video/SDL_renderer_sw.o
OBJECTS += src/video/SDL_RLEaccel.o src/video/SDL_stretch.o
OBJECTS += src/video/SDL_surface.o src/video/SDL_video.o
OBJECTS += src/video/SDL_yuv_mmx.o src/video/SDL_yuv_sw.o
OBJECTS += src/video/android/SDL_androidinput.o
OBJECTS += src/video/android/SDL_androidvideo.o

# OBJECTS += src/main/

OBJECTS += src/power/SDL_power.o

OBJECTS += src/loadso/dlopen/SDL_sysloadso.o

OBJECTS += src/atomic/dummy/SDL_atomic.o

all : libSDL.a libgraywin.so

libgraywin.so : libSDL.a
	$(CC) -shared $(CFLAGS) -o $@ sdl_main.c graywin.c libSDL.a $(LDFLAGS)
	
libSDL.a : $(OBJECTS)
	$(AR) $@ $(OBJECTS) 
	$(RANLIB) $@
	
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<
	
clean :
	$(RM) $(OBJECTS) *.a *.so
