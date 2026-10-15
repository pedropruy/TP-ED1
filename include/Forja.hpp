#ifndef FORJA_HPP
#define FORJA_HPP

#include "Lista.hpp"
#include "Fila.hpp"
#include "Item.hpp"
#include "Atributo.hpp"
#include "Aventureiro.hpp"
#include "Catalogo.hpp"

struct Pedido { int id_aventureiro; int id_item; };

class Forja {
    public:
        // Devolvendo const std::string& para evitar cópia desnecessária de strings
        const std::string& Nome_Item(int ind);
        const std::string& Nome_Atributo(int ind);
        const std::string& Nome_Aventureiro(int ind);
        char Modo(char modo); // E
        int Cadastro_Atributo(const std::string& nome); // A
        int Cadastro_Item(const std::string& nome); // I
        void Definir_Modificador(int id_i, int id_a, int valor); // M
        int Cadastro_Aventureiro(const std::string& nome); // H
        int Adiciona_Encomenda(int id_v, int id_i); // F
        int Turnos_de_Trabalho(int turnos, Lista<Pedido>& atendidas); // Z
        int Desequipar(int id_v); // D
        void Consulta_Item(int id_i, Lista<Consulta>& lista) const; // LI
        void Consulta_Atributo(int id_a, Lista<Consulta>& lista) const; // LA
        void Consulta_Atributo_Intervalo(int id_a, int min, int max, Lista<Consulta>& lista) const; // LF
        Lista<Consulta> Consulta_Build(int id_v) const; // LH
        Lista<Consulta> Consulta_Recomendacao(int id_a, int n, Lista<std::string>& metricas,
                                   Lista<double>& pesos); // Q
        void Imprime() const;
    private:
        Lista<Item> itens;
        Lista<Atributo> atributos;
        Lista<Aventureiro> aventureiros;
        Fila<Pedido> encomendas;
        Catalogo catalogo;
        double Poder(int id_i);
        double Equilibrio(int id_i);
        double Sinergia(int id_i, int id_v);
};

#endif
