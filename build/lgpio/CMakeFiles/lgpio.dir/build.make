# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/don/cmpt433/work/myApps/beatbox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/don/cmpt433/work/myApps/beatbox/build

# Include any dependencies generated for this target.
include lgpio/CMakeFiles/lgpio.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lgpio/CMakeFiles/lgpio.dir/compiler_depend.make

# Include the progress variables for this target.
include lgpio/CMakeFiles/lgpio.dir/progress.make

# Include the compile flags for this target's objects.
include lgpio/CMakeFiles/lgpio.dir/flags.make

lgpio/CMakeFiles/lgpio.dir/codegen:
.PHONY : lgpio/CMakeFiles/lgpio.dir/codegen

lgpio/CMakeFiles/lgpio.dir/lgCtx.c.o: lgpio/CMakeFiles/lgpio.dir/flags.make
lgpio/CMakeFiles/lgpio.dir/lgCtx.c.o: /home/don/cmpt433/work/myApps/beatbox/lgpio/lgCtx.c
lgpio/CMakeFiles/lgpio.dir/lgCtx.c.o: lgpio/CMakeFiles/lgpio.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/don/cmpt433/work/myApps/beatbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lgpio/CMakeFiles/lgpio.dir/lgCtx.c.o"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lgpio/CMakeFiles/lgpio.dir/lgCtx.c.o -MF CMakeFiles/lgpio.dir/lgCtx.c.o.d -o CMakeFiles/lgpio.dir/lgCtx.c.o -c /home/don/cmpt433/work/myApps/beatbox/lgpio/lgCtx.c

lgpio/CMakeFiles/lgpio.dir/lgCtx.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lgpio.dir/lgCtx.c.i"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/don/cmpt433/work/myApps/beatbox/lgpio/lgCtx.c > CMakeFiles/lgpio.dir/lgCtx.c.i

lgpio/CMakeFiles/lgpio.dir/lgCtx.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lgpio.dir/lgCtx.c.s"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/don/cmpt433/work/myApps/beatbox/lgpio/lgCtx.c -o CMakeFiles/lgpio.dir/lgCtx.c.s

lgpio/CMakeFiles/lgpio.dir/lgDbg.c.o: lgpio/CMakeFiles/lgpio.dir/flags.make
lgpio/CMakeFiles/lgpio.dir/lgDbg.c.o: /home/don/cmpt433/work/myApps/beatbox/lgpio/lgDbg.c
lgpio/CMakeFiles/lgpio.dir/lgDbg.c.o: lgpio/CMakeFiles/lgpio.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/don/cmpt433/work/myApps/beatbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lgpio/CMakeFiles/lgpio.dir/lgDbg.c.o"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lgpio/CMakeFiles/lgpio.dir/lgDbg.c.o -MF CMakeFiles/lgpio.dir/lgDbg.c.o.d -o CMakeFiles/lgpio.dir/lgDbg.c.o -c /home/don/cmpt433/work/myApps/beatbox/lgpio/lgDbg.c

lgpio/CMakeFiles/lgpio.dir/lgDbg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lgpio.dir/lgDbg.c.i"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/don/cmpt433/work/myApps/beatbox/lgpio/lgDbg.c > CMakeFiles/lgpio.dir/lgDbg.c.i

lgpio/CMakeFiles/lgpio.dir/lgDbg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lgpio.dir/lgDbg.c.s"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/don/cmpt433/work/myApps/beatbox/lgpio/lgDbg.c -o CMakeFiles/lgpio.dir/lgDbg.c.s

lgpio/CMakeFiles/lgpio.dir/lgErr.c.o: lgpio/CMakeFiles/lgpio.dir/flags.make
lgpio/CMakeFiles/lgpio.dir/lgErr.c.o: /home/don/cmpt433/work/myApps/beatbox/lgpio/lgErr.c
lgpio/CMakeFiles/lgpio.dir/lgErr.c.o: lgpio/CMakeFiles/lgpio.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/don/cmpt433/work/myApps/beatbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object lgpio/CMakeFiles/lgpio.dir/lgErr.c.o"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lgpio/CMakeFiles/lgpio.dir/lgErr.c.o -MF CMakeFiles/lgpio.dir/lgErr.c.o.d -o CMakeFiles/lgpio.dir/lgErr.c.o -c /home/don/cmpt433/work/myApps/beatbox/lgpio/lgErr.c

