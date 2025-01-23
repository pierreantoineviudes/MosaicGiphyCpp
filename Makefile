CXX = nvcc
CXXFLAGS = -std=c++17 -Iinclude
SOURCES = src/main.cu src/imageProcessor.cu src/directoryUtils.cpp
EXECUTABLE = image_processor

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
