#ifndef CATALOGO_HPP
#define CATALOGO_HPP

#include "Lista.hpp"
#include "Fila.hpp"
#include "Matriz.hpp"
#include "Item.hpp"
#include "Atributo.hpp"
#include "Aventureiro.hpp"

class Catalogo {
    public:
        void Modo(char modo); // E
        void Cadastro_Atributo(std::string nome); // A
        void Cadastro_Item(std::string nome); // I
        void Definir_Modificador(int id_i, int id_a, int valor); // M
        void Cadastro_Aventureiro(std::string nome); // H
        void Encomenda(int id_a, int id_i); // F
        void Turnos_de_Trabalho(int turnos); // Z
        void Desequipar(int id_a); // D
        void Consulta_Item(int id_i); // LI
        void Consulta_Atributo(int id_a); // LA
        void Consulta_Build(int id_a); // LH
        void Consulta_Recomendacao(); // Q
    private:
        Lista<Item> itens;
        Lista<Atributo> atributos;
        Lista<Aventureiro> aventureiros;
        Fila<int> encomendas;
        MatrizCOO* matriz_L;
        MatrizEncadeada* matriz_T;
        void Poder();
        void Equilibrio();
        void Sinergia();
};

#endif