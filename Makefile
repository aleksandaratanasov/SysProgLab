# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/redbaron/QtProjects/HskaCompiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/redbaron/QtProjects/HskaCompiler

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/redbaron/QtProjects/HskaCompiler/CMakeFiles /home/redbaron/QtProjects/HskaCompiler/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/redbaron/QtProjects/HskaCompiler/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named HskaCompiler

# Build rule for target.
HskaCompiler: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 HskaCompiler
.PHONY : HskaCompiler

# fast build rule for target.
HskaCompiler/fast:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/build
.PHONY : HskaCompiler/fast

Container/ObjectContainer.o: Container/ObjectContainer.cpp.o
.PHONY : Container/ObjectContainer.o

# target to build an object file
Container/ObjectContainer.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Container/ObjectContainer.cpp.o
.PHONY : Container/ObjectContainer.cpp.o

Container/ObjectContainer.i: Container/ObjectContainer.cpp.i
.PHONY : Container/ObjectContainer.i

# target to preprocess a source file
Container/ObjectContainer.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Container/ObjectContainer.cpp.i
.PHONY : Container/ObjectContainer.cpp.i

Container/ObjectContainer.s: Container/ObjectContainer.cpp.s
.PHONY : Container/ObjectContainer.s

# target to generate assembly for a file
Container/ObjectContainer.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Container/ObjectContainer.cpp.s
.PHONY : Container/ObjectContainer.cpp.s

IO/BufferMonitor.o: IO/BufferMonitor.cpp.o
.PHONY : IO/BufferMonitor.o

# target to build an object file
IO/BufferMonitor.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/BufferMonitor.cpp.o
.PHONY : IO/BufferMonitor.cpp.o

IO/BufferMonitor.i: IO/BufferMonitor.cpp.i
.PHONY : IO/BufferMonitor.i

# target to preprocess a source file
IO/BufferMonitor.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/BufferMonitor.cpp.i
.PHONY : IO/BufferMonitor.cpp.i

IO/BufferMonitor.s: IO/BufferMonitor.cpp.s
.PHONY : IO/BufferMonitor.s

# target to generate assembly for a file
IO/BufferMonitor.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/BufferMonitor.cpp.s
.PHONY : IO/BufferMonitor.cpp.s

IO/ConsoleOutBuffer.o: IO/ConsoleOutBuffer.cpp.o
.PHONY : IO/ConsoleOutBuffer.o

# target to build an object file
IO/ConsoleOutBuffer.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/ConsoleOutBuffer.cpp.o
.PHONY : IO/ConsoleOutBuffer.cpp.o

IO/ConsoleOutBuffer.i: IO/ConsoleOutBuffer.cpp.i
.PHONY : IO/ConsoleOutBuffer.i

# target to preprocess a source file
IO/ConsoleOutBuffer.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/ConsoleOutBuffer.cpp.i
.PHONY : IO/ConsoleOutBuffer.cpp.i

IO/ConsoleOutBuffer.s: IO/ConsoleOutBuffer.cpp.s
.PHONY : IO/ConsoleOutBuffer.s

# target to generate assembly for a file
IO/ConsoleOutBuffer.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/ConsoleOutBuffer.cpp.s
.PHONY : IO/ConsoleOutBuffer.cpp.s

IO/InBuffer.o: IO/InBuffer.cpp.o
.PHONY : IO/InBuffer.o

# target to build an object file
IO/InBuffer.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/InBuffer.cpp.o
.PHONY : IO/InBuffer.cpp.o

IO/InBuffer.i: IO/InBuffer.cpp.i
.PHONY : IO/InBuffer.i

# target to preprocess a source file
IO/InBuffer.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/InBuffer.cpp.i
.PHONY : IO/InBuffer.cpp.i

IO/InBuffer.s: IO/InBuffer.cpp.s
.PHONY : IO/InBuffer.s

# target to generate assembly for a file
IO/InBuffer.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/InBuffer.cpp.s
.PHONY : IO/InBuffer.cpp.s

IO/OutBuffer.o: IO/OutBuffer.cpp.o
.PHONY : IO/OutBuffer.o

# target to build an object file
IO/OutBuffer.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/OutBuffer.cpp.o
.PHONY : IO/OutBuffer.cpp.o

IO/OutBuffer.i: IO/OutBuffer.cpp.i
.PHONY : IO/OutBuffer.i

# target to preprocess a source file
IO/OutBuffer.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/OutBuffer.cpp.i
.PHONY : IO/OutBuffer.cpp.i

IO/OutBuffer.s: IO/OutBuffer.cpp.s
.PHONY : IO/OutBuffer.s

# target to generate assembly for a file
IO/OutBuffer.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/OutBuffer.cpp.s
.PHONY : IO/OutBuffer.cpp.s

IO/ThreadFileOutBuffer.o: IO/ThreadFileOutBuffer.cpp.o
.PHONY : IO/ThreadFileOutBuffer.o

# target to build an object file
IO/ThreadFileOutBuffer.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/ThreadFileOutBuffer.cpp.o
.PHONY : IO/ThreadFileOutBuffer.cpp.o

