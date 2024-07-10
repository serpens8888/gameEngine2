SRC = src

INPUTS = $(SRC)/main.cpp

CXX = clang++

CXXFLAGS = -std=c++23 -static

INCLUDE =  -I./Include
LIBS = -L./Lib
LINKS = -lvulkan-1 -lOpenAL32  -lglfw3 -lshell32 -luser32 -lGdi32 -lucrt
LDFLAG = -Xlinker /NODEFAULTLIB:msvcrt.lib -Xlinker /NODEFAULTLIB:libucrt.lib -Xlinker /NODEFAULTLIB:ucrt.lib

TARGET = foo.exe
all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(INPUTS) $(INCLUDE) $(LIBS) $(LINKS) $(LDFLAG)

run:
	./$(TARGET)


