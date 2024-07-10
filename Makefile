SRC = src

INPUTS = $(SRC)/main.cpp $(SRC)/soundDevice.cpp $(SRC)/soundBuffer.cpp $(SRC)/alHelper.cpp

CXX = clang++

CXXFLAGS = -std=c++23 -static 

INCLUDE =  -I./Include
LIBS = -L./Lib
LINKS = -lvulkan-1 -lOpenAL32  -lglfw3 -lshell32 -luser32 -lGdi32 -lucrt -lsndfile
LDFLAG = -Xlinker /NODEFAULTLIB:msvcrt.lib -Xlinker /NODEFAULTLIB:libucrt.lib

TARGET = foo.exe
all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(INPUTS) $(INCLUDE) $(LIBS) $(LINKS) $(LDFLAG)

run:
	./$(TARGET)


