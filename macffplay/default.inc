# The C compiler to be used
CC       = gcc

# The C++ compiler to be used
CXX      = g++

# The archiver to be used
AR       = ar

# The command to remove files
RM       = rm -f

# Flags to be passed to both C and C++ code
CPPFLAGS = -O2 -I../mindroid/Mindroid.cpp/ -I/usr/local/include/ -I../ffmpeg/ffmpeg-install-3.2/include -I/usr/include/SDL2

# Flags to be passed to C code
CFLAGS   = 

# Flags to be passed to C++ code
CXXFLAGS = 

# Flags to be passed to the linker, prior to listing of object files.
LDFLAGS  = -L/usr/local/lib/ -L../ffmpeg/ffmpeg-install-3.2/lib/

# Flags to be passed to the linker, after the listing of object files.
LDLIBS   = -pthread -lEGL -lGLESv2 -lSDL2 -lrockchip_vpu -lrockchip_mpp ../ffmpeg/ffmpeg-install-3.2/lib/libavdevice.a ../ffmpeg/ffmpeg-install-3.2/lib/libavfilter.a ../ffmpeg/ffmpeg-install-3.2/lib/libavformat.a ../ffmpeg/ffmpeg-install-3.2/lib/libavcodec.a ../ffmpeg/ffmpeg-install-3.2/lib/libpostproc.a ../ffmpeg/ffmpeg-install-3.2/lib/libswresample.a ../ffmpeg/ffmpeg-install-3.2/lib/libswscale.a ../ffmpeg/ffmpeg-install-3.2/lib/libavutil.a $(shell find ../mindroid/Mindroid.cpp -name "*.o") $(shell PKG_CONFIG_PATH="../ffmpeg/ffmpeg-install-3.2/lib/pkgconfig" pkg-config --static --libs-only-l --silence-errors libavcodec) 

# A list of directories containing source files containing "int
# main()".  Each file will be compiled into a separate executable.
EXE_DIRECTORIES = src

# A list of directories containing other source files.  Each file will
# be compiled, with the resulting source file being linked into each
# executable.
SRC_DIRECTORIES = src

# A list of directories containing include files.  Each directory will
# be made available for #include directives for included files.
INC_DIRECTORIES = src

# A list of directories that contain libraries.  The list can also
# contain patterns that expand to directories that contain libraries.
# Each library is ex
LIB_DIRECTORIES = lib?*

# If BUILD_SHARED is non-zero, shared libraries will be generated.  If
# BUILD_SHARED is greater than BUILD_STATIC, executables will be
# linked against the shared libraries.
BUILD_SHARED = 0

# If BUILD_STATIC is non-zero, static libraries will be generated.  If
# BUILD_STATIC is greater than BUILD_SHARED, executables will be
# linked against the static libraries.
BUILD_STATIC = 1

# Mandatory arguments to both C and C++ compilers.  These arguments
# will be passed even if CPPFLAGS has been overridden by command-line
# arguments.
CPPFLAGS_EXTRA =

# Mandatory arguments to the C compiler.  These arguments will be
# passed even if CFLAGS has been overriden by command-line arguments.
CFLAGS_EXTRA =

# Mandatory arguments to the C++ compiler.  These arguments will be
# passed even if CXXFLAGS has been overridden by command-line arguments.
CXXFLAGS_EXTRA = -std=c++11

# Mandatory arguments to the linker, before the listing of object
# files.  These arguments will be passed even if LDFLAGS has been
# overridden by command-line arguments.
LDFLAGS_EXTRA  = -Llib -Wl,-rpath,\$$ORIGIN/../lib -Wl,--no-as-needed

# Mandatory arguments to the linker, after the listing of object
# files.  These arguments will be passed even if LDLIBS has been
# overridden by command-line arguments.
LDLIBS_EXTRA   =

# Static libraries that should be linked into the executables.  The
# order of libraries is the order of inclusion.
EXTERNAL_STATIC_LIBS =

# Flag to generate position-independent code.  This is passed to
# object files being compiled to shared libraries, but not to any
# other object files.
PIC_FLAG = -fPIC

# A space-delimited list of file extensions to be compiled as C code.
# No element of this list should be present in CPP_EXT.
C_EXT   = c

# A space-delimited list of file extensions to be compiled as C++
# code.  No element of this list should be present in C_EXT.
CPP_EXT = C cc cpp cxx c++ cp

# A space-delimited list of file patterns to be excluded
# For example, this may contain a source file or directory
# that is not to be compiled in the current build.
# % can be used to create wildcard exclusions.
# Note: Files in the base directory are excluded as ./filename.
EXCLUSIONS =

# A function that, when given the name of a library, should return the
# output file of a shared library.  For example, the default version,
# when passed "MyLibrary" as $(1), will return "lib/libMyLibrary.so".
SHARED_LIBRARY_NAME = lib/lib$(1).so

# A function that, when given the name of a library, should return the
# output file of a static library.  For example, the default version,
# when passed "MyLibrary" as $(1), will return "lib/libMyLibrary.a".
STATIC_LIBRARY_NAME = lib/lib$(1).a

#   A macro to determine whether executables will be linked against
# static libraries or shared libraries.  By default, will compile
# against the shared libraries if BUILD_SHARED has a greater numeric
# value than BUILD_STATIC, and will compile against the static
# libraries otherwise.
#   To always link against shared libraries, change this variable to
# 0.  To always link against static libraries, change this variable to 1.
LINK_AGAINST_STATIC = $(shell test "$(BUILD_SHARED)" -gt "$(BUILD_STATIC)"; echo $$?)

# A function that, given the base name of a source file, returns the
# output filename of the executable.  For example, the default
# version, when passed "MyProgram" as $(1), will return "bin/MyProgram".
EXE_NAME     = bin/$(1)

# Determines whether the output is in color or not.  To disable
# coloring, set this variable to 0.
USE_COLOR = 1

# The location to which extra resources should be install-3.2ed.
INSTALL_DEST = /usr/local

# Extra resources that should be copied to $(INSTALL_DEST).  These can
# be either files or directories.
INSTALL_RESOURCES = bin

# A listing of the files and directories to be cleaned when running
# "make clean".
CLEAN_TARGETS = bin lib build

# Which system is the target system.  This may be used by library
# targets to choose which system libraries to include.
SYSTEM = native

# The command to be run to run tests.  This command will be run when
# running "make test".  If this variable is an empty string, then this
# target will be left undefined.
TEST_COMMAND =
