#ifndef CATALOGO_HPP
#define CATALOGO_HPP

#include "Matriz.hpp"

class Catalogo {
    public:
        Catalogo(); ~Catalogo();
        char Trocar_de_Modo(char modo);
        int Get_Tamanho_Atributos() const;
        int Get_Tamanho_Itens() const;
        Analise Get_Analise(); void Zerar_Analise();
        int Get_Celula(int id_i, int id_a) const;
        void Set_Celula(int id_i, int id_a, int valor);
        void Novo_Item(); void Novo_Atributo(); // Cresce l e c da matriz 
        void Remocao_Celula(int id_i, int id_a); // mas coisa que Set(valor = 0)
        void Somar_Linha(int id_i, int* vetor);
        void Percurso_Linha(int id_i, Lista<Consulta>& resultados) const;
        void Percurso_Coluna(int id_a, Lista<Consulta>& resultados) const;
        //double Produto_Interno(int id_i, const double* vetor_build) const;
        void Imprime() const;
    private:
        Matriz* matriz;
};

#endif