# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/irfan/grafkom/Assets

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/irfan/grafkom/Assets/build

# Include any dependencies generated for this target.
include CMakeFiles/5.advanced_lighting__7.bloom.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/5.advanced_lighting__7.bloom.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/5.advanced_lighting__7.bloom.dir/flags.make

CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o: CMakeFiles/5.advanced_lighting__7.bloom.dir/flags.make
CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o: ../src/5.advanced_lighting/7.bloom/bloom.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irfan/grafkom/Assets/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o -c /home/irfan/grafkom/Assets/src/5.advanced_lighting/7.bloom/bloom.cpp

CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/irfan/grafkom/Assets/src/5.advanced_lighting/7.bloom/bloom.cpp > CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.i

CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/irfan/grafkom/Assets/src/5.advanced_lighting/7.bloom/bloom.cpp -o CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.s

CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o.requires:

.PHONY : CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o.requires

CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o.provides: CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o.requires
	$(MAKE) -f CMakeFiles/5.advanced_lighting__7.bloom.dir/build.make CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o.provides.build
.PHONY : CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o.provides

CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o.provides.build: CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o


# Object files for target 5.advanced_lighting__7.bloom
5_advanced_lighting__7_bloom_OBJECTS = \
"CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o"

# External object files for target 5.advanced_lighting__7.bloom
5_advanced_lighting__7_bloom_EXTERNAL_OBJECTS =

bin/5.advanced_lighting/5.advanced_lighting__7.bloom: CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o
bin/5.advanced_lighting/5.advanced_lighting__7.bloom: CMakeFiles/5.advanced_lighting__7.bloom.dir/build.make
bin/5.advanced_lighting/5.advanced_lighting__7.bloom: /usr/local/lib/libglfw3.a
bin/5.advanced_lighting/5.advanced_lighting__7.bloom: /usr/lib/x86_64-linux-gnu/libassimp.so
bin/5.advanced_lighting/5.advanced_lighting__7.bloom: libSTB_IMAGE.a
bin/5.advanced_lighting/5.advanced_lighting__7.bloom: libGLAD.a
bin/5.advanced_lighting/5.advanced_lighting__7.bloom: CMakeFiles/5.advanced_lighting__7.bloom.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irfan/grafkom/Assets/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/5.advanced_lighting/5.advanced_lighting__7.bloom"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/5.advanced_lighting__7.bloom.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/5.advanced_lighting__7.bloom.dir/build: bin/5.advanced_lighting/5.advanced_lighting__7.bloom

.PHONY : CMakeFiles/5.advanced_lighting__7.bloom.dir/build

CMakeFiles/5.advanced_lighting__7.bloom.dir/requires: CMakeFiles/5.advanced_lighting__7.bloom.dir/src/5.advanced_lighting/7.bloom/bloom.cpp.o.requires

.PHONY : CMakeFiles/5.advanced_lighting__7.bloom.dir/requires

CMakeFiles/5.advanced_lighting__7.bloom.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/5.advanced_lighting__7.bloom.dir/cmake_clean.cmake
.PHONY : CMakeFiles/5.advanced_lighting__7.bloom.dir/clean

CMakeFiles/5.advanced_lighting__7.bloom.dir/depend:
	cd /home/irfan/grafkom/Assets/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irfan/grafkom/Assets /home/irfan/grafkom/Assets /home/irfan/grafkom/Assets/build /home/irfan/grafkom/Assets/build /home/irfan/grafkom/Assets/build/CMakeFiles/5.advanced_lighting__7.bloom.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/5.advanced_lighting__7.bloom.dir/depend