lgpio/CMakeFiles/lgpio.dir/lgErr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lgpio.dir/lgErr.c.i"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/don/cmpt433/work/myApps/beatbox/lgpio/lgErr.c > CMakeFiles/lgpio.dir/lgErr.c.i

lgpio/CMakeFiles/lgpio.dir/lgErr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lgpio.dir/lgErr.c.s"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/don/cmpt433/work/myApps/beatbox/lgpio/lgErr.c -o CMakeFiles/lgpio.dir/lgErr.c.s

lgpio/CMakeFiles/lgpio.dir/lgGpio.c.o: lgpio/CMakeFiles/lgpio.dir/flags.make
lgpio/CMakeFiles/lgpio.dir/lgGpio.c.o: /home/don/cmpt433/work/myApps/beatbox/lgpio/lgGpio.c
lgpio/CMakeFiles/lgpio.dir/lgGpio.c.o: lgpio/CMakeFiles/lgpio.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/don/cmpt433/work/myApps/beatbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object lgpio/CMakeFiles/lgpio.dir/lgGpio.c.o"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lgpio/CMakeFiles/lgpio.dir/lgGpio.c.o -MF CMakeFiles/lgpio.dir/lgGpio.c.o.d -o CMakeFiles/lgpio.dir/lgGpio.c.o -c /home/don/cmpt433/work/myApps/beatbox/lgpio/lgGpio.c

lgpio/CMakeFiles/lgpio.dir/lgGpio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lgpio.dir/lgGpio.c.i"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/don/cmpt433/work/myApps/beatbox/lgpio/lgGpio.c > CMakeFiles/lgpio.dir/lgGpio.c.i

lgpio/CMakeFiles/lgpio.dir/lgGpio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lgpio.dir/lgGpio.c.s"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/don/cmpt433/work/myApps/beatbox/lgpio/lgGpio.c -o CMakeFiles/lgpio.dir/lgGpio.c.s

lgpio/CMakeFiles/lgpio.dir/lgHdl.c.o: lgpio/CMakeFiles/lgpio.dir/flags.make
lgpio/CMakeFiles/lgpio.dir/lgHdl.c.o: /home/don/cmpt433/work/myApps/beatbox/lgpio/lgHdl.c
lgpio/CMakeFiles/lgpio.dir/lgHdl.c.o: lgpio/CMakeFiles/lgpio.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/don/cmpt433/work/myApps/beatbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object lgpio/CMakeFiles/lgpio.dir/lgHdl.c.o"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lgpio/CMakeFiles/lgpio.dir/lgHdl.c.o -MF CMakeFiles/lgpio.dir/lgHdl.c.o.d -o CMakeFiles/lgpio.dir/lgHdl.c.o -c /home/don/cmpt433/work/myApps/beatbox/lgpio/lgHdl.c

lgpio/CMakeFiles/lgpio.dir/lgHdl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lgpio.dir/lgHdl.c.i"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/don/cmpt433/work/myApps/beatbox/lgpio/lgHdl.c > CMakeFiles/lgpio.dir/lgHdl.c.i

lgpio/CMakeFiles/lgpio.dir/lgHdl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lgpio.dir/lgHdl.c.s"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/don/cmpt433/work/myApps/beatbox/lgpio/lgHdl.c -o CMakeFiles/lgpio.dir/lgHdl.c.s

lgpio/CMakeFiles/lgpio.dir/lgI2C.c.o: lgpio/CMakeFiles/lgpio.dir/flags.make
lgpio/CMakeFiles/lgpio.dir/lgI2C.c.o: /home/don/cmpt433/work/myApps/beatbox/lgpio/lgI2C.c
lgpio/CMakeFiles/lgpio.dir/lgI2C.c.o: lgpio/CMakeFiles/lgpio.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/don/cmpt433/work/myApps/beatbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object lgpio/CMakeFiles/lgpio.dir/lgI2C.c.o"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lgpio/CMakeFiles/lgpio.dir/lgI2C.c.o -MF CMakeFiles/lgpio.dir/lgI2C.c.o.d -o CMakeFiles/lgpio.dir/lgI2C.c.o -c /home/don/cmpt433/work/myApps/beatbox/lgpio/lgI2C.c

lgpio/CMakeFiles/lgpio.dir/lgI2C.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lgpio.dir/lgI2C.c.i"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/don/cmpt433/work/myApps/beatbox/lgpio/lgI2C.c > CMakeFiles/lgpio.dir/lgI2C.c.i

