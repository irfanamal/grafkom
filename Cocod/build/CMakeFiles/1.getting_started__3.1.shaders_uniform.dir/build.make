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
include CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/flags.make

CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o: CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/flags.make
CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o: ../src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/irfan/LearnOpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o -c /home/irfan/LearnOpenGL/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp

CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/irfan/LearnOpenGL/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp > CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.i

CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/irfan/LearnOpenGL/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp -o CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.s

CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o.requires:

.PHONY : CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o.requires

CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o.provides: CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o.requires
	$(MAKE) -f CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/build.make CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o.provides.build
.PHONY : CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o.provides

CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o.provides.build: CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o


# Object files for target 1.getting_started__3.1.shaders_uniform
1_getting_started__3_1_shaders_uniform_OBJECTS = \
"CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o"

# External object files for target 1.getting_started__3.1.shaders_uniform
1_getting_started__3_1_shaders_uniform_EXTERNAL_OBJECTS =

bin/1.getting_started/1.getting_started__3.1.shaders_uniform: CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o
bin/1.getting_started/1.getting_started__3.1.shaders_uniform: CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/build.make
bin/1.getting_started/1.getting_started__3.1.shaders_uniform: /usr/local/lib/libglfw3.a
bin/1.getting_started/1.getting_started__3.1.shaders_uniform: /usr/lib/x86_64-linux-gnu/libassimp.so
bin/1.getting_started/1.getting_started__3.1.shaders_uniform: libSTB_IMAGE.a
bin/1.getting_started/1.getting_started__3.1.shaders_uniform: libGLAD.a
bin/1.getting_started/1.getting_started__3.1.shaders_uniform: CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/irfan/LearnOpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/1.getting_started/1.getting_started__3.1.shaders_uniform"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/build: bin/1.getting_started/1.getting_started__3.1.shaders_uniform

.PHONY : CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/build

CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/requires: CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp.o.requires

.PHONY : CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/requires

CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/cmake_clean.cmake
.PHONY : CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/clean

CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/depend:
	cd /home/irfan/LearnOpenGL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/irfan/LearnOpenGL /home/irfan/LearnOpenGL /home/irfan/LearnOpenGL/build /home/irfan/LearnOpenGL/build /home/irfan/LearnOpenGL/build/CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/1.getting_started__3.1.shaders_uniform.dir/depend

