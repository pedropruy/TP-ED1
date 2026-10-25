#include <iostream>

template<typename TipoItem>
Lista<TipoItem>::Lista() {
    tamanho = 0;
    capacidade = 1;
    itens = new TipoItem[capacidade];
}

template<typename TipoItem>
Lista<TipoItem>::~Lista() { delete[] itens; }

template<typename TipoItem>
Lista<TipoItem>::Lista(const Lista<TipoItem> &l) {
    this->tamanho = l.tamanho;
    this->capacidade = l.capacidade;

    this->alocacoes = l.alocacoes;
    this->capacidade = l.capacidade;
    this->copiados = l.copiados;
    this->deslocados = l.deslocados;
    
    this->itens = new TipoItem[this->capacidade];
    for (int i = 0; i < this->tamanho; i++)
        this->itens[i] = l.itens[i];
}

template<typename TipoItem>
Lista<TipoItem>& Lista<TipoItem>::operator= (const Lista<TipoItem> &l) {
    if (this == &l) {
        return *this;
    }

    delete[] this->itens;
    this->tamanho = l.tamanho;
    this->capacidade = l.capacidade;

    this->alocacoes = l.alocacoes;
    this->capacidade = l.capacidade;
    this->copiados = l.copiados;
    this->deslocados = l.deslocados;

    this->itens = new TipoItem[this->capacidade];
    for (int i = 0; i < this->tamanho; i++)
        this->itens[i] = l.itens[i];

    return *this;
}

template<typename TipoItem>
int Lista<TipoItem>::Get_Tamanho() { return tamanho; }

template<typename TipoItem>
int Lista<TipoItem>::Get_Tamanho() const { return tamanho; }

template<typename TipoItem>
int Lista<TipoItem>::Get_Capacidade() const { return capacidade; }

template<typename TipoItem>
Analise Lista<TipoItem>::Get_Contadores() const {
    Analise a;
    a.deslocados = deslocados;
    a.alocacoes = alocacoes;
    a.liberacoes = liberacoes;
    a.copiados = copiados;
    return a;
}

template<typename TipoItem>
void Lista<TipoItem>::Zerar_Contadores() {
    deslocados = 0; alocacoes = 0;
    liberacoes = 0; copiados = 0;
}

template<typename TipoItem>
TipoItem& Lista<TipoItem>::Get_Item(int ind) {
    if ((ind > tamanho-1) ||(ind < 0)) throw "Get_Item: Id Invalido!";
    return itens[ind];
}

template<typename TipoItem>
TipoItem& Lista<TipoItem>::Get_Item(int ind) const {
    if ((ind > tamanho-1) ||(ind < 0)) throw "Get_Item: Id Invalido!";
    return itens[ind];
}

template<typename TipoItem>
void Lista<TipoItem>::Set_Item(const TipoItem& item, int ind) {
    if ((ind >= tamanho) ||(ind < 0)) throw "Set_Item: Id Invalido!";
    itens[ind] = item;
}

template<typename TipoItem>
void Lista<TipoItem>::Insere_Inicio(const TipoItem& item) {
    if (tamanho == capacidade) Dobrar_Tamanho();
    tamanho++;
    CONTA_VAR(deslocados, tamanho-1);
    int i;
    for (i = tamanho-1; i > 0; i--) itens[i] = itens[i-1];
    itens[0] = item;
}

template<typename TipoItem>
void Lista<TipoItem>::Insere_Final(const TipoItem& item) {
    if (tamanho == capacidade) Dobrar_Tamanho();
    itens[tamanho] = item;
    tamanho++;
}

template<typename TipoItem>
void Lista<TipoItem>::Insere_Posicao(const TipoItem& item, int pos) {
    if ((pos > tamanho+1) || (pos <= 0)) throw "Insere_Posicao: Posicao Invalida!";
    if (tamanho == capacidade) Dobrar_Tamanho();
    pos--; // posição no vetor = pos-1
    CONTA_VAR(deslocados, tamanho - pos);
    int i;
    for (i = tamanho; i > pos; i--) itens[i] = itens[i-1];
    itens[pos] = item;
    tamanho++;
}

template<typename TipoItem>
TipoItem Lista<TipoItem>::Remove_Inicio() {
    if (tamanho == 0) throw "ERRO: Lista vazia!";
    int i; TipoItem aux;
    aux = itens[0];
    CONTA_VAR(deslocados, tamanho-1);
    for (i=0; i < tamanho-1; i++) itens[i] = itens[i+1];
    tamanho--;
    return aux;
}

template<typename TipoItem>
TipoItem Lista<TipoItem>::Remove_Final() {
    if (tamanho == 0) throw "ERRO: Lista vazia!";
    TipoItem aux;
    tamanho--;
    aux = itens[tamanho];
    return aux;
}

template<typename TipoItem>
TipoItem Lista<TipoItem>::Remove_Posicao(int pos) {
    if ((pos > tamanho) ||(pos <= 0)) throw "Remove_Posicao: Posicao Invalida!";
    pos--; // posição no vetor = pos-1
    int i; TipoItem aux;
    aux = itens [pos];
    CONTA_VAR(deslocados, tamanho-1-pos);
    for (i= pos; i < tamanho-1; i++) itens[i] = itens[i+1];
    tamanho--;
    return aux;
}

template<typename TipoItem> // Função desnecessário pois tem acesso direto pelo índice
TipoItem Lista<TipoItem>::Pesquisa(int c) {
    if (tamanho == 0) throw "ERRO: Lista vazia!";
    int i; TipoItem aux;
    for (i= 0; i < tamanho; i++)
        if (itens[i].GetChave() == c) {
            aux = itens[i]; break;
        }
    return aux;
}

template<typename TipoItem>
void Lista<TipoItem>::Imprime() {
    if (tamanho == 0) return;
    int i;
    for (i=0; i < tamanho; i++) 
        std::cout << itens[i] << std::endl;
}

template<typename TipoItem>
void Lista<TipoItem>::Limpa() { tamanho = 0; }

template<typename TipoItem>
void Lista<TipoItem>::Dobrar_Tamanho() {
    int nova_capacidade = capacidade*2;
    TipoItem* novo_itens = new TipoItem[nova_capacidade]; 
    
    for (int i = 0; i < tamanho; i++)
        novo_itens[i] = itens[i];
    
    CONTA_VAR(alocacoes, 1); CONTA_VAR(liberacoes, 1);
    delete[] itens;
    capacidade = nova_capacidade;
    itens = novo_itens;
}