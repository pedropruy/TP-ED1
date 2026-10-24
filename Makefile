CC = g++
CFLAGS = -std=c++11 -Wall -fsanitize=address -g -fno-omit-frame-pointer

SRC_DIR = ./src
INCLUDE_DIR = ./include
OBJ_DIR = ./obj
OUT_DIR = ./bin

TARGET = $(OUT_DIR)/tp1.out

OBJ = $(OBJ_DIR)/main.o \
	  $(OBJ_DIR)/Item.o \
	  $(OBJ_DIR)/Atributo.o \
	  $(OBJ_DIR)/Aventureiro.o \
	  $(OBJ_DIR)/Matriz.o \
	  $(OBJ_DIR)/Catalogo.o \
	  $(OBJ_DIR)/Forja.o \
	  $(OBJ_DIR)/Entrada.o \
	  $(OBJ_DIR)/Ordenacao.o

all: $(TARGET)

$(OBJ_DIR)/Item.o: $(INCLUDE_DIR)/Item.hpp $(SRC_DIR)/Item.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Item.cpp -o $(OBJ_DIR)/Item.o

$(OBJ_DIR)/Atributo.o: $(INCLUDE_DIR)/Atributo.hpp $(SRC_DIR)/Atributo.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Atributo.cpp -o $(OBJ_DIR)/Atributo.o

$(OBJ_DIR)/Aventureiro.o: $(INCLUDE_DIR)/Aventureiro.hpp $(SRC_DIR)/Aventureiro.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Aventureiro.cpp -o $(OBJ_DIR)/Aventureiro.o

$(OBJ_DIR)/Matriz.o: $(SRC_DIR)/Matriz_COO.cpp $(SRC_DIR)/Matriz_CSR.cpp $(SRC_DIR)/Matriz_Encadeada.cpp $(INCLUDE_DIR)/Matriz.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Matriz_COO.cpp -o $(OBJ_DIR)/Matriz_COO.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Matriz_CSR.cpp -o $(OBJ_DIR)/Matriz_CSR.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Matriz_Encadeada.cpp -o $(OBJ_DIR)/Matriz_Encadeada.o
	ld -r $(OBJ_DIR)/Matriz_COO.o $(OBJ_DIR)/Matriz_CSR.o $(OBJ_DIR)/Matriz_Encadeada.o -o $@
	rm $(OBJ_DIR)/Matriz_COO.o $(OBJ_DIR)/Matriz_CSR.o $(OBJ_DIR)/Matriz_Encadeada.o


$(OBJ_DIR)/Catalogo.o: $(INCLUDE_DIR)/Catalogo.hpp $(SRC_DIR)/Catalogo.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Catalogo.cpp -o $(OBJ_DIR)/Catalogo.o

$(OBJ_DIR)/Forja.o: $(INCLUDE_DIR)/Forja.hpp $(SRC_DIR)/Forja.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Forja.cpp -o $(OBJ_DIR)/Forja.o

$(OBJ_DIR)/Entrada.o: $(INCLUDE_DIR)/Entrada.hpp $(SRC_DIR)/Entrada.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Entrada.cpp -o $(OBJ_DIR)/Entrada.o

$(OBJ_DIR)/Ordenacao.o: $(INCLUDE_DIR)/Ordenacao.hpp $(SRC_DIR)/Ordenacao.cpp
	${CC} ${CFLAGS} -c $(SRC_DIR)/Ordenacao.cpp -o $(OBJ_DIR)/Ordenacao.o

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp 
	${CC} ${CFLAGS} -c $(SRC_DIR)/main.cpp  -o $(OBJ_DIR)/main.o

$(TARGET): $(OBJ)
	${CC} ${CFLAGS} $(OBJ) -o $(TARGET)

# Rule for cleaning files generated during compilation.
# Call 'make clean' to use it
clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(TARGET)

run: $(TARGET)
	$(TARGET)