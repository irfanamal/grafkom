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
include CMakeFiles/6.pbr__1.2.lighting_textured.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/6.pbr__1.2.lighting_textured.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/6.pbr__1.2.lighting_textured.dir/flags.make

CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o: CMakeFiles/6.pbr__1.2.lighting_textured.dir/flags.make
CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o: ../src/6.pbr/1.2.lighting_textured/lighting_textured.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irfan/LearnOpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o -c /home/irfan/LearnOpenGL/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp

CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/irfan/LearnOpenGL/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp > CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.i

CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/irfan/LearnOpenGL/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp -o CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.s

CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o.requires:

.PHONY : CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o.requires

CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o.provides: CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o.requires
	$(MAKE) -f CMakeFiles/6.pbr__1.2.lighting_textured.dir/build.make CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o.provides.build
.PHONY : CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o.provides

CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o.provides.build: CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o


# Object files for target 6.pbr__1.2.lighting_textured
6_pbr__1_2_lighting_textured_OBJECTS = \
"CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o"

# External object files for target 6.pbr__1.2.lighting_textured
6_pbr__1_2_lighting_textured_EXTERNAL_OBJECTS =

bin/6.pbr/6.pbr__1.2.lighting_textured: CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o
bin/6.pbr/6.pbr__1.2.lighting_textured: CMakeFiles/6.pbr__1.2.lighting_textured.dir/build.make
bin/6.pbr/6.pbr__1.2.lighting_textured: /usr/local/lib/libglfw3.a
bin/6.pbr/6.pbr__1.2.lighting_textured: /usr/lib/x86_64-linux-gnu/libassimp.so
bin/6.pbr/6.pbr__1.2.lighting_textured: libSTB_IMAGE.a
bin/6.pbr/6.pbr__1.2.lighting_textured: libGLAD.a
bin/6.pbr/6.pbr__1.2.lighting_textured: CMakeFiles/6.pbr__1.2.lighting_textured.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irfan/LearnOpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/6.pbr/6.pbr__1.2.lighting_textured"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/6.pbr__1.2.lighting_textured.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/6.pbr__1.2.lighting_textured.dir/build: bin/6.pbr/6.pbr__1.2.lighting_textured

.PHONY : CMakeFiles/6.pbr__1.2.lighting_textured.dir/build

CMakeFiles/6.pbr__1.2.lighting_textured.dir/requires: CMakeFiles/6.pbr__1.2.lighting_textured.dir/src/6.pbr/1.2.lighting_textured/lighting_textured.cpp.o.requires

.PHONY : CMakeFiles/6.pbr__1.2.lighting_textured.dir/requires

CMakeFiles/6.pbr__1.2.lighting_textured.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/6.pbr__1.2.lighting_textured.dir/cmake_clean.cmake
.PHONY : CMakeFiles/6.pbr__1.2.lighting_textured.dir/clean

CMakeFiles/6.pbr__1.2.lighting_textured.dir/depend:
	cd /home/irfan/LearnOpenGL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irfan/LearnOpenGL /home/irfan/LearnOpenGL /home/irfan/LearnOpenGL/build /home/irfan/LearnOpenGL/build /home/irfan/LearnOpenGL/build/CMakeFiles/6.pbr__1.2.lighting_textured.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/6.pbr__1.2.lighting_textured.dir/depend

