#ifndef TIPOCELULA_HPP
#define TIPOCELULA_HPP

template<typename TipoItem>
class Fila;
template<typename TipoItem>
class FilaEncadeada;

template<typename TipoItem>
class Pilha;
template<typename TipoItem>
class PilhaEncadeada;

template<typename TipoItem>
class TipoCelula {
    public:
        TipoCelula();

    private:
        TipoItem item;
        TipoCelula<TipoItem>* prox;

        friend class Fila<TipoItem>;
        friend class FilaEncadeada<TipoItem>;
        friend class Pilha<TipoItem>;
        friend class PilhaEncadeada<TipoItem>;
};

#include "../src/TipoCelula.tpp"

#endif