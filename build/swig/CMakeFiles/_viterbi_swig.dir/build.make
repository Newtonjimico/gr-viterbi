# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/jagdish/Desktop/gr-viterbi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jagdish/Desktop/gr-viterbi/build

# Include any dependencies generated for this target.
include swig/CMakeFiles/_viterbi_swig.dir/depend.make

# Include the progress variables for this target.
include swig/CMakeFiles/_viterbi_swig.dir/progress.make

# Include the compile flags for this target's objects.
include swig/CMakeFiles/_viterbi_swig.dir/flags.make

swig/viterbi_swigPYTHON_wrap.cxx: /usr/local/include/gnuradio/swig/gnuradio.i
swig/viterbi_swigPYTHON_wrap.cxx: /usr/local/include/gnuradio/swig/gr_extras.i
swig/viterbi_swigPYTHON_wrap.cxx: ../swig/viterbi_swig.i
swig/viterbi_swigPYTHON_wrap.cxx: /usr/local/include/gnuradio/swig/gr_shared_ptr.i
swig/viterbi_swigPYTHON_wrap.cxx: /usr/local/include/gnuradio/swig/gnuradio_swig_bug_workaround.h
swig/viterbi_swigPYTHON_wrap.cxx: /usr/local/include/gnuradio/swig/gr_types.i
swig/viterbi_swigPYTHON_wrap.cxx: swig/viterbi_swig.tag
swig/viterbi_swigPYTHON_wrap.cxx: ../swig/viterbi_swig.i
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jagdish/Desktop/gr-viterbi/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Swig source"
	cd /home/jagdish/Desktop/gr-viterbi/build/swig && /usr/bin/cmake -E make_directory /home/jagdish/Desktop/gr-viterbi/build/swig
	cd /home/jagdish/Desktop/gr-viterbi/build/swig && /usr/bin/swig2.0 -python -fvirtual -modern -keyword -w511 -module viterbi_swig -I/usr/local/include/gnuradio/swig -I/usr/include/python2.7 -I/usr/include/python2.7 -I/usr/include/x86_64-linux-gnu/python2.7 -I/home/jagdish/Desktop/gr-viterbi/swig -I/home/jagdish/Desktop/gr-viterbi/build/swig -outdir /home/jagdish/Desktop/gr-viterbi/build/swig -c++ -I/home/jagdish/Desktop/gr-viterbi/lib -I/home/jagdish/Desktop/gr-viterbi/include -I/home/jagdish/Desktop/gr-viterbi/build/lib -I/home/jagdish/Desktop/gr-viterbi/build/include -I/usr/include -I/usr/include -I/usr/local/include -I/usr/local/include/gnuradio/swig -I/usr/include/python2.7 -I/usr/include/python2.7 -I/usr/include/x86_64-linux-gnu/python2.7 -I/home/jagdish/Desktop/gr-viterbi/swig -I/home/jagdish/Desktop/gr-viterbi/build/swig -o /home/jagdish/Desktop/gr-viterbi/build/swig/viterbi_swigPYTHON_wrap.cxx /home/jagdish/Desktop/gr-viterbi/swig/viterbi_swig.i

swig/viterbi_swig.py: swig/viterbi_swigPYTHON_wrap.cxx

swig/viterbi_swig.tag: swig/viterbi_swig_doc.i
swig/viterbi_swig.tag: swig/_viterbi_swig_swig_tag
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jagdish/Desktop/gr-viterbi/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating viterbi_swig.tag"
	cd /home/jagdish/Desktop/gr-viterbi/build/swig && ./_viterbi_swig_swig_tag
	cd /home/jagdish/Desktop/gr-viterbi/build/swig && /usr/bin/cmake -E touch /home/jagdish/Desktop/gr-viterbi/build/swig/viterbi_swig.tag

swig/viterbi_swig_doc.i: swig/viterbi_swig_doc_swig_docs/xml/index.xml
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jagdish/Desktop/gr-viterbi/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating viterbi_swig_doc.i"
	cd /home/jagdish/Desktop/gr-viterbi/docs/doxygen && /usr/bin/python2 -B /home/jagdish/Desktop/gr-viterbi/docs/doxygen/swig_doc.py /home/jagdish/Desktop/gr-viterbi/build/swig/viterbi_swig_doc_swig_docs/xml /home/jagdish/Desktop/gr-viterbi/build/swig/viterbi_swig_doc.i

