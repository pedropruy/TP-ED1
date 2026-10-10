#ifndef PILHA_HPP
#define PILHA_HPP

#include "TipoCelula.hpp"

template<typename TipoItem>
class Pilha {
    public:
        Pilha(); ~Pilha();
        int Get_Tamanho();
        void Empilha(TipoItem item);
        TipoItem Desempilha();
        void Limpa();
    private:
        TipoCelula<TipoItem>* topo;
        int tamanho;
};
// O(n) = Destrutor e Limpa (mas mesmo assim é melhor implementação)

#include "Pilha.tpp"

#endif