#include "Fila.hpp"
#include "Pilha.hpp"
#include "Item.hpp"
#include <iostream>

int main() {
    int tam = 10;
    Fila<Item*> *filha = new Fila<Item*>();
    //Pilha<int> *pilha = new Pilha<int>();

    std::string entrada; 
    for(int i = 0; i < tam; i++) {
        std::getline(std::cin >> std::ws, entrada);
        Item* item = new Item(i, entrada);
        filha->Enfileira(item);
        //pilha->Empilha(i);
    }

    for(int i = 0; i < tam; i++) {
        std::cout << filha->Desenfileira()->Get_Nome() << std::endl;
        //std::cout << pilha->Desempilha() << std::endl;
    }

    delete filha;
    //delete pilha;

    return 0;
}