swig/viterbi_swig_doc_swig_docs/xml/index.xml: swig/_viterbi_swig_doc_tag
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jagdish/Desktop/gr-viterbi/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating doxygen xml for viterbi_swig_doc docs"
	cd /home/jagdish/Desktop/gr-viterbi/build/swig && ./_viterbi_swig_doc_tag
	cd /home/jagdish/Desktop/gr-viterbi/build/swig && /usr/bin/doxygen /home/jagdish/Desktop/gr-viterbi/build/swig/viterbi_swig_doc_swig_docs/Doxyfile

swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o: swig/CMakeFiles/_viterbi_swig.dir/flags.make
swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o: swig/viterbi_swigPYTHON_wrap.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jagdish/Desktop/gr-viterbi/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o"
	cd /home/jagdish/Desktop/gr-viterbi/build/swig && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o -c /home/jagdish/Desktop/gr-viterbi/build/swig/viterbi_swigPYTHON_wrap.cxx

swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.i"
	cd /home/jagdish/Desktop/gr-viterbi/build/swig && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jagdish/Desktop/gr-viterbi/build/swig/viterbi_swigPYTHON_wrap.cxx > CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.i

swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.s"
	cd /home/jagdish/Desktop/gr-viterbi/build/swig && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jagdish/Desktop/gr-viterbi/build/swig/viterbi_swigPYTHON_wrap.cxx -o CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.s

swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o.requires:
.PHONY : swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o.requires

swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o.provides: swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o.requires
	$(MAKE) -f swig/CMakeFiles/_viterbi_swig.dir/build.make swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o.provides.build
.PHONY : swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o.provides

swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o.provides.build: swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o

# Object files for target _viterbi_swig
_viterbi_swig_OBJECTS = \
"CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o"

# External object files for target _viterbi_swig
_viterbi_swig_EXTERNAL_OBJECTS =

swig/_viterbi_swig.so: swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o
swig/_viterbi_swig.so: swig/CMakeFiles/_viterbi_swig.dir/build.make
swig/_viterbi_swig.so: /usr/lib/x86_64-linux-gnu/libpython2.7.so
swig/_viterbi_swig.so: lib/libgnuradio-viterbi.so
swig/_viterbi_swig.so: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
swig/_viterbi_swig.so: /usr/lib/x86_64-linux-gnu/libboost_system.so
swig/_viterbi_swig.so: /usr/local/lib/libgnuradio-runtime.so
swig/_viterbi_swig.so: swig/CMakeFiles/_viterbi_swig.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared module _viterbi_swig.so"
	cd /home/jagdish/Desktop/gr-viterbi/build/swig && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_viterbi_swig.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
swig/CMakeFiles/_viterbi_swig.dir/build: swig/_viterbi_swig.so
.PHONY : swig/CMakeFiles/_viterbi_swig.dir/build

swig/CMakeFiles/_viterbi_swig.dir/requires: swig/CMakeFiles/_viterbi_swig.dir/viterbi_swigPYTHON_wrap.cxx.o.requires
.PHONY : swig/CMakeFiles/_viterbi_swig.dir/requires

swig/CMakeFiles/_viterbi_swig.dir/clean:
	cd /home/jagdish/Desktop/gr-viterbi/build/swig && $(CMAKE_COMMAND) -P CMakeFiles/_viterbi_swig.dir/cmake_clean.cmake
.PHONY : swig/CMakeFiles/_viterbi_swig.dir/clean

swig/CMakeFiles/_viterbi_swig.dir/depend: swig/viterbi_swigPYTHON_wrap.cxx
swig/CMakeFiles/_viterbi_swig.dir/depend: swig/viterbi_swig.py
swig/CMakeFiles/_viterbi_swig.dir/depend: swig/viterbi_swig.tag
swig/CMakeFiles/_viterbi_swig.dir/depend: swig/viterbi_swig_doc.i
swig/CMakeFiles/_viterbi_swig.dir/depend: swig/viterbi_swig_doc_swig_docs/xml/index.xml
	cd /home/jagdish/Desktop/gr-viterbi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jagdish/Desktop/gr-viterbi /home/jagdish/Desktop/gr-viterbi/swig /home/jagdish/Desktop/gr-viterbi/build /home/jagdish/Desktop/gr-viterbi/build/swig /home/jagdish/Desktop/gr-viterbi/build/swig/CMakeFiles/_viterbi_swig.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : swig/CMakeFiles/_viterbi_swig.dir/depend

