# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_SOURCE_DIR = /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build

# Include any dependencies generated for this target.
include external/glfw-3.1.2/tests/CMakeFiles/empty.dir/depend.make

# Include the progress variables for this target.
include external/glfw-3.1.2/tests/CMakeFiles/empty.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw-3.1.2/tests/CMakeFiles/empty.dir/flags.make

external/glfw-3.1.2/tests/CMakeFiles/empty.dir/empty.c.o: external/glfw-3.1.2/tests/CMakeFiles/empty.dir/flags.make
external/glfw-3.1.2/tests/CMakeFiles/empty.dir/empty.c.o: ../external/glfw-3.1.2/tests/empty.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw-3.1.2/tests/CMakeFiles/empty.dir/empty.c.o"
	cd /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/empty.dir/empty.c.o   -c /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/external/glfw-3.1.2/tests/empty.c

external/glfw-3.1.2/tests/CMakeFiles/empty.dir/empty.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/empty.dir/empty.c.i"
	cd /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/external/glfw-3.1.2/tests/empty.c > CMakeFiles/empty.dir/empty.c.i

external/glfw-3.1.2/tests/CMakeFiles/empty.dir/empty.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/empty.dir/empty.c.s"
	cd /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/external/glfw-3.1.2/tests/empty.c -o CMakeFiles/empty.dir/empty.c.s

external/glfw-3.1.2/tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o: external/glfw-3.1.2/tests/CMakeFiles/empty.dir/flags.make
external/glfw-3.1.2/tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o: ../external/glfw-3.1.2/deps/tinycthread.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object external/glfw-3.1.2/tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o"
	cd /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/empty.dir/__/deps/tinycthread.c.o   -c /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/external/glfw-3.1.2/deps/tinycthread.c

external/glfw-3.1.2/tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/empty.dir/__/deps/tinycthread.c.i"
	cd /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/external/glfw-3.1.2/deps/tinycthread.c > CMakeFiles/empty.dir/__/deps/tinycthread.c.i

external/glfw-3.1.2/tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/empty.dir/__/deps/tinycthread.c.s"
	cd /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/external/glfw-3.1.2/deps/tinycthread.c -o CMakeFiles/empty.dir/__/deps/tinycthread.c.s

# Object files for target empty
empty_OBJECTS = \
"CMakeFiles/empty.dir/empty.c.o" \
"CMakeFiles/empty.dir/__/deps/tinycthread.c.o"

# External object files for target empty
empty_EXTERNAL_OBJECTS =

external/glfw-3.1.2/tests/empty: external/glfw-3.1.2/tests/CMakeFiles/empty.dir/empty.c.o
external/glfw-3.1.2/tests/empty: external/glfw-3.1.2/tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o
external/glfw-3.1.2/tests/empty: external/glfw-3.1.2/tests/CMakeFiles/empty.dir/build.make
external/glfw-3.1.2/tests/empty: external/glfw-3.1.2/src/libglfw3.a
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/librt.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libm.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libX11.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libXrandr.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libXinerama.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libXi.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libXcursor.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libGL.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/librt.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libm.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libX11.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libXrandr.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libXinerama.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libXi.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libXcursor.so
external/glfw-3.1.2/tests/empty: /usr/lib/x86_64-linux-gnu/libGL.so
external/glfw-3.1.2/tests/empty: external/glfw-3.1.2/tests/CMakeFiles/empty.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable empty"
	cd /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build/external/glfw-3.1.2/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/empty.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw-3.1.2/tests/CMakeFiles/empty.dir/build: external/glfw-3.1.2/tests/empty

.PHONY : external/glfw-3.1.2/tests/CMakeFiles/empty.dir/build

external/glfw-3.1.2/tests/CMakeFiles/empty.dir/clean:
	cd /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build/external/glfw-3.1.2/tests && $(CMAKE_COMMAND) -P CMakeFiles/empty.dir/cmake_clean.cmake
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/empty.dir/clean

external/glfw-3.1.2/tests/CMakeFiles/empty.dir/depend:
	cd /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/external/glfw-3.1.2/tests /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build/external/glfw-3.1.2/tests /home/tanujgarg/Downloads/Sem-4/Graphics/Assignment-2/3-d-jet-fighter-game/build/external/glfw-3.1.2/tests/CMakeFiles/empty.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/empty.dir/depend

