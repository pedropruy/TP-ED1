#include "Matriz.hpp"
#include <iostream>

Matriz::Matriz() {};
Matriz::~Matriz() {};

MatrizCOO::MatrizCOO(int linhas_, int colunas_) : l(linhas_), c(colunas_) {}

valor MatrizCOO::Get(int i, int j) const {
    if (i < 0 || i >= l || j < 0 || j >= c) throw "Posicao invalida!";
    bool achou = false;
    int pos = Busca_Binaria(i, j, achou);

    if (achou) return tripletas.Get_Item(pos-1).val;
    return 0; // nao esta na lista: e zero
}

void MatrizCOO::Get_Dimensoes(int& lin, int& col) {
    lin = this->l; col = this->c;
}

void MatrizCOO::Set(int i, int j, valor v) {
    if (i < 0 || i >= l || j < 0 || j >= c) throw "Posicao invalida!";
    bool achou = false;
    int pos = Busca_Binaria(i, j, achou);
    
    if (achou) {
        if (v == 0) Remove_Elemento(pos);
        // pos-1, pois Get_Item é por id não posição
        else tripletas.Get_Item(pos-1).val = v;
        return;
    }
    if (v != 0) Insere_Elemento(pos, i, j, v);
}

void MatrizCOO::Adicionar_Linha() { l++; }
void MatrizCOO::Adicionar_Coluna() { c++; }

void MatrizCOO::Somar_Linha(int i, int* vetor, int sinal) {
    bool achou = false;
    // Buscar por (i,0) sempre irá devolver um item ou a última posição perto desse item
    int pos = Busca_Binaria(i, 0, achou); 
    
    Tripleta t;
    
    for (int k = pos-1; k < tripletas.Get_Tamanho(); k++) {
        t = tripletas.Get_Item(k);
        
        // Como o vetor é ordenado, se a primeira posição é maior então linha é vazia
        if (t.lin > i) break; 
        
        if (t.lin == i) vetor[t.col] += (t.val * sinal);
    }
}

void MatrizCOO::Percorrer_Linha(int i, Lista<Consulta>& resultados) {
    bool achou = false;
    // Buscar por (i,0) sempre irá devolver um item ou a última posição perto desse item
    int pos = Busca_Binaria(i, 0, achou); 
    
    Consulta c; Tripleta t;
    
    for (int k = pos-1; k < tripletas.Get_Tamanho(); k++) {
        t = tripletas.Get_Item(k);
        
        // Como o vetor é ordenado, se a primeira posição é maior então linha é vazia
        if (t.lin > i) break; 
        
        if (t.lin == i) {
            c.id_objeto = t.col; c.valor = t.val;
            resultados.Insere_Final(c);
        }
    }
}

void MatrizCOO::Percorrer_Coluna(int j, Lista<Consulta>& resultados) {
    Consulta c; Tripleta t;
    
    // Não há atalho: Varrer a lista de tripletas de ponta a ponta
    for (int k = 0; k < tripletas.Get_Tamanho(); k++) {
        t = tripletas.Get_Item(k);
        
        // Só filtra os itens que batem com a coluna 'j'
        if (t.col == j) {
            c.id_objeto = t.lin;
            c.valor = t.val;
            resultados.Insere_Final(c);
        }
    }
}

// Deve exigir que a matriz m seja recém-construida
void MatrizCOO::Converter_Matriz(Matriz& m) {
    MatrizEncadeada* me = dynamic_cast<MatrizEncadeada*>(&m);
    if (me == nullptr) throw "Classe Matriz invalida!";
    
    // Tenho que exigir que matriz m é compatível com a matriz atual
    if (me->cabCol.Get_Tamanho() != this->c ||
        me->cabLin.Get_Tamanho() != this->l) throw "Dimensoes invalidas!";

    // Ponteiro ultCol será utilizado para associar durante o loop principal
    Celula** ultCol = new Celula*[this->c];
    for (int j = 0; j < this->c; j++)
        ultCol[j] = me->cabCol.Get_Item(j);
    
    Celula* ultLin = nullptr;
    int linAtual = -1;
    // Esse const aqui para evitar cópias desnecessárias na variável tri
    const Lista<Tripleta>& origem = tripletas;
        
    for (int i = 0; i < tripletas.Get_Tamanho(); i++) {
        const Tripleta& tri = origem.Get_Item(i);
                
        Celula* nova = new Celula{tri.lin, tri.col, tri.val, nullptr, nullptr};
        
        // ASSOCIAÇÃO POR LINHA
        if (tri.lin != linAtual) {
            linAtual = tri.lin;
            // Pegando a célula cabeça da linha
            ultLin = me->cabLin.Get_Item(linAtual);
        }
        
        ultLin->proxLin = nova; // Última linha liga a nova linha
        ultLin = nova; // Atualiza quem é a última linha
        
        // ASSOCIAÇÃO POR COLUNA
        ultCol[tri.col]->proxCol = nova; // Última coluna liga a nova coluna
        ultCol[tri.col] = nova; // Atualiza quem é a última coluna
    }
    me->tamanho = tripletas.Get_Tamanho();
    delete[] ultCol;
}

