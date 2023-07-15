#**************************************************************************************************
#
#   raylib makefile for Desktop platforms, Raspberry Pi, Android and HTML5
#
#   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
#
#   This software is provided "as-is", without any express or implied warranty. In no event
#   will the authors be held liable for any damages arising from the use of this software.
#
#   Permission is granted to anyone to use this software for any purpose, including commercial
#   applications, and to alter it and redistribute it freely, subject to the following restrictions:
#
#     1. The origin of this software must not be misrepresented; you must not claim that you
#     wrote the original software. If you use this software in a product, an acknowledgment
#     in the product documentation would be appreciated but is not required.
#
#     2. Altered source versions must be plainly marked as such, and must not be misrepresented
#     as being the original software.
#
#     3. This notice may not be removed or altered from any source distribution.
#
#**************************************************************************************************


# App specific 
# The files you want to get compiled and the output file
# eg if you made n external dependancies on main.cpp, you would add main.cpp extra_1.cpp ... extra_n.cpp

MAIN := main.cpp 

EXE_FILE := main.exe 

EXTRA_DIR := ../source

MEDIA_DIR := ../resources





.PHONY: all clean

# Define required environment variables
#------------------------------------------------------------------------------------------------
# Define target platform: PLATFORM_DESKTOP, PLATFORM_RPI, PLATFORM_DRM, PLATFORM_ANDROID, PLATFORM_WEB
PLATFORM              := PLATFORM_DESKTOP

# Define required raylib variables
PROJECT_NAME          := Cool shooting game
RAYLIB_VERSION        := 4.0.0
#RAYLIB_PATH           := ../../../raylib

# Locations of raylib.h and libraylib.a/libraylib.so
# NOTE: Those variables are only used for PLATFORM_OS: LINUX, BSD
RAYLIB_INCLUDE_PATH   := ../include
RAYLIB_LIB_PATH       := ../lib

# Library type compilation: STATIC (.a) or SHARED (.so/.dll)
RAYLIB_LIBTYPE        := STATIC

# Build mode for project: DEBUG or RELEASE
BUILD_MODE            := DEBUG 

# Use external GLFW library instead of rglfw module
# USE_EXTERNAL_GLFW     := FALSE

# Use Wayland display server protocol on Linux desktop (by default it uses X11 windowing system)
# NOTE: This variable is only used for PLATFORM_OS: LINUX
# USE_WAYLAND_DISPLAY   := FALSE

# Determine PLATFORM_OS in case PLATFORM_DESKTOP selected
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    # No uname.exe on MinGW!, but OS=Windows_NT on Windows!
    # ifeq ($(UNAME),Msys) -> Windows
    ifeq ($(OS),Windows_NT)
        PLATFORM_OS = WINDOWS
    else
        UNAMEOS = $(shell uname)
        ifeq ($(UNAMEOS),Linux)
            PLATFORM_OS = LINUX
        endif
        ifeq ($(UNAMEOS),Darwin)
            PLATFORM_OS = OSX
        endif
        
    endif
endif

ifeq ($(PLATFORM),PLATFORM_DRM)
    UNAMEOS = $(shell uname)
    ifeq ($(UNAMEOS),Linux)
        PLATFORM_OS = LINUX
    endif
endif


# Define raylib release directory for compiled library
#RAYLIB_RELEASE_PATH 	:= $(RAYLIB_PATH)/src


# Define default C compiler: CC
#------------------------------------------------------------------------------------------------
CC := g++

#ifeq ($(PLATFORM),PLATFORM_DESKTOP)
 #   ifeq ($(PLATFORM_OS),OSX)
        # OSX default compiler
   #     CC = clang
  #  endif
#endif

# Define default make program: MAKE
#------------------------------------------------------------------------------------------------
# MAKE := make

# ifeq ($(PLATFORM),PLATFORM_DESKTOP)
#     ifeq ($(PLATFORM_OS),WINDOWS)
#         MAKE = mingw32-make
#     endif
# endif

# Define compiler flags: CFLAGS
#------------------------------------------------------------------------------------------------
#  -O1                  defines optimization level
#  -g                   include debug information on compilation
#  -s                   strip unnecessary data from build
#  -Wall                turns on most, but not all, compiler warnings
#  -std=c99             defines C language mode (standard C from 1999 revision)
#  -std=gnu99           defines C language mode (GNU C from 1999 revision)
#  -Wno-missing-braces  ignore invalid warning (GCC bug 53119)
#  -Wno-unused-value    ignore unused return values of some functions (i.e. fread())
#  -D_DEFAULT_SOURCE    use with -std=c99 on Linux and PLATFORM_WEB, required for timespec
CFLAGS = -Wall -Wno-missing-braces -Wunused-result -std=c++11

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -D_DEBUG
else
    CFLAGS += -s -O1
