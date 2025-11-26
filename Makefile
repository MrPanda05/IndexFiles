CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Recursively find sources and include dirs
SRC := main.cpp $(shell dir /s /b src\*.cpp | findstr /i /v /c:".git" /c:".svn")
SRC := $(subst \,/,$(SRC))
INCLUDE_DIRS := $(shell dir /s /b /ad includes)
INCFLAGS := $(foreach dir,$(INCLUDE_DIRS),-I$(dir))

# Objects in root, flattened
OBJ := $(notdir $(SRC:.cpp=.o))

TARGET = main.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $^ -o $@

# Generic rule for .o from any .cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

# For src/ files
%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

# For deeper src/
%.o: src/**/%.cpp
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

clean:
	del /Q *.o 2>nul || true
	del /Q $(TARGET) 2>nul || true
