CXX = g++
CXXFLAGS = -std=c++11 -Iinclude

SOURCES = src/main.cpp src/MemoryManager.cpp src/Cache.cpp src/Paging.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = memsim

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET)