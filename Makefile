SRC = src
SND = $(SRC)/snd
GFX = $(SRC)/gfx
PROC_SND= $(SND)/procedural

INPUTS = $(SRC)/main.cpp $(SND)/soundDevice.cpp $(SND)/soundBuffer.cpp $(SND)/alHelper.cpp $(SND)/soundSource.cpp $(GFX)/window.cpp $(SND)/soundGen.cpp $(PROC_SND)/waveforms.cpp

CXX = clang++

CXXFLAGS = -std=c++23 -static

INCLUDE =  -I./Include
LIBS = -L./Lib
LINKS = -lvulkan-1 -lOpenAL32  -lglfw3 -lshell32 -luser32 -lGdi32 -lucrt -lglm -lsndfile -llibmp3lame-static -llibmpghip-static -lmpg123 -logg -lopus -lFLAC  -lvorbis -lShLwApi
LDFLAG = -Xlinker /NODEFAULTLIB:msvcrt.lib -Xlinker /NODEFAULTLIB:libucrt.lib

TARGET = foo.exe
all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(INPUTS) $(INCLUDE) $(LIBS) $(LINKS) $(LDFLAG)

run:
	./$(TARGET)


