# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /root/workspace/MyJson

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/workspace/MyJson/build

# Include any dependencies generated for this target.
include CMakeFiles/myjson.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/myjson.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/myjson.dir/flags.make

CMakeFiles/myjson.dir/myjson.c.o: CMakeFiles/myjson.dir/flags.make
CMakeFiles/myjson.dir/myjson.c.o: ../myjson.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/MyJson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/myjson.dir/myjson.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/myjson.dir/myjson.c.o   -c /root/workspace/MyJson/myjson.c

CMakeFiles/myjson.dir/myjson.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/myjson.dir/myjson.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/workspace/MyJson/myjson.c > CMakeFiles/myjson.dir/myjson.c.i

CMakeFiles/myjson.dir/myjson.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/myjson.dir/myjson.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/workspace/MyJson/myjson.c -o CMakeFiles/myjson.dir/myjson.c.s

# Object files for target myjson
myjson_OBJECTS = \
"CMakeFiles/myjson.dir/myjson.c.o"

# External object files for target myjson
myjson_EXTERNAL_OBJECTS =

libmyjson.a: CMakeFiles/myjson.dir/myjson.c.o
libmyjson.a: CMakeFiles/myjson.dir/build.make
libmyjson.a: CMakeFiles/myjson.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/workspace/MyJson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libmyjson.a"
	$(CMAKE_COMMAND) -P CMakeFiles/myjson.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myjson.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/myjson.dir/build: libmyjson.a

.PHONY : CMakeFiles/myjson.dir/build

CMakeFiles/myjson.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/myjson.dir/cmake_clean.cmake
.PHONY : CMakeFiles/myjson.dir/clean

CMakeFiles/myjson.dir/depend:
	cd /root/workspace/MyJson/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/workspace/MyJson /root/workspace/MyJson /root/workspace/MyJson/build /root/workspace/MyJson/build /root/workspace/MyJson/build/CMakeFiles/myjson.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/myjson.dir/depend
