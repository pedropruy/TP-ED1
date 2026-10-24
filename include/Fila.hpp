#ifndef FILA_HPP
#define FILA_HPP

#include "TipoCelula.hpp"

template<typename TipoItem>
class Fila {
    public:
        Fila(); ~Fila();
        int Get_Tamanho() const;
        void Enfileira(const TipoItem& item);
        TipoItem Desenfileira();
        void Imprime();
        void Limpa();
    private:
        int tamanho;
        int capacidade;
        int frente;
        int tras;
        TipoItem* itens;
        void Dobrar_Tamanho();
};

template<typename TipoItem>
class FilaEncadeada {
    public:
        FilaEncadeada(); ~FilaEncadeada();
        int Get_Tamanho() const;
        void Enfileira(const TipoItem& item);
        TipoItem Desenfileira();
        void Imprime();
        void Limpa();
    private:
        int tamanho;
        TipoCelula<TipoItem>* frente;
        TipoCelula<TipoItem>* tras;
};

#include "../src/Fila.tpp"

#endif