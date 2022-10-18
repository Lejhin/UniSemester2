SRC_DIR = Aufgaben/Blatt3/3_2

BUILD_DIR = $(SRC_DIR)
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
INCLUDE =  -I Include
LIB = -L Lib 
GTEST = -lgtest -lgtest_main -lpthread -L/usr/lib

all:
	$(CC) $(INCLUDE) $(LIB) $(SRC_FILES) -o $(BUILD_DIR)/run.exe
gtest: 
	$(CC) $(INCLUDE) $(LIB) $(SRC_FILES) $(GTEST) -o $(BUILD_DIR)/run.exe


clean: 
	 $(RM) run



