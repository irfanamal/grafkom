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
CMAKE_SOURCE_DIR = /home/irfan/LearnOpenGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/irfan/LearnOpenGL/build

# Include any dependencies generated for this target.
include CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/flags.make

CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o: CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/flags.make
CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o: ../src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irfan/LearnOpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o -c /home/irfan/LearnOpenGL/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp

CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/irfan/LearnOpenGL/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp > CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.i

CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/irfan/LearnOpenGL/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp -o CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.s

CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o.requires:

.PHONY : CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o.requires

CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o.provides: CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o.requires
	$(MAKE) -f CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/build.make CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o.provides.build
.PHONY : CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o.provides

CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o.provides.build: CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o


# Object files for target 5.advanced_lighting__1.advanced_lighting
5_advanced_lighting__1_advanced_lighting_OBJECTS = \
"CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o"

# External object files for target 5.advanced_lighting__1.advanced_lighting
5_advanced_lighting__1_advanced_lighting_EXTERNAL_OBJECTS =

bin/5.advanced_lighting/5.advanced_lighting__1.advanced_lighting: CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o
bin/5.advanced_lighting/5.advanced_lighting__1.advanced_lighting: CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/build.make
bin/5.advanced_lighting/5.advanced_lighting__1.advanced_lighting: /usr/local/lib/libglfw3.a
bin/5.advanced_lighting/5.advanced_lighting__1.advanced_lighting: /usr/lib/x86_64-linux-gnu/libassimp.so
bin/5.advanced_lighting/5.advanced_lighting__1.advanced_lighting: libSTB_IMAGE.a
bin/5.advanced_lighting/5.advanced_lighting__1.advanced_lighting: libGLAD.a
bin/5.advanced_lighting/5.advanced_lighting__1.advanced_lighting: CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irfan/LearnOpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/5.advanced_lighting/5.advanced_lighting__1.advanced_lighting"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/build: bin/5.advanced_lighting/5.advanced_lighting__1.advanced_lighting

.PHONY : CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/build

CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/requires: CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/src/5.advanced_lighting/1.advanced_lighting/advanced_lighting.cpp.o.requires

.PHONY : CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/requires

CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/cmake_clean.cmake
.PHONY : CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/clean

CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/depend:
	cd /home/irfan/LearnOpenGL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irfan/LearnOpenGL /home/irfan/LearnOpenGL /home/irfan/LearnOpenGL/build /home/irfan/LearnOpenGL/build /home/irfan/LearnOpenGL/build/CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/5.advanced_lighting__1.advanced_lighting.dir/depend

