#include <iostream>

template<typename TipoItem>
Fila<TipoItem>::Fila() {
    if (encadeada) celula_frente = new TipoCelula<TipoItem>();
    else celula_frente = nullptr;
    celula_tras = celula_frente;
    tamanho = 0;

    
    capacidade = 1;
    indice_frente = 0;
    indice_tras = 0;
    if (encadeada) itens = nullptr;
    else itens = new TipoItem[capacidade];
}

template<typename TipoItem>
Fila<TipoItem>::~Fila() {
    if (encadeada) { Limpa(); delete celula_frente; }
    else { delete[] itens; }
}

template<typename TipoItem>
int Fila<TipoItem>::Get_Tamanho() const { return tamanho; }

template<typename TipoItem>
void Fila<TipoItem>::Enfileira(TipoItem item) {
    if (encadeada) {
        TipoCelula<TipoItem>* nova;
        nova = new TipoCelula<TipoItem>();
        nova->item = item;
        celula_tras->prox = nova;
        celula_tras = nova;
        tamanho++;
    } else {
        if (tamanho == capacidade) Dobrar_Tamanho();
        itens[indice_tras] = item;
        indice_tras = (indice_tras + 1) % capacidade;
        tamanho++;
    }
}

template<typename TipoItem>
TipoItem Fila<TipoItem>::Desenfileira() {
    if (encadeada) {
        if (tamanho == 0) throw "Fila está vazia!";

        TipoCelula<TipoItem>* aux;
        TipoItem item;
        item = celula_frente->prox->item;
        aux = celula_frente;
        celula_frente = celula_frente->prox;
        delete aux;
        tamanho--;
        return item;
    } else {
        TipoItem aux;
        if (tamanho == 0) throw "Fila esta vazia!";
        aux = itens[indice_frente];
        indice_frente = (indice_frente + 1) % capacidade;
        tamanho --;
        return aux;
    }
}

template<typename TipoItem>
void Fila<TipoItem>::Imprime(){
    if (tamanho == 0) return;
    if(encadeada) {
        TipoCelula<TipoItem>* aux = this->celula_frente;
        while (aux != nullptr) {
            std::cout << aux->item << std::endl;
            aux = aux->prox;
        }
    } else {
        int iterador = indice_frente;
        for (int i = 0; i < tamanho; i++) {
            std::cout << itens[iterador] << std::endl;
            iterador++;
            if (iterador == capacidade) iterador = 0; 
        }
    }
}

template<typename TipoItem>
void Fila<TipoItem>::Limpa(){
    if (encadeada) {
        TipoCelula<TipoItem>* aux;
        aux = celula_frente->prox;
        while (aux != nullptr) {
            celula_frente->prox = aux->prox;
            delete aux;
            aux = celula_frente->prox;
        }
        tamanho = 0;
        celula_tras = celula_frente;
    } else {
        tamanho = 0;
        indice_frente = 0;
        indice_tras = 0;
    }
}

template<typename TipoItem>
void Fila<TipoItem>::Dobrar_Tamanho(){
    int nova_capacidade = capacidade*2;
    TipoItem* novo_itens = new TipoItem[nova_capacidade]; 
    
    int iterador = indice_frente;
    for (int i = 0; i < tamanho; i++) {
        novo_itens[i] = itens[iterador];
        iterador++;
        if (iterador == capacidade) iterador = 0; 
    }
    
    delete[] itens;
    capacidade = nova_capacidade;
    itens = novo_itens;
    indice_frente = 0;
    indice_tras = tamanho;
}