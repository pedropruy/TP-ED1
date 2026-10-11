#include <iostream>

template<typename TipoItem>
Pilha<TipoItem>::Pilha() {
    topoE = nullptr;

    capacidade = 1;
    topoA = -1;
    if (encadeada) itens = nullptr;
    else itens = new TipoItem[capacidade];

    tamanho = 0;
}

template<typename TipoItem>
Pilha<TipoItem>::~Pilha() {
    if (encadeada) Limpa();
    else delete[] itens;
}

template<typename TipoItem>
Pilha<TipoItem>::Pilha(const Pilha<TipoItem> &p) {
    this->encadeada = p.encadeada;
    this->tamanho = 0;
    this->topoE = nullptr;
    this->topoA = -1;
    this->itens = nullptr;
    Copia(p);
}
template<typename TipoItem>
Pilha<TipoItem>& Pilha<TipoItem>::operator= (const Pilha<TipoItem> &p) {
    if (this == &p) return *this;

    if(this->encadeada) Limpa();
    else delete[] itens; 
    this->encadeada = p.encadeada;
    Copia(p);
    
    return *this;
}

template<typename TipoItem>
void Pilha<TipoItem>::Copia(const Pilha& p) {
    if (this->encadeada) {
        this->capacidade = p.capacidade;
        if (p.topoE == nullptr) { return; }

        this->topoE = new TipoCelula<TipoItem>();
        this->topoE->item = p.topoE->item;
        this->tamanho++;

        TipoCelula<TipoItem>* iterador = p.topoE->prox;
        TipoCelula<TipoItem>* aux = this->topoE;

        while (iterador != nullptr) {
            aux->prox = new TipoCelula<TipoItem>();
            aux = aux->prox;
            
            aux->item = iterador->item;
            this->tamanho++;
            
            iterador = iterador->prox;
        }
        aux->prox = nullptr;
    } else {
        this->tamanho = p.tamanho;
        this->topoA = p.topoA;
        this->capacidade = p.capacidade;
        
        if (p.itens != nullptr) {
            this->itens = new TipoItem[this->capacidade];
            for (int i = 0; i < this->tamanho; i++)
                this->itens[i] = p.itens[i];
        } else this->itens = nullptr;
    }
}

template<typename TipoItem>
int Pilha<TipoItem>::Get_Tamanho() const { return tamanho; }

template<typename TipoItem>
void Pilha<TipoItem>::Empilha(TipoItem item){
    if (encadeada) {
        TipoCelula<TipoItem>* nova;
        nova = new TipoCelula<TipoItem>();
        nova->item = item;
        nova->prox = topoE;
        topoE = nova;
    } else { 
        if (tamanho == capacidade) Dobrar_Tamanho();
        topoA++;
        itens[topoA] = item;
    }
    tamanho++;
}

template<typename TipoItem>
TipoItem Pilha<TipoItem>::Desempilha(){
    if (tamanho == 0) throw "A pilha esta vazia!";

    TipoItem aux;
    if (encadeada) {
        TipoCelula<TipoItem>* p;
        aux = topoE->item;
        p = topoE;
        topoE = topoE->prox;
        delete p;
    } else {
        aux = itens [topoA];
        topoA --;
    }
    tamanho --;
    return aux;
}

template<typename TipoItem>
void Pilha<TipoItem>::Imprime(){
    if (tamanho == 0) return;
    if(encadeada) {
        TipoCelula<TipoItem>* aux = this->topoE;
        while (aux != nullptr) {
            std::cout << aux->item << std::endl;
            aux = aux->prox;
        }
    } else {
        for (int i = 0; i < tamanho; i++)
            std::cout << itens[i] << std::endl;
    }
}

template<typename TipoItem>
void Pilha<TipoItem>::Limpa(){
    if (encadeada) {
        while (tamanho != 0)
            Desempilha();
        topoE = nullptr;
    } else {        
        tamanho = 0;
        topoA = -1;
    }
}

template<typename TipoItem>
void Pilha<TipoItem>::Dobrar_Tamanho(){
    int nova_capacidade = capacidade*2;
    TipoItem* novo_itens = new TipoItem[nova_capacidade]; 
    
    for (int i = 0; i < tamanho; i++)
        novo_itens[i] = itens[i];
    
    delete[] itens;
    capacidade = nova_capacidade;
    itens = novo_itens;
}