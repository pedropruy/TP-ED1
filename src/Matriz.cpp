#include "Matriz.hpp"
#include <iostream>

MatrizEncadeada::MatrizEncadeada(int li, int co) {
    if (li < 0 || co < 0) throw "Tamanho invalido!";
    // l = li; c = co;
    tamanho = 0;
    // cabLin = new Celula*[l];
    cabLin = new Lista<Celula*>();
    // cabCol = new Celula*[c];
    cabCol = new Lista<Celula*>();
    for (int i = 0; i < li; i++)
        cabLin->Insere_Final(new Celula{i, -1, 0, nullptr, nullptr});
        //cabLin[i] = new Celula{i, -1, 0, nullptr, nullptr};
    for (int j = 0; j < co; j++)
        cabCol->Insere_Final(new Celula{-1, j, 0, nullptr, nullptr});
        //cabCol[j] = new Celula{-1, j, 0, nullptr, nullptr};
}

MatrizEncadeada::~MatrizEncadeada() {
    for (int i = 0; i < cabLin->Get_Tamanho(); i++) { // pelas linhas
        Celula* p = cabLin->Get_Item(i);
        while (p != nullptr) {
            Celula* q = p->proxLin; 
            delete p;
            p = q;
        }
    }
    for (int j = 0; j < cabCol->Get_Tamanho(); j++) delete cabCol->Get_Item(j);
    //delete[] cabLin; delete[] cabCol;
    delete cabLin; delete cabCol;
}

valor MatrizEncadeada::Get(int i, int j) const {
    if (i < 0 || i >= cabLin->Get_Tamanho()
     || j < 0 || j >= cabCol->Get_Tamanho()) throw "Indice invalido!";
    Celula* ant = AntLinha(i, j);
    Celula* p = ant->proxLin;
    if (p != nullptr && p->col == j) return p->val;
    return 0;
}

void MatrizEncadeada::Set(int i, int j, valor v) {
    if (i < 0 || i >= cabLin->Get_Tamanho()
     || j < 0 || j >= cabCol->Get_Tamanho()) throw "Indice invalido!";
    Celula* antL = AntLinha(i, j);
    Celula* antC;
    Celula* p = antL->proxLin;
    if (p != nullptr && p->col == j) {  // ja existe
        if (v != 0) { p->val = v; return; }
        antC = AntColuna(i, j);
        antL->proxLin = p->proxLin; // desliga da linha
        antC->proxCol = p->proxCol; // desliga da coluna
        delete p; tamanho --;
        return;
    }
    if (v == 0) return;
    antC = AntColuna(i, j);
    Celula* nova = new Celula{i, j, v, antL->proxLin, antC->proxCol};
    antL->proxLin = nova; // liga na linha
    antC->proxCol = nova; // liga na coluna
    tamanho++;
}

void MatrizEncadeada::Adicionar_Linha() {
    cabLin->Insere_Final(new Celula{cabLin->Get_Tamanho(), -1, 0, nullptr, nullptr});
}

void MatrizEncadeada::Adicionar_Coluna() {
    cabCol->Insere_Final(new Celula{-1, cabCol->Get_Tamanho(), 0, nullptr, nullptr});
}

int MatrizEncadeada::Soma_Coluna(int j) const {
    if (j < 0 || j >= cabCol->Get_Tamanho()) throw "Indice invalido!";

    valor total = 0;
    // Começa do primeiro nó real da coluna j
    Celula* p = cabCol->Get_Item(j)->proxCol; 
    
    // Desce pela coluna somando os valores
    while (p != nullptr) { total += p->val; p = p->proxCol; }
    
    return total;
}

// ATENÇÂO: obj retornado deve fazer delete em algum momento
valor* MatrizEncadeada::Produto(const valor* v, int dim_v) {
    if (cabCol->Get_Tamanho() != dim_v) throw "Dimensoes incompativeis!"; 
    valor* vetor_res = new valor[cabLin->Get_Tamanho()];

    for (int i = 0; i < cabLin->Get_Tamanho(); i++) {
        vetor_res[i] = 0;
        Celula* p = cabLin->Get_Item(i)->proxLin;
        while (p != nullptr) {
            vetor_res[i] += p->val * v[p->col];
            p = p->proxLin;
        }
    }
    return vetor_res;
}

void MatrizEncadeada::Imprime() {
    for (int i = 0; i < cabLin->Get_Tamanho(); i++) {
        Celula* p = cabLin->Get_Item(i)->proxLin; 
        for (int j = 0; j < cabCol->Get_Tamanho(); j++) {
            if (p != nullptr && p->col == j) {
                std::cout << p->val << " ";
                p = p->proxLin;
            } else std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}

Celula* MatrizEncadeada::AntLinha(int i, int j) const {
    Celula* p = cabLin->Get_Item(i);
    while (p->proxLin != nullptr&& p->proxLin->col < j)
        p = p->proxLin;
    return p;
}

Celula* MatrizEncadeada::AntColuna(int i, int j) const {
    Celula* p = cabCol->Get_Item(j);
    while (p->proxCol != nullptr && p->proxCol->lin < i)
        p = p->proxCol;
    return p;
}