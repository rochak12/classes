# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.1.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.1.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Rochak\Desktop\Open_MP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Rochak\Desktop\Open_MP\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/practice_CA.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/practice_CA.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/practice_CA.dir/flags.make

CMakeFiles/practice_CA.dir/practice_CA.c.obj: CMakeFiles/practice_CA.dir/flags.make
CMakeFiles/practice_CA.dir/practice_CA.c.obj: ../practice_CA.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Rochak\Desktop\Open_MP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/practice_CA.dir/practice_CA.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\practice_CA.dir\practice_CA.c.obj   -c C:\Users\Rochak\Desktop\Open_MP\practice_CA.c

CMakeFiles/practice_CA.dir/practice_CA.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/practice_CA.dir/practice_CA.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Rochak\Desktop\Open_MP\practice_CA.c > CMakeFiles\practice_CA.dir\practice_CA.c.i

CMakeFiles/practice_CA.dir/practice_CA.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/practice_CA.dir/practice_CA.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Rochak\Desktop\Open_MP\practice_CA.c -o CMakeFiles\practice_CA.dir\practice_CA.c.s

# Object files for target practice_CA
practice_CA_OBJECTS = \
"CMakeFiles/practice_CA.dir/practice_CA.c.obj"

# External object files for target practice_CA
practice_CA_EXTERNAL_OBJECTS =

practice_CA.exe: CMakeFiles/practice_CA.dir/practice_CA.c.obj
practice_CA.exe: CMakeFiles/practice_CA.dir/build.make
practice_CA.exe: CMakeFiles/practice_CA.dir/linklibs.rsp
practice_CA.exe: CMakeFiles/practice_CA.dir/objects1.rsp
practice_CA.exe: CMakeFiles/practice_CA.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Rochak\Desktop\Open_MP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable practice_CA.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\practice_CA.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/practice_CA.dir/build: practice_CA.exe

.PHONY : CMakeFiles/practice_CA.dir/build

CMakeFiles/practice_CA.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\practice_CA.dir\cmake_clean.cmake
.PHONY : CMakeFiles/practice_CA.dir/clean

CMakeFiles/practice_CA.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Rochak\Desktop\Open_MP C:\Users\Rochak\Desktop\Open_MP C:\Users\Rochak\Desktop\Open_MP\cmake-build-debug C:\Users\Rochak\Desktop\Open_MP\cmake-build-debug C:\Users\Rochak\Desktop\Open_MP\cmake-build-debug\CMakeFiles\practice_CA.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/practice_CA.dir/depend

