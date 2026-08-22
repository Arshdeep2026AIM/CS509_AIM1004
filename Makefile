# 1. Define your compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

# Define subdirectories
SUBDIRS = assignment_01 assignment_02 assignment_03

.PHONY: all clean run $(SUBDIRS)

# Default target: builds all subdirectories AND the standalone binary
all: $(SUBDIRS) $(STANDALONE_TARGET)

# Rule to build subdirectories recursively
$(SUBDIRS):
	$(MAKE) -C $@


# Clean all subdirectories AND remove the standalone executable
clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done