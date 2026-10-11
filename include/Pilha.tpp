#include <iostream>

template<typename TipoItem>
Pilha<TipoItem>::Pilha() {
    capacidade = 1;
    topo = -1;
    itens = new TipoItem[capacidade];
    tamanho = 0;
}

template<typename TipoItem>
Pilha<TipoItem>::~Pilha() { delete[] itens; }

template<typename TipoItem>
Pilha<TipoItem>::Pilha(const Pilha<TipoItem> &p) {
    this->tamanho = 0;
    this->topo = -1;
    this->itens = nullptr;
    Copia(p);
}

template<typename TipoItem>
Pilha<TipoItem>& Pilha<TipoItem>::operator= (const Pilha<TipoItem> &p) {
    if (this == &p) return *this;
    delete[] itens; 
    Copia(p);
    
    return *this;
}

template<typename TipoItem>
void Pilha<TipoItem>::Copia(const Pilha& p) {
    this->tamanho = p.tamanho;
    this->topo = p.topo;
    this->capacidade = p.capacidade;
        
    if (p.itens != nullptr) {
        this->itens = new TipoItem[this->capacidade];
        for (int i = 0; i < this->tamanho; i++)
            this->itens[i] = p.itens[i];
    } else this->itens = nullptr;
}

template<typename TipoItem>
int Pilha<TipoItem>::Get_Tamanho() const { return tamanho; }

template<typename TipoItem>
void Pilha<TipoItem>::Empilha(const TipoItem& item){
    if (tamanho == capacidade) Dobrar_Tamanho();
    topo++;
    itens[topo] = item;
    tamanho++;
}

template<typename TipoItem>
TipoItem Pilha<TipoItem>::Desempilha(){
    if (tamanho == 0) throw "A pilha esta vazia!";

    TipoItem aux;
    aux = itens [topo];
    topo--;
    tamanho--;
    return aux;
}


template<typename TipoItem>
void Pilha<TipoItem>::Imprime() {
    if (tamanho == 0) return;
    for (int i = tamanho-1; i >= 0; i--)
        std::cout << itens[i] << std::endl;
}

template<typename TipoItem>
void Pilha<TipoItem>::Limpa(){ tamanho = 0; topo = -1; }

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


template<typename TipoItem>
PilhaEncadeada<TipoItem>::PilhaEncadeada() { topo = nullptr; tamanho = 0; }

template<typename TipoItem>
PilhaEncadeada<TipoItem>::~PilhaEncadeada() { Limpa(); }

template<typename TipoItem>
PilhaEncadeada<TipoItem>::PilhaEncadeada(const PilhaEncadeada<TipoItem> &p) {
    this->tamanho = 0;
    this->topo = nullptr;
    Copia(p);
}

template<typename TipoItem>
PilhaEncadeada<TipoItem>& PilhaEncadeada<TipoItem>::operator= (const PilhaEncadeada<TipoItem> &p) {
    if (this == &p) return *this;
    Limpa();
    Copia(p);
    
    return *this;
}

template<typename TipoItem>
void PilhaEncadeada<TipoItem>::Copia(const PilhaEncadeada& p) {
    if (p.topo == nullptr) { return; }

    this->topo = new TipoCelula<TipoItem>();
    this->topo->item = p.topo->item;
    this->tamanho++;

    TipoCelula<TipoItem>* iterador = p.topo->prox;
    TipoCelula<TipoItem>* aux = this->topo;

    while (iterador != nullptr) {
        aux->prox = new TipoCelula<TipoItem>();
        aux = aux->prox;
            
        aux->item = iterador->item;
        this->tamanho++;
            
        iterador = iterador->prox;
    }
    aux->prox = nullptr;
}

template<typename TipoItem>
int PilhaEncadeada<TipoItem>::Get_Tamanho() const { return tamanho; }

template<typename TipoItem>
void PilhaEncadeada<TipoItem>::Empilha(const TipoItem& item){
    TipoCelula<TipoItem>* nova;
    nova = new TipoCelula<TipoItem>();

    nova->item = item;
    nova->prox = topo;
    topo = nova;

    tamanho++;
}

template<typename TipoItem>
TipoItem PilhaEncadeada<TipoItem>::Desempilha() {
    if (tamanho == 0) throw "A pilha esta vazia!";

    TipoItem aux;
    TipoCelula<TipoItem>* p;
    aux = topo->item;
    p = topo;
    topo = topo->prox;
    delete p;
    tamanho--;
    return aux;
}

template<typename TipoItem>
void PilhaEncadeada<TipoItem>::Imprime() {
    if (tamanho == 0) return;
    TipoCelula<TipoItem>* aux = this->topo;
    while (aux != nullptr) {
        std::cout << aux->item << std::endl;
        aux = aux->prox;
    }
}

template<typename TipoItem>
void PilhaEncadeada<TipoItem>::Limpa() {
    while (tamanho != 0)
        Desempilha();
    topo = nullptr;
}