CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

TARGET = driver/driver

SRCS = driver/driver.cpp src/vertexColor.cpp src/pageRank.cpp ../assignment_01/src/csr.cpp

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
	-del /f /q $(subst /,\,$(OBJS) $(TARGET)) 2>NUL