# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zhanghui/codes/slamcodes/cmaketext

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhanghui/codes/slamcodes/cmaketext/build

# Include any dependencies generated for this target.
include CMakeFiles/libhelloslam.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libhelloslam.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libhelloslam.dir/flags.make

CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o: CMakeFiles/libhelloslam.dir/flags.make
CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o: ../libhelloslam.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhanghui/codes/slamcodes/cmaketext/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o -c /home/zhanghui/codes/slamcodes/cmaketext/libhelloslam.cpp

CMakeFiles/libhelloslam.dir/libhelloslam.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libhelloslam.dir/libhelloslam.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhanghui/codes/slamcodes/cmaketext/libhelloslam.cpp > CMakeFiles/libhelloslam.dir/libhelloslam.cpp.i

CMakeFiles/libhelloslam.dir/libhelloslam.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libhelloslam.dir/libhelloslam.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhanghui/codes/slamcodes/cmaketext/libhelloslam.cpp -o CMakeFiles/libhelloslam.dir/libhelloslam.cpp.s

CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o.requires:

.PHONY : CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o.requires

CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o.provides: CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o.requires
	$(MAKE) -f CMakeFiles/libhelloslam.dir/build.make CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o.provides.build
.PHONY : CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o.provides

CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o.provides.build: CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o


# Object files for target libhelloslam
libhelloslam_OBJECTS = \
"CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o"

# External object files for target libhelloslam
libhelloslam_EXTERNAL_OBJECTS =

libhelloslam: CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o
libhelloslam: CMakeFiles/libhelloslam.dir/build.make
libhelloslam: CMakeFiles/libhelloslam.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhanghui/codes/slamcodes/cmaketext/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable libhelloslam"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libhelloslam.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libhelloslam.dir/build: libhelloslam

.PHONY : CMakeFiles/libhelloslam.dir/build

CMakeFiles/libhelloslam.dir/requires: CMakeFiles/libhelloslam.dir/libhelloslam.cpp.o.requires

.PHONY : CMakeFiles/libhelloslam.dir/requires

CMakeFiles/libhelloslam.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libhelloslam.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libhelloslam.dir/clean

CMakeFiles/libhelloslam.dir/depend:
	cd /home/zhanghui/codes/slamcodes/cmaketext/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhanghui/codes/slamcodes/cmaketext /home/zhanghui/codes/slamcodes/cmaketext /home/zhanghui/codes/slamcodes/cmaketext/build /home/zhanghui/codes/slamcodes/cmaketext/build /home/zhanghui/codes/slamcodes/cmaketext/build/CMakeFiles/libhelloslam.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libhelloslam.dir/depend

