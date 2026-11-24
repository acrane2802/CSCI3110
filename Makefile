CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRCS = main.cpp Record.cpp RecordOperations.cpp
OBJS = $(SRCS:.cpp=.o)

# Detect Windows vs. Unix-like environments (Linux/macOS/MSYS/Git Bash)
ifeq ($(OS),Windows_NT)
	TARGET = CSCI3110.exe
	# Check if running inside a Unix-style shell on Windows (e.g., Git Bash/MSYS2)
	ifneq ($(findstring /,$(SHELL)),)
		RM = rm -f
		FIX_PATH = $1
	else
		RM = del /Q /F
		FIX_PATH = $(subst /,\,$1)
	endif
else
	TARGET = CSCI3110
	RM = rm -f
	FIX_PATH = $1
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Record.h RecordOperations.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Record.o: Record.cpp Record.h
	$(CXX) $(CXXFLAGS) -c Record.cpp -o Record.o

RecordOperations.o: RecordOperations.cpp RecordOperations.h Record.h
	$(CXX) $(CXXFLAGS) -c RecordOperations.cpp -o RecordOperations.o

clean:
	$(RM) $(call FIX_PATH,$(OBJS) $(TARGET))

.PHONY: all clean