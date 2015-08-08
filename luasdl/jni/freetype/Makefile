include ../config.mk

CC = gcc
CPP = g++
AR	= ar
RANLIB	= ranlib

CFLAGS := -g -O2 
CFLAGS += -DFT_CONFIG_CONFIG_H="<ftconfig.h>" 
CFLAGS += -DFT2_BUILD_LIBRARY 
CFLAGS += -DFT_CONFIG_MODULES_H="<ftmodule.h>"
CFLAGS += -I./objs -I./builds/unix -I./include
CPPFLAGS  = $(CFLAGS)

TARGET := libfreetype.a

OBJECTS := 
OBJECTS += src/base/ftsystem.o src/base/ftdebug.o src/base/ftinit.o
OBJECTS += src/base/ftbase.o src/base/ftbbox.o src/base/ftbdf.o
OBJECTS += src/base/ftbitmap.o src/base/ftcid.o src/base/ftfstype.o
OBJECTS += src/base/ftgasp.o src/base/ftglyph.o src/base/ftgxval.o
OBJECTS += src/base/ftlcdfil.o src/base/ftmm.o src/base/ftotval.o
OBJECTS += src/base/ftpatent.o src/base/ftpfr.o src/base/ftstroke.o
OBJECTS += src/base/ftsynth.o src/base/fttype1.o src/base/ftwinfnt.o
OBJECTS += src/base/ftxf86.o 

OBJECTS += src/truetype/truetype.o
OBJECTS += src/type1/type1.o
OBJECTS += src/cff/cff.o
OBJECTS += src/cid/type1cid.o
OBJECTS += src/pfr/pfr.o
OBJECTS += src/type42/type42.o
OBJECTS += src/winfonts/winfnt.o
OBJECTS += src/pcf/pcf.o
OBJECTS += src/bdf/bdf.o
OBJECTS += src/sfnt/sfnt.o
OBJECTS += src/autofit/autofit.o
OBJECTS += src/pshinter/pshinter.o
OBJECTS += src/raster/raster.o
OBJECTS += src/smooth/smooth.o
OBJECTS += src/cache/ftcache.o
OBJECTS += src/gzip/ftgzip.o
OBJECTS += src/lzw/ftlzw.o
OBJECTS += src/psaux/psaux.o
OBJECTS += src/psnames/psmodule.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) cr $@ $^
	$(RANLIB) $@

clean:
	rm -f $(TARGET) $(OBJECTS)