endif

# Additional flags for compiler (if desired)
#  -Wextra                  enables some extra warning flags that are not enabled by -Wall
#  -Wmissing-prototypes     warn if a global function is defined without a previous prototype declaration
#  -Wstrict-prototypes      warn if a function is declared or defined without specifying the argument types
#  -Werror=implicit-function-declaration   catch function calls without prior declaration
#CFLAGS += -Wextra -Wmissing-prototypes -Wstrict-prototypes
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),LINUX)
        ifeq ($(RAYLIB_LIBTYPE),STATIC)
            CFLAGS += -D_DEFAULT_SOURCE
        endif
    endif
endif

# Define include paths for required headers: INCLUDE_PATHS
# NOTE: Some external/extras libraries could be required (stb, physac, easings...)
#------------------------------------------------------------------------------------------------
#INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external -I$(RAYLIB_PATH)/src/extras

INCLUDE_PATHS += -I$(RAYLIB_INCLUDE_PATH)

# Define library paths containing required libs: LDFLAGS
#------------------------------------------------------------------------------------------------
#LDFLAGS = -L. -L$(RAYLIB_RELEASE_PATH) -L$(RAYLIB_PATH)/src

ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),WINDOWS)
        # NOTE: The resource .rc file contains windows executable icon and properties
        #LDFLAGS += $(RAYLIB_PATH)/src/raylib.rc.data
        # -Wl,--subsystem,windows hides the console window
        ifeq ($(BUILD_MODE), RELEASE)
            LDFLAGS += -Wl,--subsystem,windows
        endif
    endif
    ifeq ($(PLATFORM_OS),LINUX)
        LDFLAGS += -L$(RAYLIB_LIB_PATH)
    endif
endif

# Define libraries required on linking: LDLIBS
# NOTE: To link libraries (lib<name>.so or lib<name>.a), use -l<name>
#------------------------------------------------------------------------------------------------
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),WINDOWS)
        # Libraries for Windows desktop compilation
        # NOTE: WinMM library required to set high-res timer resolution
        LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
        # Required for physac examples
        #LDLIBS += -static -lpthread
    endif
    ifeq ($(PLATFORM_OS),LINUX)

		# @echo "Be sure to install the packages required for linux compilation"
        # Libraries for Debian GNU/Linux desktop compiling
        # NOTE: Required packages: libegl1-mesa-dev
        LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt

        # On X11 requires also below libraries
        LDLIBS += -lX11
        # NOTE: It seems additional libraries are not required any more, latest GLFW just dlopen them
        LDLIBS += -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor
	endif
    ifeq ($(PLATFORM_OS),OSX)
        # Libraries for OSX 10.9 desktop compiling
        # NOTE: Required packages: libopenal-dev libegl1-mesa-dev
        LDLIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
    endif
endif

LIB := -L
ifeq ($(PLATFORM_OS), WINDOWS)
	LIB += $(RAYLIB_LIB_PATH)/windows/
endif
ifeq ($(PLATFORM_OS), LINUX)
	LIB += $(RAYLIB_LIB_PATH)/linux/
endif
ifeq ($(PLATFORM_OS),OSX)
    LIB += $(RAYLIB_LIB_PATH)/macos/
endif

#	$(CC) ../$(CPP_FILES) $(CFLAGS) -I ../include/ -L ../lib/linux/ $(LDLIBS) -o $(EXE_FILE)
#	$(CC) ../$(CPP_FILES) -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/windows/ -lraylib -lopengl32 -lgdi32 -lwinmm -o $(EXE_FILE) 
# LINUX ONLY WAY
# SOURCES := $(shell find $(EXTRA_DIR) -name '*.cpp')

# rwildcard function to scan a directory for .cpp files
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SOURCES:= $(call rwildcard,$(EXTRA_DIR),*.cpp)

default: ../$(MAIN) $(SOURCES)
	$(CC) ../$(MAIN) $(SOURCES) $(CFLAGS) -I $(RAYLIB_INCLUDE_PATH) $(LIB) $(LDLIBS) -o $(EXE_FILE) 
	@echo "Compiled $(EXE_FILE)"



# Clean everything
clean:
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),WINDOWS)
		del *.o *.exe /s
    endif
    ifeq ($(PLATFORM_OS),LINUX)
		find . -type f -executable -delete
		rm -fv *.o
    endif
    
endif
	@echo Cleaning done

