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
        void Limpa();
    private:
        void Copia(const Pilha& p);
        TipoCelula<TipoItem>* topo;
        int tamanho;
};
// O(n) = Destrutor e Limpa (mas mesmo assim é melhor implementação)

#include "Pilha.tpp"

#endif