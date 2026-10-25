#ifndef PILHA_HPP
#define PILHA_HPP

#include "TipoCelula.hpp"
#include "Lista.hpp"

template<typename TipoItem>
class Pilha {
    public:
        Pilha(); ~Pilha();
        Pilha(const Pilha &p);
        Pilha& operator= (const Pilha &p);
        int Get_Tamanho() const;
        void Empilha(const TipoItem& item);
        TipoItem Desempilha();
        void Percorrer_Pilha(Lista<TipoItem>& lista) const;
        void Imprime();
        void Limpa();

        Analise Get_Analise() const; void Zerar_Analise();
        long long Bytes_Usados() const;
    private:
        mutable Analise ana;
        bool encadeada = false;
        int tamanho;
        void Copia(const Pilha& p);
        int capacidade;
        TipoItem* itens;
        int topo;
        void Dobrar_Tamanho();
};

template<typename TipoItem>
class PilhaEncadeada {
    public:
        PilhaEncadeada(); ~PilhaEncadeada();
        PilhaEncadeada(const PilhaEncadeada &p);
        PilhaEncadeada& operator= (const PilhaEncadeada &p);
        int Get_Tamanho() const;
        void Empilha(const TipoItem& item);
        TipoItem Desempilha();
        void Percorrer_Pilha(Lista<TipoItem>& lista) const;
        void Imprime();
        void Limpa();
        
        Analise Get_Analise() const; void Zerar_Analise();
        long long Bytes_Usados() const;
    private:
        mutable Analise ana;
        int tamanho;
        void Copia(const PilhaEncadeada& p);
        TipoCelula<TipoItem>* topo;
};

#include "../src/Pilha.tpp"

#endif