lgpio/CMakeFiles/lgpio.dir/lgI2C.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lgpio.dir/lgI2C.c.s"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/don/cmpt433/work/myApps/beatbox/lgpio/lgI2C.c -o CMakeFiles/lgpio.dir/lgI2C.c.s

lgpio/CMakeFiles/lgpio.dir/lgNotify.c.o: lgpio/CMakeFiles/lgpio.dir/flags.make
lgpio/CMakeFiles/lgpio.dir/lgNotify.c.o: /home/don/cmpt433/work/myApps/beatbox/lgpio/lgNotify.c
lgpio/CMakeFiles/lgpio.dir/lgNotify.c.o: lgpio/CMakeFiles/lgpio.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/don/cmpt433/work/myApps/beatbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object lgpio/CMakeFiles/lgpio.dir/lgNotify.c.o"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lgpio/CMakeFiles/lgpio.dir/lgNotify.c.o -MF CMakeFiles/lgpio.dir/lgNotify.c.o.d -o CMakeFiles/lgpio.dir/lgNotify.c.o -c /home/don/cmpt433/work/myApps/beatbox/lgpio/lgNotify.c

lgpio/CMakeFiles/lgpio.dir/lgNotify.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lgpio.dir/lgNotify.c.i"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/don/cmpt433/work/myApps/beatbox/lgpio/lgNotify.c > CMakeFiles/lgpio.dir/lgNotify.c.i

lgpio/CMakeFiles/lgpio.dir/lgNotify.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lgpio.dir/lgNotify.c.s"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/don/cmpt433/work/myApps/beatbox/lgpio/lgNotify.c -o CMakeFiles/lgpio.dir/lgNotify.c.s

lgpio/CMakeFiles/lgpio.dir/lgPthAlerts.c.o: lgpio/CMakeFiles/lgpio.dir/flags.make
lgpio/CMakeFiles/lgpio.dir/lgPthAlerts.c.o: /home/don/cmpt433/work/myApps/beatbox/lgpio/lgPthAlerts.c
lgpio/CMakeFiles/lgpio.dir/lgPthAlerts.c.o: lgpio/CMakeFiles/lgpio.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/don/cmpt433/work/myApps/beatbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object lgpio/CMakeFiles/lgpio.dir/lgPthAlerts.c.o"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lgpio/CMakeFiles/lgpio.dir/lgPthAlerts.c.o -MF CMakeFiles/lgpio.dir/lgPthAlerts.c.o.d -o CMakeFiles/lgpio.dir/lgPthAlerts.c.o -c /home/don/cmpt433/work/myApps/beatbox/lgpio/lgPthAlerts.c

lgpio/CMakeFiles/lgpio.dir/lgPthAlerts.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lgpio.dir/lgPthAlerts.c.i"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/don/cmpt433/work/myApps/beatbox/lgpio/lgPthAlerts.c > CMakeFiles/lgpio.dir/lgPthAlerts.c.i

lgpio/CMakeFiles/lgpio.dir/lgPthAlerts.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lgpio.dir/lgPthAlerts.c.s"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/don/cmpt433/work/myApps/beatbox/lgpio/lgPthAlerts.c -o CMakeFiles/lgpio.dir/lgPthAlerts.c.s

lgpio/CMakeFiles/lgpio.dir/lgPthTx.c.o: lgpio/CMakeFiles/lgpio.dir/flags.make
lgpio/CMakeFiles/lgpio.dir/lgPthTx.c.o: /home/don/cmpt433/work/myApps/beatbox/lgpio/lgPthTx.c
lgpio/CMakeFiles/lgpio.dir/lgPthTx.c.o: lgpio/CMakeFiles/lgpio.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/don/cmpt433/work/myApps/beatbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object lgpio/CMakeFiles/lgpio.dir/lgPthTx.c.o"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lgpio/CMakeFiles/lgpio.dir/lgPthTx.c.o -MF CMakeFiles/lgpio.dir/lgPthTx.c.o.d -o CMakeFiles/lgpio.dir/lgPthTx.c.o -c /home/don/cmpt433/work/myApps/beatbox/lgpio/lgPthTx.c

lgpio/CMakeFiles/lgpio.dir/lgPthTx.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lgpio.dir/lgPthTx.c.i"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/don/cmpt433/work/myApps/beatbox/lgpio/lgPthTx.c > CMakeFiles/lgpio.dir/lgPthTx.c.i

