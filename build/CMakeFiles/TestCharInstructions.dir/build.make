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
CMAKE_SOURCE_DIR = /home/mark/Documents/intel64xELF

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mark/Documents/intel64xELF/build

# Include any dependencies generated for this target.
include CMakeFiles/TestCharInstructions.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TestCharInstructions.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestCharInstructions.dir/flags.make

CMakeFiles/TestCharInstructions.dir/tokens+dependencies/get_instructions.c.o: CMakeFiles/TestCharInstructions.dir/flags.make
CMakeFiles/TestCharInstructions.dir/tokens+dependencies/get_instructions.c.o: ../tokens+dependencies/get_instructions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Documents/intel64xELF/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TestCharInstructions.dir/tokens+dependencies/get_instructions.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TestCharInstructions.dir/tokens+dependencies/get_instructions.c.o   -c /home/mark/Documents/intel64xELF/tokens+dependencies/get_instructions.c

CMakeFiles/TestCharInstructions.dir/tokens+dependencies/get_instructions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TestCharInstructions.dir/tokens+dependencies/get_instructions.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mark/Documents/intel64xELF/tokens+dependencies/get_instructions.c > CMakeFiles/TestCharInstructions.dir/tokens+dependencies/get_instructions.c.i

CMakeFiles/TestCharInstructions.dir/tokens+dependencies/get_instructions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TestCharInstructions.dir/tokens+dependencies/get_instructions.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mark/Documents/intel64xELF/tokens+dependencies/get_instructions.c -o CMakeFiles/TestCharInstructions.dir/tokens+dependencies/get_instructions.c.s

CMakeFiles/TestCharInstructions.dir/tokens+dependencies/TestCharInstructions.c.o: CMakeFiles/TestCharInstructions.dir/flags.make
CMakeFiles/TestCharInstructions.dir/tokens+dependencies/TestCharInstructions.c.o: ../tokens+dependencies/TestCharInstructions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Documents/intel64xELF/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/TestCharInstructions.dir/tokens+dependencies/TestCharInstructions.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TestCharInstructions.dir/tokens+dependencies/TestCharInstructions.c.o   -c /home/mark/Documents/intel64xELF/tokens+dependencies/TestCharInstructions.c

CMakeFiles/TestCharInstructions.dir/tokens+dependencies/TestCharInstructions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TestCharInstructions.dir/tokens+dependencies/TestCharInstructions.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mark/Documents/intel64xELF/tokens+dependencies/TestCharInstructions.c > CMakeFiles/TestCharInstructions.dir/tokens+dependencies/TestCharInstructions.c.i

CMakeFiles/TestCharInstructions.dir/tokens+dependencies/TestCharInstructions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TestCharInstructions.dir/tokens+dependencies/TestCharInstructions.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mark/Documents/intel64xELF/tokens+dependencies/TestCharInstructions.c -o CMakeFiles/TestCharInstructions.dir/tokens+dependencies/TestCharInstructions.c.s

# Object files for target TestCharInstructions
TestCharInstructions_OBJECTS = \
"CMakeFiles/TestCharInstructions.dir/tokens+dependencies/get_instructions.c.o" \
"CMakeFiles/TestCharInstructions.dir/tokens+dependencies/TestCharInstructions.c.o"

# External object files for target TestCharInstructions
TestCharInstructions_EXTERNAL_OBJECTS =

TestCharInstructions: CMakeFiles/TestCharInstructions.dir/tokens+dependencies/get_instructions.c.o
TestCharInstructions: CMakeFiles/TestCharInstructions.dir/tokens+dependencies/TestCharInstructions.c.o
TestCharInstructions: CMakeFiles/TestCharInstructions.dir/build.make
TestCharInstructions: CMakeFiles/TestCharInstructions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/Documents/intel64xELF/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable TestCharInstructions"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestCharInstructions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TestCharInstructions.dir/build: TestCharInstructions

.PHONY : CMakeFiles/TestCharInstructions.dir/build

CMakeFiles/TestCharInstructions.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TestCharInstructions.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestCharInstructions.dir/clean

CMakeFiles/TestCharInstructions.dir/depend:
	cd /home/mark/Documents/intel64xELF/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/Documents/intel64xELF /home/mark/Documents/intel64xELF /home/mark/Documents/intel64xELF/build /home/mark/Documents/intel64xELF/build /home/mark/Documents/intel64xELF/build/CMakeFiles/TestCharInstructions.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TestCharInstructions.dir/depend