void MatrizCOO::Imprime() const {
    int id = 0; // proxima tripla a imprimir
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            if (id < tripletas.Get_Tamanho() && tripletas.Get_Item(id).lin == i
                 && tripletas.Get_Item(id).col == j) {
                std::cout << tripletas.Get_Item(id).val << " ";
                id++;
            } else std::cout << "0 ";
        }
        std::cout << "\n";
    }
}

int MatrizCOO::Busca_Binaria(int i, int j, bool& achou) const {
    int meio; int esq = 1; int dir = tripletas.Get_Tamanho();
    
    while (esq <= dir) {
        meio = esq + (dir - esq) / 2;
        Tripleta t = tripletas.Get_Item(meio-1);
        
        // Item está exatamente na posição meio
        if (t.lin == i && t.col == j) { achou = true; return meio; }
        
        // 1º procurar pela linha. Se busco item maior procuro na direita. 
        // 2º achei item, mas não atributo. Se busco atributo maior procuro a direita.
        // Se não, procuro a esquerda
        if (t.lin < i || (t.lin == i && t.col < j)) esq = meio + 1;
        else dir = meio - 1;
    }
    
    achou = false;
    // O valor da esquerda é exatamente onde novo item deve ser inserido
    return esq; 
}

void MatrizCOO::Insere_Elemento(int pos, int i, int j, valor v) {
    Tripleta nova_tripla;
    nova_tripla.lin = i; nova_tripla.col = j; nova_tripla.val = v;
    
    tripletas.Insere_Posicao(nova_tripla, pos); 
}

void MatrizCOO::Remove_Elemento(int pos) { tripletas.Remove_Posicao(pos); }

MatrizEncadeada::MatrizEncadeada(int li, int co) {
    if (li < 0 || co < 0) throw "Tamanho invalido!";
    tamanho = 0;
    for (int i = 0; i < li; i++)
        cabLin.Insere_Final(new Celula{i, -1, 0, nullptr, nullptr});
    for (int j = 0; j < co; j++)
        cabCol.Insere_Final(new Celula{-1, j, 0, nullptr, nullptr});
}

MatrizEncadeada::~MatrizEncadeada() {
    for (int i = 0; i < cabLin.Get_Tamanho(); i++) { // pelas linhas
        Celula* p = cabLin.Get_Item(i);
        while (p != nullptr) {
            Celula* q = p->proxLin; 
            delete p;
            p = q;
        }
    }
    for (int j = 0; j < cabCol.Get_Tamanho(); j++) delete cabCol.Get_Item(j);
}

valor MatrizEncadeada::Get(int i, int j) const {
    if (i < 0 || i >= cabLin.Get_Tamanho()
     || j < 0 || j >= cabCol.Get_Tamanho()) throw "Indice invalido!";
    Celula* ant = AntLinha(i, j);
    Celula* p = ant->proxLin;
    if (p != nullptr && p->col == j) return p->val;
    return 0;
}

void MatrizEncadeada::Get_Dimensoes(int& lin, int& col) {
    lin = this->cabLin.Get_Tamanho(); col = this->cabCol.Get_Tamanho();
}

void MatrizEncadeada::Set(int i, int j, valor v) {
    if (i < 0 || i >= cabLin.Get_Tamanho()
     || j < 0 || j >= cabCol.Get_Tamanho()) throw "Indice invalido!";
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
    cabLin.Insere_Final(new Celula{cabLin.Get_Tamanho(), -1, 0, nullptr, nullptr});
}