IO/ThreadFileOutBuffer.i: IO/ThreadFileOutBuffer.cpp.i
.PHONY : IO/ThreadFileOutBuffer.i

# target to preprocess a source file
IO/ThreadFileOutBuffer.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/ThreadFileOutBuffer.cpp.i
.PHONY : IO/ThreadFileOutBuffer.cpp.i

IO/ThreadFileOutBuffer.s: IO/ThreadFileOutBuffer.cpp.s
.PHONY : IO/ThreadFileOutBuffer.s

# target to generate assembly for a file
IO/ThreadFileOutBuffer.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/ThreadFileOutBuffer.cpp.s
.PHONY : IO/ThreadFileOutBuffer.cpp.s

IO/ThreadInBuffer.o: IO/ThreadInBuffer.cpp.o
.PHONY : IO/ThreadInBuffer.o

# target to build an object file
IO/ThreadInBuffer.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/ThreadInBuffer.cpp.o
.PHONY : IO/ThreadInBuffer.cpp.o

IO/ThreadInBuffer.i: IO/ThreadInBuffer.cpp.i
.PHONY : IO/ThreadInBuffer.i

# target to preprocess a source file
IO/ThreadInBuffer.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/ThreadInBuffer.cpp.i
.PHONY : IO/ThreadInBuffer.cpp.i

IO/ThreadInBuffer.s: IO/ThreadInBuffer.cpp.s
.PHONY : IO/ThreadInBuffer.s

# target to generate assembly for a file
IO/ThreadInBuffer.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/IO/ThreadInBuffer.cpp.s
.PHONY : IO/ThreadInBuffer.cpp.s

Parser/PARSER_NEW.o: Parser/PARSER_NEW.cpp.o
.PHONY : Parser/PARSER_NEW.o

# target to build an object file
Parser/PARSER_NEW.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Parser/PARSER_NEW.cpp.o
.PHONY : Parser/PARSER_NEW.cpp.o

Parser/PARSER_NEW.i: Parser/PARSER_NEW.cpp.i
.PHONY : Parser/PARSER_NEW.i

# target to preprocess a source file
Parser/PARSER_NEW.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Parser/PARSER_NEW.cpp.i
.PHONY : Parser/PARSER_NEW.cpp.i

Parser/PARSER_NEW.s: Parser/PARSER_NEW.cpp.s
.PHONY : Parser/PARSER_NEW.s

# target to generate assembly for a file
Parser/PARSER_NEW.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Parser/PARSER_NEW.cpp.s
.PHONY : Parser/PARSER_NEW.cpp.s

Scanner/Information.o: Scanner/Information.cpp.o
.PHONY : Scanner/Information.o

# target to build an object file
Scanner/Information.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/Information.cpp.o
.PHONY : Scanner/Information.cpp.o

Scanner/Information.i: Scanner/Information.cpp.i
.PHONY : Scanner/Information.i

# target to preprocess a source file
Scanner/Information.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/Information.cpp.i
.PHONY : Scanner/Information.cpp.i

Scanner/Information.s: Scanner/Information.cpp.s
.PHONY : Scanner/Information.s

# target to generate assembly for a file
Scanner/Information.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/Information.cpp.s
.PHONY : Scanner/Information.cpp.s

Scanner/List.o: Scanner/List.cpp.o
.PHONY : Scanner/List.o

# target to build an object file
Scanner/List.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/List.cpp.o
.PHONY : Scanner/List.cpp.o

Scanner/List.i: Scanner/List.cpp.i
.PHONY : Scanner/List.i

# target to preprocess a source file
Scanner/List.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/List.cpp.i
.PHONY : Scanner/List.cpp.i

Scanner/List.s: Scanner/List.cpp.s
.PHONY : Scanner/List.s

# target to generate assembly for a file
Scanner/List.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/List.cpp.s
.PHONY : Scanner/List.cpp.s

Scanner/ListElement.o: Scanner/ListElement.cpp.o
.PHONY : Scanner/ListElement.o

# target to build an object file
Scanner/ListElement.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/ListElement.cpp.o
.PHONY : Scanner/ListElement.cpp.o

Scanner/ListElement.i: Scanner/ListElement.cpp.i
.PHONY : Scanner/ListElement.i

# target to preprocess a source file
Scanner/ListElement.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/ListElement.cpp.i
.PHONY : Scanner/ListElement.cpp.i

Scanner/ListElement.s: Scanner/ListElement.cpp.s
.PHONY : Scanner/ListElement.s

# target to generate assembly for a file
Scanner/ListElement.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/ListElement.cpp.s
.PHONY : Scanner/ListElement.cpp.s

Scanner/Scanner.o: Scanner/Scanner.cpp.o
.PHONY : Scanner/Scanner.o

# target to build an object file
Scanner/Scanner.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/Scanner.cpp.o
.PHONY : Scanner/Scanner.cpp.o

Scanner/Scanner.i: Scanner/Scanner.cpp.i
.PHONY : Scanner/Scanner.i