lgpio/CMakeFiles/lgpio.dir/lgPthTx.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lgpio.dir/lgPthTx.c.s"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/don/cmpt433/work/myApps/beatbox/lgpio/lgPthTx.c -o CMakeFiles/lgpio.dir/lgPthTx.c.s

lgpio/CMakeFiles/lgpio.dir/lgSerial.c.o: lgpio/CMakeFiles/lgpio.dir/flags.make
lgpio/CMakeFiles/lgpio.dir/lgSerial.c.o: /home/don/cmpt433/work/myApps/beatbox/lgpio/lgSerial.c
lgpio/CMakeFiles/lgpio.dir/lgSerial.c.o: lgpio/CMakeFiles/lgpio.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/don/cmpt433/work/myApps/beatbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object lgpio/CMakeFiles/lgpio.dir/lgSerial.c.o"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lgpio/CMakeFiles/lgpio.dir/lgSerial.c.o -MF CMakeFiles/lgpio.dir/lgSerial.c.o.d -o CMakeFiles/lgpio.dir/lgSerial.c.o -c /home/don/cmpt433/work/myApps/beatbox/lgpio/lgSerial.c

lgpio/CMakeFiles/lgpio.dir/lgSerial.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lgpio.dir/lgSerial.c.i"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/don/cmpt433/work/myApps/beatbox/lgpio/lgSerial.c > CMakeFiles/lgpio.dir/lgSerial.c.i

lgpio/CMakeFiles/lgpio.dir/lgSerial.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lgpio.dir/lgSerial.c.s"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/don/cmpt433/work/myApps/beatbox/lgpio/lgSerial.c -o CMakeFiles/lgpio.dir/lgSerial.c.s

lgpio/CMakeFiles/lgpio.dir/lgSPI.c.o: lgpio/CMakeFiles/lgpio.dir/flags.make
lgpio/CMakeFiles/lgpio.dir/lgSPI.c.o: /home/don/cmpt433/work/myApps/beatbox/lgpio/lgSPI.c
lgpio/CMakeFiles/lgpio.dir/lgSPI.c.o: lgpio/CMakeFiles/lgpio.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/don/cmpt433/work/myApps/beatbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object lgpio/CMakeFiles/lgpio.dir/lgSPI.c.o"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lgpio/CMakeFiles/lgpio.dir/lgSPI.c.o -MF CMakeFiles/lgpio.dir/lgSPI.c.o.d -o CMakeFiles/lgpio.dir/lgSPI.c.o -c /home/don/cmpt433/work/myApps/beatbox/lgpio/lgSPI.c

lgpio/CMakeFiles/lgpio.dir/lgSPI.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lgpio.dir/lgSPI.c.i"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/don/cmpt433/work/myApps/beatbox/lgpio/lgSPI.c > CMakeFiles/lgpio.dir/lgSPI.c.i

lgpio/CMakeFiles/lgpio.dir/lgSPI.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lgpio.dir/lgSPI.c.s"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/don/cmpt433/work/myApps/beatbox/lgpio/lgSPI.c -o CMakeFiles/lgpio.dir/lgSPI.c.s

lgpio/CMakeFiles/lgpio.dir/lgThread.c.o: lgpio/CMakeFiles/lgpio.dir/flags.make
lgpio/CMakeFiles/lgpio.dir/lgThread.c.o: /home/don/cmpt433/work/myApps/beatbox/lgpio/lgThread.c
lgpio/CMakeFiles/lgpio.dir/lgThread.c.o: lgpio/CMakeFiles/lgpio.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/don/cmpt433/work/myApps/beatbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object lgpio/CMakeFiles/lgpio.dir/lgThread.c.o"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lgpio/CMakeFiles/lgpio.dir/lgThread.c.o -MF CMakeFiles/lgpio.dir/lgThread.c.o.d -o CMakeFiles/lgpio.dir/lgThread.c.o -c /home/don/cmpt433/work/myApps/beatbox/lgpio/lgThread.c

lgpio/CMakeFiles/lgpio.dir/lgThread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lgpio.dir/lgThread.c.i"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/don/cmpt433/work/myApps/beatbox/lgpio/lgThread.c > CMakeFiles/lgpio.dir/lgThread.c.i

lgpio/CMakeFiles/lgpio.dir/lgThread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lgpio.dir/lgThread.c.s"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/don/cmpt433/work/myApps/beatbox/lgpio/lgThread.c -o CMakeFiles/lgpio.dir/lgThread.c.s

