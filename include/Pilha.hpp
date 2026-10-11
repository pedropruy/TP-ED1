#ifndef PILHA_HPP
#define PILHA_HPP

#include "TipoCelula.hpp"

template<typename TipoItem>
class Pilha {
    public:
        Pilha(); ~Pilha();
        Pilha(const Pilha &p);
        Pilha& operator= (const Pilha &p);
        int Get_Tamanho() const;
        void Empilha(TipoItem item);
        TipoItem Desempilha();
        void Imprime();
        void Limpa();
    private:
        bool encadeada = true;
        int tamanho;
        void Copia(const Pilha& p);
        // Pilha Encadeada
        TipoCelula<TipoItem>* topoE;
        // Pilha Arranjo
        int capacidade;
        TipoItem* itens;
        int topoA;
        void Dobrar_Tamanho();
};
// O(n) = Destrutor e Limpa (mas mesmo assim é melhor implementação)

#include "Pilha.tpp"

#endif