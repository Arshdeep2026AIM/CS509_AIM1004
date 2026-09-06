# 1. Define compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

# Define subdirectories
SUBDIRS = assignment_01 assignment_02 assignment_03 assignment_04

.PHONY: all clean run $(SUBDIRS)

# Default target: builds all subdirectories AND the standalone binary
all: $(SUBDIRS) common_wrapper/wrapper.exe

# Rule to build subdirectories recursively
$(SUBDIRS):
	$(MAKE) -C $@

# Rule for standalone wrapper (Uses Windows path syntax)
common_wrapper/wrapper.exe: common_wrapper/wrapper.cpp | $(SUBDIRS)
	$(CXX) $(CXXFLAGS) -o $@ $<

run: common_wrapper/wrapper.exe
	common_wrapper\wrapper.exe

# Clean target formatted for Windows CMD (fixes "dir was unexpected" error)
clean:
	for %%d in ($(SUBDIRS)) do $(MAKE) -C %%d clean
	-del /f /q common_wrapper\wrapper.exe 2>NUL