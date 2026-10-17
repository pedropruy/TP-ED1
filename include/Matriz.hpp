#ifndef MATRIZ_HPP
#define MATRIZ_HPP

typedef int valor;
#include "Lista.hpp"

// A implementação das matrizes irá utilizar lin = id_item, col = id_atributo, val = modificador

// Tem que fazer construtores de cópia e associação com =delete para bloquear

struct Consulta {int id_objeto; int valor; };
class Matriz {
    public:
        Matriz(); virtual ~Matriz();
        virtual valor Get(int i, int j) const = 0;
        virtual void Get_Dimensoes(int& lin, int& col) = 0;
        virtual void Set(int i, int j, valor v) = 0;
        virtual void Adicionar_Linha() = 0;
        virtual void Adicionar_Coluna() = 0;
        virtual void Somar_Linha(int id_i, int* vetor, int sinal = 1) = 0;
        virtual void Percorrer_Linha(int i, Lista<Consulta>& resultados) = 0;
        virtual void Percorrer_Coluna(int j, Lista<Consulta>& resultados) = 0;
        virtual void Converter_Matriz(Matriz& m) = 0;
        virtual void Imprime() const = 0;
};

struct Tripleta { int lin, col; valor val; };

class MatrizEncadeada; // Aqui só pro compilador não reclamar!
class MatrizCOO : public Matriz {
    public:
        MatrizCOO(int linhas, int colunas);
        // ~MatrizCOO();
        valor Get(int i, int j) const override;
        void Get_Dimensoes(int& lin, int& col) override;
        void Set(int i, int j, valor v) override;
        void Adicionar_Linha() override; void Adicionar_Coluna() override;
        void Somar_Linha(int id_i, int* vetor, int sinal) override;
        void Percorrer_Linha(int i, Lista<Consulta>& resultados) override;
        void Percorrer_Coluna(int j, Lista<Consulta>& resultados) override;
        void Converter_Matriz(Matriz& m) override;
        void Imprime() const override;
    private:
        int l, c;    // dimensoes da matriz representada
        Lista<Tripleta> tripletas; // Todos as variáveis acima, Lista e Tripleta já armazenam
        // Retorna pos (não indice) e "achou" serve para indicar se encontrou ou não
        int Busca_Binaria(int i, int j, bool& achou) const;
        void Insere_Elemento(int pos, int i, int j, valor v);  
        void Remove_Elemento(int pos);
        friend class MatrizEncadeada;
};

struct Celula {
    int lin, col;
    valor val;
    Celula* proxLin;  // proxima celula na mesma linha (coluna maior)
    Celula* proxCol;  // proxima celula na mesma coluna (linha maior)
};

class MatrizEncadeada : public Matriz {
    public:
        MatrizEncadeada(int linhas, int colunas); ~MatrizEncadeada();
        valor Get(int i, int j) const override;
        void Get_Dimensoes(int& lin, int& col) override;
        void Set(int i, int j, valor v) override;
        void Adicionar_Linha() override; void Adicionar_Coluna() override;
        void Somar_Linha(int id_i, int* vetor, int sinal) override;
        void Percorrer_Linha(int i, Lista<Consulta>& resultados) override;
        void Percorrer_Coluna(int j, Lista<Consulta>& resultados) override;
        valor Soma_Coluna(int j) const;  // percorre so a lista da coluna j
        valor* Produto(const valor* v, int dim_v);
        void Converter_Matriz(Matriz& m) override;
        void Imprime() const override;
    private:
        // Reorganizar a implementação para usar Lista
        // contadores l e c foram removidos pois Lista já armazena esses valores
        int tamanho;
        Lista<Celula*> cabLin;  // cabLin.Get_Item(i): celula cabeca da linha i
        Lista<Celula*> cabCol;  // cabCol.Get_Item(j): celula cabeca da coluna j
        Celula* AntLinha(int i, int j) const;
        Celula* AntColuna(int i, int j) const;
        friend class MatrizCOO;
};

#endif