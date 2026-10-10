#ifndef TIPOCELULA_HPP
#define TIPOCELULA_HPP

template<typename TipoItem>
class Fila;

template<typename TipoItem>
class Pilha;

template<typename TipoItem>
class TipoCelula {
    public:
        TipoCelula();

    private:
        TipoItem item;
        TipoCelula<TipoItem>* prox;

        friend class Fila<TipoItem>;
        friend class Pilha<TipoItem>;
};

template<typename TipoItem>
class TipoCelulado {
    public:
        TipoCelulado();

    private:
        TipoItem item;
        TipoItem item;
        TipoCelula<TipoItem>* prox;

        friend class Fila<TipoItem>;
        friend class Pilha<TipoItem>;
};

#include "TipoCelula.tpp"

#endif