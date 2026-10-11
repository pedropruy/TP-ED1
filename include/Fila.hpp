#ifndef FILA_HPP
#define FILA_HPP

#include "TipoCelula.hpp"

template<typename TipoItem>
class Fila {
    public:
        Fila(); ~Fila();
        int Get_Tamanho() const;
        void Enfileira(TipoItem item);
        TipoItem Desenfileira();
        void Imprime();
        void Limpa();
    private:
        bool encadeada = false;
        int tamanho;
        // Fila Encadeada
        TipoCelula<TipoItem>* celula_frente;
        TipoCelula<TipoItem>* celula_tras;
        // Fila Arranjo
        int capacidade;
        int indice_frente;
        int indice_tras;
        TipoItem* itens;
        void Dobrar_Tamanho();
};

#include "Fila.tpp"

#endif