####################################################
# Plugin Infomation
####################################################

PLUGIN_NAME = myplugin

####################################################
# Plugin files and directories
####################################################

CC = gcc
CLINK = gcc
HL2SDK_DIR = /root/hl2sdk-csgo
SRCDS_DIR = /home/steam/steamcmd/csgods

####################################################
# Plugin Flags
####################################################

ARCH_CFLAGS = -mtune=i486 -march=pentium3 -mmmx -msse
BASE_CFLAGS = -D_LINUX -DPOSIX -DCOMPILER_GCC \
-Dstricmp=strcasecmp -D_stricmp=strcasecmp -D_strnicmp=strncasecmp -Dstrnicmp=strncasecmp \
-D_snprintf=snprintf -D_vsnprintf=vsnprintf -D_alloca=alloca -Dstrcmpi=strcasecmp -Wall -Werror \
-Wno-overloaded-virtual -Wno-switch -Wno-unused -Wno-non-virtual-dtor -fno-exceptions -fno-rtti \
-mfpmath=sse -Wno-delete-non-virtual-dtor

OPT_FLAGS = -O3 -funroll-loops -pipe -fno-strict-aliasing
DEBUG_FLAGS = -g -ggdb3 -D_DEBUG
GCC4_FLAGS = -fvisibility=hidden -fvisibility-inlines-hidden 

####################################################
# Plugin lib includes
####################################################

LINK = tier1_i486.a interfaces_i486.a libvstdlib.so libtier0.so \
mathlib_i486.a libprotobuf.a -m32 -lm -ldl -shared -static-libgcc \
-lstdc++

####################################################
# .h file folder includes
####################################################

INCLUDES = -I$(HL2SDK_DIR)/public -I$(HL2SDK_DIR)/public/engine -I$(HL2SDK_DIR)/public/tier0 \
-I$(HL2SDK_DIR)/public/tier1 -I$(HL2SDK_DIR)/public/vstdlib -I$(HL2SDK_DIR)/public/game/server \
-I$(HL2SDK_DIR)/public/game/client

####################################################
# Compile section
####################################################

CFLAGS = $(ARCH_CFLAGS) $(OPT_FLAGS) $(BASE_CFLAGS) $(GCC4_FLAGS)
OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

%.o: %.cpp
	$(CC) -m32 -std=c++11 -c $(INCLUDES) $(CFLAGS) -o $@ $<


all: $(OBJS)
	ln -sf $(SRCDS_DIR)/bin/libtier0.so libtier0.so
	ln -sf $(SRCDS_DIR)/bin/libvstdlib.so libvstdlib.so
	ln -sf $(HL2SDK_DIR)/lib/linux/tier1_i486.a tier1_i486.a
	ln -sf $(HL2SDK_DIR)/lib/linux/interfaces_i486.a interfaces_i486.a
	ln -sf $(HL2SDK_DIR)/lib/linux/mathlib_i486.a mathlib_i486.a
	ln -sf $(HL2SDK_DIR)/lib/linux32/release/libprotobuf.a libprotobuf.a
	$(CC) $(INCLUDES) $(OBJS) $(LINK) -o myplugin.so
	cp myplugin.so /home/steam/steamcmd/csgods/csgo/addons

clean:
	rm -rf *.o
	rm -rf *.so
	rm -rd *.a