lgpio/CMakeFiles/lgpio.dir/lgUtil.c.o: lgpio/CMakeFiles/lgpio.dir/flags.make
lgpio/CMakeFiles/lgpio.dir/lgUtil.c.o: /home/don/cmpt433/work/myApps/beatbox/lgpio/lgUtil.c
lgpio/CMakeFiles/lgpio.dir/lgUtil.c.o: lgpio/CMakeFiles/lgpio.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/don/cmpt433/work/myApps/beatbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object lgpio/CMakeFiles/lgpio.dir/lgUtil.c.o"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lgpio/CMakeFiles/lgpio.dir/lgUtil.c.o -MF CMakeFiles/lgpio.dir/lgUtil.c.o.d -o CMakeFiles/lgpio.dir/lgUtil.c.o -c /home/don/cmpt433/work/myApps/beatbox/lgpio/lgUtil.c

lgpio/CMakeFiles/lgpio.dir/lgUtil.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lgpio.dir/lgUtil.c.i"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/don/cmpt433/work/myApps/beatbox/lgpio/lgUtil.c > CMakeFiles/lgpio.dir/lgUtil.c.i

lgpio/CMakeFiles/lgpio.dir/lgUtil.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lgpio.dir/lgUtil.c.s"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/don/cmpt433/work/myApps/beatbox/lgpio/lgUtil.c -o CMakeFiles/lgpio.dir/lgUtil.c.s

# Object files for target lgpio
lgpio_OBJECTS = \
"CMakeFiles/lgpio.dir/lgCtx.c.o" \
"CMakeFiles/lgpio.dir/lgDbg.c.o" \
"CMakeFiles/lgpio.dir/lgErr.c.o" \
"CMakeFiles/lgpio.dir/lgGpio.c.o" \
"CMakeFiles/lgpio.dir/lgHdl.c.o" \
"CMakeFiles/lgpio.dir/lgI2C.c.o" \
"CMakeFiles/lgpio.dir/lgNotify.c.o" \
"CMakeFiles/lgpio.dir/lgPthAlerts.c.o" \
"CMakeFiles/lgpio.dir/lgPthTx.c.o" \
"CMakeFiles/lgpio.dir/lgSerial.c.o" \
"CMakeFiles/lgpio.dir/lgSPI.c.o" \
"CMakeFiles/lgpio.dir/lgThread.c.o" \
"CMakeFiles/lgpio.dir/lgUtil.c.o"

# External object files for target lgpio
lgpio_EXTERNAL_OBJECTS =

lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/lgCtx.c.o
lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/lgDbg.c.o
lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/lgErr.c.o
lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/lgGpio.c.o
lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/lgHdl.c.o
lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/lgI2C.c.o
lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/lgNotify.c.o
lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/lgPthAlerts.c.o
lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/lgPthTx.c.o
lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/lgSerial.c.o
lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/lgSPI.c.o
lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/lgThread.c.o
lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/lgUtil.c.o
lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/build.make
lgpio/liblgpio.a: lgpio/CMakeFiles/lgpio.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/don/cmpt433/work/myApps/beatbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking C static library liblgpio.a"
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && $(CMAKE_COMMAND) -P CMakeFiles/lgpio.dir/cmake_clean_target.cmake
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lgpio.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lgpio/CMakeFiles/lgpio.dir/build: lgpio/liblgpio.a
.PHONY : lgpio/CMakeFiles/lgpio.dir/build

lgpio/CMakeFiles/lgpio.dir/clean:
	cd /home/don/cmpt433/work/myApps/beatbox/build/lgpio && $(CMAKE_COMMAND) -P CMakeFiles/lgpio.dir/cmake_clean.cmake
.PHONY : lgpio/CMakeFiles/lgpio.dir/clean

lgpio/CMakeFiles/lgpio.dir/depend:
	cd /home/don/cmpt433/work/myApps/beatbox/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/don/cmpt433/work/myApps/beatbox /home/don/cmpt433/work/myApps/beatbox/lgpio /home/don/cmpt433/work/myApps/beatbox/build /home/don/cmpt433/work/myApps/beatbox/build/lgpio /home/don/cmpt433/work/myApps/beatbox/build/lgpio/CMakeFiles/lgpio.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : lgpio/CMakeFiles/lgpio.dir/depend