# target to preprocess a source file
Scanner/Scanner.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/Scanner.cpp.i
.PHONY : Scanner/Scanner.cpp.i

Scanner/Scanner.s: Scanner/Scanner.cpp.s
.PHONY : Scanner/Scanner.s

# target to generate assembly for a file
Scanner/Scanner.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/Scanner.cpp.s
.PHONY : Scanner/Scanner.cpp.s

Scanner/SymtabTest.o: Scanner/SymtabTest.cpp.o
.PHONY : Scanner/SymtabTest.o

# target to build an object file
Scanner/SymtabTest.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/SymtabTest.cpp.o
.PHONY : Scanner/SymtabTest.cpp.o

Scanner/SymtabTest.i: Scanner/SymtabTest.cpp.i
.PHONY : Scanner/SymtabTest.i

# target to preprocess a source file
Scanner/SymtabTest.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/SymtabTest.cpp.i
.PHONY : Scanner/SymtabTest.cpp.i

Scanner/SymtabTest.s: Scanner/SymtabTest.cpp.s
.PHONY : Scanner/SymtabTest.s

# target to generate assembly for a file
Scanner/SymtabTest.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/SymtabTest.cpp.s
.PHONY : Scanner/SymtabTest.cpp.s

Scanner/Symtable.o: Scanner/Symtable.cpp.o
.PHONY : Scanner/Symtable.o

# target to build an object file
Scanner/Symtable.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/Symtable.cpp.o
.PHONY : Scanner/Symtable.cpp.o

Scanner/Symtable.i: Scanner/Symtable.cpp.i
.PHONY : Scanner/Symtable.i

# target to preprocess a source file
Scanner/Symtable.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/Symtable.cpp.i
.PHONY : Scanner/Symtable.cpp.i

Scanner/Symtable.s: Scanner/Symtable.cpp.s
.PHONY : Scanner/Symtable.s

# target to generate assembly for a file
Scanner/Symtable.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/Symtable.cpp.s
.PHONY : Scanner/Symtable.cpp.s

Scanner/Token.o: Scanner/Token.cpp.o
.PHONY : Scanner/Token.o

# target to build an object file
Scanner/Token.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/Token.cpp.o
.PHONY : Scanner/Token.cpp.o

Scanner/Token.i: Scanner/Token.cpp.i
.PHONY : Scanner/Token.i

# target to preprocess a source file
Scanner/Token.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/Token.cpp.i
.PHONY : Scanner/Token.cpp.i

Scanner/Token.s: Scanner/Token.cpp.s
.PHONY : Scanner/Token.s

# target to generate assembly for a file
Scanner/Token.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/Scanner/Token.cpp.s
.PHONY : Scanner/Token.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/HskaCompiler.dir/build.make CMakeFiles/HskaCompiler.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... HskaCompiler"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Container/ObjectContainer.o"
	@echo "... Container/ObjectContainer.i"
	@echo "... Container/ObjectContainer.s"
	@echo "... IO/BufferMonitor.o"
	@echo "... IO/BufferMonitor.i"
	@echo "... IO/BufferMonitor.s"
	@echo "... IO/ConsoleOutBuffer.o"
	@echo "... IO/ConsoleOutBuffer.i"
	@echo "... IO/ConsoleOutBuffer.s"
	@echo "... IO/InBuffer.o"
	@echo "... IO/InBuffer.i"
	@echo "... IO/InBuffer.s"
	@echo "... IO/OutBuffer.o"
	@echo "... IO/OutBuffer.i"
	@echo "... IO/OutBuffer.s"
	@echo "... IO/ThreadFileOutBuffer.o"
	@echo "... IO/ThreadFileOutBuffer.i"
	@echo "... IO/ThreadFileOutBuffer.s"
	@echo "... IO/ThreadInBuffer.o"
	@echo "... IO/ThreadInBuffer.i"
	@echo "... IO/ThreadInBuffer.s"
	@echo "... Parser/PARSER_NEW.o"
	@echo "... Parser/PARSER_NEW.i"
	@echo "... Parser/PARSER_NEW.s"
	@echo "... Scanner/Information.o"
	@echo "... Scanner/Information.i"
	@echo "... Scanner/Information.s"
	@echo "... Scanner/List.o"
	@echo "... Scanner/List.i"
	@echo "... Scanner/List.s"
	@echo "... Scanner/ListElement.o"
	@echo "... Scanner/ListElement.i"
	@echo "... Scanner/ListElement.s"
	@echo "... Scanner/Scanner.o"
	@echo "... Scanner/Scanner.i"
	@echo "... Scanner/Scanner.s"
	@echo "... Scanner/SymtabTest.o"
	@echo "... Scanner/SymtabTest.i"
	@echo "... Scanner/SymtabTest.s"
	@echo "... Scanner/Symtable.o"
	@echo "... Scanner/Symtable.i"
	@echo "... Scanner/Symtable.s"
	@echo "... Scanner/Token.o"
	@echo "... Scanner/Token.i"
	@echo "... Scanner/Token.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