void MatrizEncadeada::Adicionar_Coluna() {
    cabCol.Insere_Final(new Celula{-1, cabCol.Get_Tamanho(), 0, nullptr, nullptr});
}

int MatrizEncadeada::Soma_Coluna(int j) const {
    if (j < 0 || j >= cabCol.Get_Tamanho()) throw "Indice invalido!";

    valor total = 0;
    // Começa do primeiro nó real da coluna j
    Celula* p = cabCol.Get_Item(j)->proxCol; 
    
    // Desce pela coluna somando os valores
    while (p != nullptr) { total += p->val; p = p->proxCol; }
    
    return total;
}

// ATENÇÂO: obj retornado deve fazer delete em algum momento
valor* MatrizEncadeada::Produto(const valor* v, int dim_v) {
    if (cabCol.Get_Tamanho() != dim_v) throw "Dimensoes incompativeis!"; 
    valor* vetor_res = new valor[cabLin.Get_Tamanho()];

    for (int i = 0; i < cabLin.Get_Tamanho(); i++) {
        vetor_res[i] = 0;
        Celula* p = cabLin.Get_Item(i)->proxLin;
        while (p != nullptr) {
            vetor_res[i] += p->val * v[p->col];
            p = p->proxLin;
        }
    }
    return vetor_res;
}

void MatrizEncadeada::Somar_Linha(int i, int* vetor, int sinal) {
    Celula* p = cabLin.Get_Item(i)->proxLin;
    while (p != nullptr) {
        vetor[p->col] += (p->val * sinal);
        p = p->proxLin;
    }
}

void MatrizEncadeada::Percorrer_Linha(int i, Lista<Consulta>& resultados) {
    Celula* p = cabLin.Get_Item(i)->proxLin;
    Consulta c;
    while (p != nullptr) {
        c.id_objeto = p->col; c.valor = p->val;
        resultados.Insere_Final(c);
        p = p->proxLin;
    }
}

void MatrizEncadeada::Percorrer_Coluna(int j, Lista<Consulta>& resultados) {
    Celula* p = cabCol.Get_Item(j)->proxCol;
    Consulta c;
    while (p != nullptr) {
        c.id_objeto = p->lin; c.valor = p->val;
        resultados.Insere_Final(c);
        p = p->proxCol;
    }
}

void MatrizEncadeada::Converter_Matriz(Matriz& m) {
    MatrizCOO* mo = dynamic_cast<MatrizCOO*>(&m);
    if (mo == nullptr) throw "Classe Matriz invalida!";

    if (mo->c != this->cabCol.Get_Tamanho() ||
        mo->l != this->cabLin.Get_Tamanho()) throw "Dimensoes invalidas!";

    // Limpa Lista de tripletas antes de inserir no final da lista
    mo->tripletas.Limpa();

    mo->l = this->cabLin.Get_Tamanho();
    mo->c = this->cabCol.Get_Tamanho();
    Tripleta aux;

    for (int i = 0; i < cabLin.Get_Tamanho(); i++)
        // Acesso proxLin por item da linha
        for (Celula* p = cabLin.Get_Item(i)->proxLin; p != nullptr; p = p->proxLin) {
            aux.lin = p->lin; aux.col = p->col; aux.val = p->val;
            mo->tripletas.Insere_Final(aux);
        }
}

void MatrizEncadeada::Imprime() const {
    for (int i = 0; i < cabLin.Get_Tamanho(); i++) {
        Celula* p = cabLin.Get_Item(i)->proxLin; 
        for (int j = 0; j < cabCol.Get_Tamanho(); j++) {
            if (p != nullptr && p->col == j) {
                std::cout << p->val << " ";
                p = p->proxLin;
            } else std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}

Celula* MatrizEncadeada::AntLinha(int i, int j) const {
    Celula* p = cabLin.Get_Item(i);
    while (p->proxLin != nullptr&& p->proxLin->col < j)
        p = p->proxLin;
    return p;
}

Celula* MatrizEncadeada::AntColuna(int i, int j) const {
    Celula* p = cabCol.Get_Item(j);
    while (p->proxCol != nullptr && p->proxCol->lin < i)
        p = p->proxCol;
    return p;
}