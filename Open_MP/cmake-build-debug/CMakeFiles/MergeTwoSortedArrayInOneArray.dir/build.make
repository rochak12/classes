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
include CMakeFiles/MergeTwoSortedArrayInOneArray.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MergeTwoSortedArrayInOneArray.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MergeTwoSortedArrayInOneArray.dir/flags.make

CMakeFiles/MergeTwoSortedArrayInOneArray.dir/MergeTwoSortedArrayInOneArray.cpp.obj: CMakeFiles/MergeTwoSortedArrayInOneArray.dir/flags.make
CMakeFiles/MergeTwoSortedArrayInOneArray.dir/MergeTwoSortedArrayInOneArray.cpp.obj: ../MergeTwoSortedArrayInOneArray.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Rochak\Desktop\Open_MP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MergeTwoSortedArrayInOneArray.dir/MergeTwoSortedArrayInOneArray.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\MergeTwoSortedArrayInOneArray.dir\MergeTwoSortedArrayInOneArray.cpp.obj -c C:\Users\Rochak\Desktop\Open_MP\MergeTwoSortedArrayInOneArray.cpp

CMakeFiles/MergeTwoSortedArrayInOneArray.dir/MergeTwoSortedArrayInOneArray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MergeTwoSortedArrayInOneArray.dir/MergeTwoSortedArrayInOneArray.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Rochak\Desktop\Open_MP\MergeTwoSortedArrayInOneArray.cpp > CMakeFiles\MergeTwoSortedArrayInOneArray.dir\MergeTwoSortedArrayInOneArray.cpp.i

CMakeFiles/MergeTwoSortedArrayInOneArray.dir/MergeTwoSortedArrayInOneArray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MergeTwoSortedArrayInOneArray.dir/MergeTwoSortedArrayInOneArray.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Rochak\Desktop\Open_MP\MergeTwoSortedArrayInOneArray.cpp -o CMakeFiles\MergeTwoSortedArrayInOneArray.dir\MergeTwoSortedArrayInOneArray.cpp.s

# Object files for target MergeTwoSortedArrayInOneArray
MergeTwoSortedArrayInOneArray_OBJECTS = \
"CMakeFiles/MergeTwoSortedArrayInOneArray.dir/MergeTwoSortedArrayInOneArray.cpp.obj"

# External object files for target MergeTwoSortedArrayInOneArray
MergeTwoSortedArrayInOneArray_EXTERNAL_OBJECTS =

MergeTwoSortedArrayInOneArray.exe: CMakeFiles/MergeTwoSortedArrayInOneArray.dir/MergeTwoSortedArrayInOneArray.cpp.obj
MergeTwoSortedArrayInOneArray.exe: CMakeFiles/MergeTwoSortedArrayInOneArray.dir/build.make
MergeTwoSortedArrayInOneArray.exe: CMakeFiles/MergeTwoSortedArrayInOneArray.dir/linklibs.rsp
MergeTwoSortedArrayInOneArray.exe: CMakeFiles/MergeTwoSortedArrayInOneArray.dir/objects1.rsp
MergeTwoSortedArrayInOneArray.exe: CMakeFiles/MergeTwoSortedArrayInOneArray.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Rochak\Desktop\Open_MP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MergeTwoSortedArrayInOneArray.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\MergeTwoSortedArrayInOneArray.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MergeTwoSortedArrayInOneArray.dir/build: MergeTwoSortedArrayInOneArray.exe

.PHONY : CMakeFiles/MergeTwoSortedArrayInOneArray.dir/build

CMakeFiles/MergeTwoSortedArrayInOneArray.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\MergeTwoSortedArrayInOneArray.dir\cmake_clean.cmake
.PHONY : CMakeFiles/MergeTwoSortedArrayInOneArray.dir/clean

CMakeFiles/MergeTwoSortedArrayInOneArray.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Rochak\Desktop\Open_MP C:\Users\Rochak\Desktop\Open_MP C:\Users\Rochak\Desktop\Open_MP\cmake-build-debug C:\Users\Rochak\Desktop\Open_MP\cmake-build-debug C:\Users\Rochak\Desktop\Open_MP\cmake-build-debug\CMakeFiles\MergeTwoSortedArrayInOneArray.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MergeTwoSortedArrayInOneArray.dir/depend
