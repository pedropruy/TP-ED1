#ifndef FILA_HPP
#define FILA_HPP

#include "TipoCelula.hpp"
#include "Analise.hpp"

template<typename TipoItem>
class Fila {
    public:
        Fila(); ~Fila();
        int Get_Tamanho() const;
        void Enfileira(const TipoItem& item);
        TipoItem Desenfileira();
        void Imprime();
        void Limpa();
        
        Analise Get_Analise() const; void Zerar_Analise();
        long long Bytes_Usados() const;
    private:
        mutable Analise ana;
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

        Analise Get_Analise() const; void Zerar_Analise();
        long long Bytes_Usados() const;
    private:
        mutable Analise ana;
        int tamanho;
        TipoCelula<TipoItem>* frente;
        TipoCelula<TipoItem>* tras;
};

#include "../src/Fila.tpp"

#endif