# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build

# Include any dependencies generated for this target.
include CMakeFiles/Midterm.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Midterm.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Midterm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Midterm.dir/flags.make

CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.pch: CMakeFiles/Midterm.dir/flags.make
CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.pch: CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.cxx
CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.pch: CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx
CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.pch: CMakeFiles/Midterm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.pch"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGSarm64) -Winvalid-pch -Xclang -emit-pch -Xclang -include -Xclang /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx -x c++-header -MD -MT CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.pch -MF CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.pch.d -o CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.pch -c /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.cxx

CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGSarm64) -Winvalid-pch -Xclang -emit-pch -Xclang -include -Xclang /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx -x c++-header -E /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.cxx > CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.i

CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGSarm64) -Winvalid-pch -Xclang -emit-pch -Xclang -include -Xclang /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx -x c++-header -S /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.cxx -o CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.s

CMakeFiles/Midterm.dir/Main.cpp.o: CMakeFiles/Midterm.dir/flags.make
CMakeFiles/Midterm.dir/Main.cpp.o: /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/Main.cpp
CMakeFiles/Midterm.dir/Main.cpp.o: CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx
CMakeFiles/Midterm.dir/Main.cpp.o: CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.pch
CMakeFiles/Midterm.dir/Main.cpp.o: CMakeFiles/Midterm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Midterm.dir/Main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx -MD -MT CMakeFiles/Midterm.dir/Main.cpp.o -MF CMakeFiles/Midterm.dir/Main.cpp.o.d -o CMakeFiles/Midterm.dir/Main.cpp.o -c /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/Main.cpp

CMakeFiles/Midterm.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Midterm.dir/Main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx -E /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/Main.cpp > CMakeFiles/Midterm.dir/Main.cpp.i

CMakeFiles/Midterm.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Midterm.dir/Main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx -S /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/Main.cpp -o CMakeFiles/Midterm.dir/Main.cpp.s

CMakeFiles/Midterm.dir/src/ImageManager.cpp.o: CMakeFiles/Midterm.dir/flags.make
CMakeFiles/Midterm.dir/src/ImageManager.cpp.o: /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/src/ImageManager.cpp
CMakeFiles/Midterm.dir/src/ImageManager.cpp.o: CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx
CMakeFiles/Midterm.dir/src/ImageManager.cpp.o: CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.pch
CMakeFiles/Midterm.dir/src/ImageManager.cpp.o: CMakeFiles/Midterm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Midterm.dir/src/ImageManager.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx -MD -MT CMakeFiles/Midterm.dir/src/ImageManager.cpp.o -MF CMakeFiles/Midterm.dir/src/ImageManager.cpp.o.d -o CMakeFiles/Midterm.dir/src/ImageManager.cpp.o -c /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/src/ImageManager.cpp

CMakeFiles/Midterm.dir/src/ImageManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Midterm.dir/src/ImageManager.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx -E /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/src/ImageManager.cpp > CMakeFiles/Midterm.dir/src/ImageManager.cpp.i

CMakeFiles/Midterm.dir/src/ImageManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Midterm.dir/src/ImageManager.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx -S /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/src/ImageManager.cpp -o CMakeFiles/Midterm.dir/src/ImageManager.cpp.s

# Object files for target Midterm
Midterm_OBJECTS = \
"CMakeFiles/Midterm.dir/Main.cpp.o" \
"CMakeFiles/Midterm.dir/src/ImageManager.cpp.o"

# External object files for target Midterm
Midterm_EXTERNAL_OBJECTS =

Midterm: CMakeFiles/Midterm.dir/cmake_pch_arm64.hxx.pch
Midterm: CMakeFiles/Midterm.dir/Main.cpp.o
Midterm: CMakeFiles/Midterm.dir/src/ImageManager.cpp.o
Midterm: CMakeFiles/Midterm.dir/build.make
Midterm: CMakeFiles/Midterm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Midterm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Midterm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Midterm.dir/build: Midterm
.PHONY : CMakeFiles/Midterm.dir/build

CMakeFiles/Midterm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Midterm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Midterm.dir/clean

CMakeFiles/Midterm.dir/depend:
	cd /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build /Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/build/CMakeFiles/Midterm.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Midterm.dir/depend

