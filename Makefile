CXX = g++
CXXFLAGS = -std=c++11 -Wall -I./include 
#-fsanitize=address -g -fno-omit-frame-pointer

SRC_DIR = ./src
INCLUDE_DIR = ./include
OBJ_DIR = ./obj
OUT_DIR = ./bin

TARGET = $(OUT_DIR)/tp1.out

OBJ = $(OBJ_DIR)/main.o \
	  $(OBJ_DIR)/Item.o \
	  $(OBJ_DIR)/Atributo.o \
	  $(OBJ_DIR)/Aventureiro.o \
	  $(OBJ_DIR)/Matriz.o

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

$(OBJ_DIR)/Item.o: $(SRC_DIR)/Item.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/Atributo.o: $(SRC_DIR)/Atributo.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/Aventureiro.o: $(SRC_DIR)/Aventureiro.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/Matriz.o: $(SRC_DIR)/Matriz.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(TARGET)

run: $(TARGET)
	$(TARGET)