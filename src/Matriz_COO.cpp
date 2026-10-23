#include "Matriz.hpp"

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

    Tripleta t;
    for (int k = pos-1; k < tripletas.Get_Tamanho(); k++) {
        t = tripletas.Get_Item(k);
        
        // Como o vetor é ordenado, se a primeira posição é maior então linha é vazia
        if (t.lin > i) break; 
        
        if (t.lin == i) {
            Consulta c = {t.col, t.val};
            resultados.Insere_Final(c);
        }
    }
}

void MatrizCOO::Percorrer_Coluna(int j, Lista<Consulta>& resultados) {
     Tripleta t;
    
    // Não consegui achar caminhos mais simples, teremos que varrer todo o vetor
    for (int k = 0; k < tripletas.Get_Tamanho(); k++) {
        t = tripletas.Get_Item(k);
        
        // Só filtra os itens que batem com a coluna 'j'
        if (t.col == j) {
            Consulta c = {t.lin, t.val};
            resultados.Insere_Final(c);
        }
    }
}

void MatrizCOO::Converter_em_CSR(Matriz& m) {
    MatrizCSR* mc = dynamic_cast<MatrizCSR*>(&m);
    if (mc == nullptr) throw "Classe Matriz invalida!";

    if (mc->c != this->c || mc->l != this->l) throw "Dimensoes invalidas!";

    mc->colunas.Limpa(); mc->valores.Limpa();
    mc->tamanho = 0;
    // Iniciando os vetor de linhas com dimenções l + 1
    mc->linhas.Limpa();
    for (int i = 0; i <= this->l; i++)
        mc->linhas.Insere_Final(0);

    for (int k = 0; k < this->tripletas.Get_Tamanho(); k++) {
        Tripleta t = tripletas.Get_Item(k);
        mc->Set(t.lin, t.col, t.val);
    }
}

void MatrizCOO::Converter_em_Encadeada(Matriz& m) {
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

// Deve exigir que a matriz m seja recém-construida
void MatrizCOO::Converter_Matriz(Matriz& m, char tipo) {
    switch (tipo) { 
        case 'T':
            break;
        
        case 'C':
            Converter_em_CSR(m);
            break;

        case 'L':
            Converter_em_Encadeada(m);
            break;

        default:
            break;
    }
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

#include "Matriz_CSR.cpp"
#include "Matriz_Encadeada.cpp"