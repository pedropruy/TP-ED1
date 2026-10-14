#ifndef MATRIZ_HPP
#define MATRIZ_HPP

typedef int valor;
#include "Lista.hpp"

struct Celula {
    int lin, col;
    valor val;
    Celula* proxLin;  // proxima celula na mesma linha (coluna maior)
    Celula* proxCol;  // proxima celula na mesma coluna (linha maior)
};

class MatrizEncadeada {
    public:
        MatrizEncadeada(int linhas, int colunas); ~MatrizEncadeada();
        valor Get(int i, int j) const;
        void Set(int i, int j, valor v);
        void Adicionar_Linha(); void Adicionar_Coluna();
        valor Soma_Coluna(int j) const;  // percorre so a lista da coluna j
        valor* Produto(const valor* v, int dim_v);
        void Imprime();
    private:
        // Reorganizar a implementação para usar Lista
        // contadores l e c foram removidos pois Lista já armazena esses valores
        int tamanho;
        Lista<Celula*>* cabLin;  // cabLin.Get_Item(i): celula cabeca da linha i
        Lista<Celula*>* cabCol;  // cabCol.Get_Item(j): celula cabeca da coluna j
        Celula* AntLinha(int i, int j) const;
        Celula* AntColuna(int i, int j) const;
};

#endif