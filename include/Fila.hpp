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
        void Limpa();
    private:
        TipoCelula<TipoItem>* frente;
        TipoCelula<TipoItem>* tras;
        int tamanho;
};

#include "Fila.tpp"

#endif