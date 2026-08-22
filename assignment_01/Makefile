# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

# Define your target executable name here
TARGET = driver/driver

# List your source (.cpp) files here
SRCS = driver/driver.cpp src/gemm.cpp src/mat.cpp

OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe