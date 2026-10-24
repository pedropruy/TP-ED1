#include <iostream>

template<typename TipoItem>
Fila<TipoItem>::Fila() {
    tamanho = 0;
    capacidade = 1;
    frente = 0; tras = 0;
    itens = new TipoItem[capacidade];
}

template<typename TipoItem>
Fila<TipoItem>::~Fila() { delete[] itens; }

template<typename TipoItem>
int Fila<TipoItem>::Get_Tamanho() const { return tamanho; }

template<typename TipoItem>
void Fila<TipoItem>::Enfileira(const TipoItem& item) {
    if (tamanho == capacidade) Dobrar_Tamanho();
    itens[tras] = item;
    tras = (tras + 1) % capacidade;
    tamanho++;
}

template<typename TipoItem>
TipoItem Fila<TipoItem>::Desenfileira() {
    TipoItem aux;
    if (tamanho == 0) throw "Fila esta vazia!";
    aux = itens[frente];
    frente = (frente + 1) % capacidade;
    tamanho --;
    return aux;
}

template<typename TipoItem>
void Fila<TipoItem>::Imprime(){
    if (tamanho == 0) return;
    int iterador = frente;
    for (int i = 0; i < tamanho; i++) {
        std::cout << itens[iterador] << std::endl;
        iterador++;
        if (iterador == capacidade) iterador = 0; 
    }
}

template<typename TipoItem>
void Fila<TipoItem>::Limpa(){
    tamanho = 0;
    frente = 0;
    tras = 0;
}

template<typename TipoItem>
void Fila<TipoItem>::Dobrar_Tamanho(){
    int nova_capacidade = capacidade*2;
    TipoItem* novo_itens = new TipoItem[nova_capacidade]; 
    
    int iterador = frente;
    for (int i = 0; i < tamanho; i++) {
        novo_itens[i] = itens[iterador];
        iterador++;
        if (iterador == capacidade) iterador = 0; 
    }
    
    delete[] itens;
    capacidade = nova_capacidade;
    itens = novo_itens;
    frente = 0;
    tras = tamanho;
}


template<typename TipoItem>
FilaEncadeada<TipoItem>::FilaEncadeada() {
    frente = new TipoCelula<TipoItem>();
    tras = frente;
    tamanho = 0;
}

template<typename TipoItem>
FilaEncadeada<TipoItem>::~FilaEncadeada() { Limpa(); delete frente; }

template<typename TipoItem>
int FilaEncadeada<TipoItem>::Get_Tamanho() const { return tamanho; }

template<typename TipoItem>
void FilaEncadeada<TipoItem>::Enfileira(const TipoItem& item) {
    TipoCelula<TipoItem>* nova;
    nova = new TipoCelula<TipoItem>();
    nova->item = item;
    tras->prox = nova;
    tras = nova;
    tamanho++;
}

template<typename TipoItem>
TipoItem FilaEncadeada<TipoItem>::Desenfileira() {
    if (tamanho == 0) throw "Fila está vazia!";

    TipoCelula<TipoItem>* aux;
    TipoItem item;
    item = frente->prox->item;
    aux = frente;
    frente = frente->prox;
    delete aux;
    tamanho--;
    return item;
}

template<typename TipoItem>
void FilaEncadeada<TipoItem>::Imprime(){
    if (tamanho == 0) return;
    TipoCelula<TipoItem>* aux = this->frente->prox;
    while (aux != nullptr) {
        std::cout << aux->item << std::endl;
        aux = aux->prox;
    }
}

template<typename TipoItem>
void FilaEncadeada<TipoItem>::Limpa(){
    TipoCelula<TipoItem>* aux;
    aux = frente->prox;
    while (aux != nullptr) {
        frente->prox = aux->prox;
        delete aux;
        aux = frente->prox;
    }
    tamanho = 0;
    tras = frente;
}