#ifndef MATRIZ_HPP
#define MATRIZ_HPP

typedef int valor;
#include "Lista.hpp"

/* A implementação das matrizes irá utilizar lin = id_item, col = id_atributo, val = modificador */

struct Tripleta { int lin, col; valor val; };
class MatrizCOO {
    public:
        MatrizCOO(int linhas, int colunas);
        // ~MatrizCOO();
        valor Get(int i, int j) const;
        void Set(int i, int j, valor v);
        void Adicionar_Linha(); void Adicionar_Coluna();
        void Imprime() const;
    private:
        int l, c;    // dimensoes da matriz representada
        Lista<Tripleta>* tripletas; // Todos as variáveis acima, Lista e Tripleta já armazenam
        // Retorna pos (não indice) e "achou" serve para indicar se encontrou ou não
        int Busca_Binaria(int i, int j, bool& achou) const;
        void Insere_Elemento(int pos, int i, int j, valor v);  
        void Remove_Elemento(int pos);
};

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