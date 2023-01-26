SRC_DIR = Projekt



BUILD_DIR = $(SRC_DIR)
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
INCLUDE = -I Include #C:\opt\msys\mingw64\include\gtest\gtest.h
LIB =  -L Lib  #C:\opt\msys\mingw64\lib\libgtest.a
GTEST = -lgtest -lgtest_main -pthread
DEBUG = -lm


all:
	$(CC) $(INCLUDE) $(LIB) $(SRC_FILES) -o $(BUILD_DIR)/run.exe
gtest: 
	$(CC) $(INCLUDE) $(LIB) $(SRC_FILES) $(GTEST) -o $(BUILD_DIR)/run.exe

clean: 
	 $(RM) run
main:
	$(CC) $(DEBUG) $(INCLUDE) $(LIB) $(SRC_FILES)  -o main $(DEBUG)
debug: DEBUG = -DDEBUG
debug: main





