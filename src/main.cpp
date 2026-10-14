#include "Matriz.hpp"
#include <iostream>

int main() {
    int tam = 8;

    try {
    MatrizCOO m(tam, tam);
    m.Set(0, 0, 3); m.Set(0, 1, 2); m.Set(1, 6, 5);
    m.Set(7, 0, 1); m.Set(3, 3, 3); m.Set(2, 7, 9);
    m.Set(7, 5, 0); m.Set(5, 7, 9); m.Set(7, 7, 8);
    m.Imprime();
    std::cout << "=======================" << std::endl;

    MatrizEncadeada me(tam,tam);
    m.Converter_Matriz(me);
    me.Imprime();
    std::cout << "=======================" << std::endl;

    me.Adicionar_Linha();
    me.Adicionar_Coluna();
    me.Set(8, 5, 3); me.Set(8, 7, 9); me.Set(7, 7, 0);
    me.Imprime();
    std::cout << "=======================" << std::endl;

    MatrizCOO mo(tam+1,tam+1);
    me.Converter_Matriz(mo);
    mo.Imprime();
    std::cout << "=======================" << std::endl;
    } catch (char const* e) { std::cout << e << std::endl; }

    return 0;
}