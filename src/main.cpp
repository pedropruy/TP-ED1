#include "Fila.hpp"
#include "Pilha.hpp"
#include "Lista.hpp"
#include "Item.hpp"
#include "Atributo.hpp"
#include "Aventureiro.hpp"
#include <iostream>


int main() {
    int tam = 8;

    Fila<Aventureiro> *PI = new Fila<Aventureiro>();

    std::string entrada;
    for(int i = 0; i < tam; i++) {
        std::getline(std::cin >> std::ws, entrada);
        Aventureiro aventureiro(i, entrada);
        for (int j = 0; j <= i; j++)
            aventureiro.Equipar_Item(j);
        PI->Enfileira(aventureiro);
    }

    PI->Desenfileira();

    try{ PI->Imprime();
    } catch (char const* e) { std::cout << e << std::endl; }

    delete PI;

    return 0;
}