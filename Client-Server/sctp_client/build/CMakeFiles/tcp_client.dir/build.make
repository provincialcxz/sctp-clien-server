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
CMAKE_SOURCE_DIR = /home/erema/code/Client-Server/tcp_client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erema/code/Client-Server/tcp_client/build

# Include any dependencies generated for this target.
include CMakeFiles/tcp_client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tcp_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tcp_client.dir/flags.make

CMakeFiles/tcp_client.dir/main.cpp.o: CMakeFiles/tcp_client.dir/flags.make
CMakeFiles/tcp_client.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erema/code/Client-Server/tcp_client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tcp_client.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcp_client.dir/main.cpp.o -c /home/erema/code/Client-Server/tcp_client/main.cpp

CMakeFiles/tcp_client.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_client.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erema/code/Client-Server/tcp_client/main.cpp > CMakeFiles/tcp_client.dir/main.cpp.i

CMakeFiles/tcp_client.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_client.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erema/code/Client-Server/tcp_client/main.cpp -o CMakeFiles/tcp_client.dir/main.cpp.s

# Object files for target tcp_client
tcp_client_OBJECTS = \
"CMakeFiles/tcp_client.dir/main.cpp.o"

# External object files for target tcp_client
tcp_client_EXTERNAL_OBJECTS =

tcp_client: CMakeFiles/tcp_client.dir/main.cpp.o
tcp_client: CMakeFiles/tcp_client.dir/build.make
tcp_client: /usr/lib/x86_64-linux-gnu/libsctp.a
tcp_client: CMakeFiles/tcp_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/erema/code/Client-Server/tcp_client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tcp_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcp_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tcp_client.dir/build: tcp_client

.PHONY : CMakeFiles/tcp_client.dir/build

CMakeFiles/tcp_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tcp_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tcp_client.dir/clean

CMakeFiles/tcp_client.dir/depend:
	cd /home/erema/code/Client-Server/tcp_client/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erema/code/Client-Server/tcp_client /home/erema/code/Client-Server/tcp_client /home/erema/code/Client-Server/tcp_client/build /home/erema/code/Client-Server/tcp_client/build /home/erema/code/Client-Server/tcp_client/build/CMakeFiles/tcp_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tcp_client.dir/depend

