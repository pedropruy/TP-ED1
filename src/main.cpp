#include "Fila.hpp"
#include "Pilha.hpp"
#include "Lista.hpp"
#include "Item.hpp"
#include "Atributo.hpp"
#include "Aventureiro.hpp"
#include <iostream>

int main() {
    int tam = 8;
    Lista<Item> *LI = new Lista<Item>();
    Lista<Atributo> *LA = new Lista<Atributo>(); 
    Lista<Aventureiro> *LE = new Lista<Aventureiro>(); 

    std::string entrada;
    for(int i = 0; i < tam; i++) {
        std::getline(std::cin >> std::ws, entrada);
        Item item(i, entrada);
        LI->Insere_Final(item);
        Atributo atributo(i, entrada);
        LA->Insere_Final(atributo);
        Aventureiro aventureiro(i, entrada);
        for (int j = 0; j <= i; j++)
            aventureiro.Equipar_Item(j);
        LE->Insere_Final(aventureiro);
    }

    try{ LI->Imprime();
         LA->Imprime();
         LE->Imprime();
    } catch (char const* e) { std::cout << e << std::endl; }

    delete LI;
    delete LA;
    delete LE;

    return 0;
}