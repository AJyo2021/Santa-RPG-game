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
CMAKE_SOURCE_DIR = /home/sciencemouse/SantaGame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sciencemouse/SantaGame/build

# Include any dependencies generated for this target.
include CMakeFiles/SantaGame.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SantaGame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SantaGame.dir/flags.make

CMakeFiles/SantaGame.dir/src/santa.c.o: CMakeFiles/SantaGame.dir/flags.make
CMakeFiles/SantaGame.dir/src/santa.c.o: ../src/santa.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sciencemouse/SantaGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SantaGame.dir/src/santa.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SantaGame.dir/src/santa.c.o   -c /home/sciencemouse/SantaGame/src/santa.c

CMakeFiles/SantaGame.dir/src/santa.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SantaGame.dir/src/santa.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sciencemouse/SantaGame/src/santa.c > CMakeFiles/SantaGame.dir/src/santa.c.i

CMakeFiles/SantaGame.dir/src/santa.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SantaGame.dir/src/santa.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sciencemouse/SantaGame/src/santa.c -o CMakeFiles/SantaGame.dir/src/santa.c.s

# Object files for target SantaGame
SantaGame_OBJECTS = \
"CMakeFiles/SantaGame.dir/src/santa.c.o"

# External object files for target SantaGame
SantaGame_EXTERNAL_OBJECTS =

bin/SantaGame: CMakeFiles/SantaGame.dir/src/santa.c.o
bin/SantaGame: CMakeFiles/SantaGame.dir/build.make
bin/SantaGame: CMakeFiles/SantaGame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sciencemouse/SantaGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/SantaGame"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SantaGame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SantaGame.dir/build: bin/SantaGame

.PHONY : CMakeFiles/SantaGame.dir/build

CMakeFiles/SantaGame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SantaGame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SantaGame.dir/clean

CMakeFiles/SantaGame.dir/depend:
	cd /home/sciencemouse/SantaGame/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sciencemouse/SantaGame /home/sciencemouse/SantaGame /home/sciencemouse/SantaGame/build /home/sciencemouse/SantaGame/build /home/sciencemouse/SantaGame/build/CMakeFiles/SantaGame.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SantaGame.dir/depend

