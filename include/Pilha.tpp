template<typename TipoItem>
Pilha<TipoItem>::Pilha() {
    topo = nullptr;
    tamanho = 0;
}

template<typename TipoItem>
Pilha<TipoItem>::~Pilha() {
    Limpa();
}

template<typename TipoItem>
Pilha<TipoItem>::Pilha(const Pilha<TipoItem> &p) {
    this->tamanho = 0;
    this->topo = nullptr;
    Copia(p);
}
template<typename TipoItem>
Pilha<TipoItem>& Pilha<TipoItem>::operator= (const Pilha<TipoItem> &p) {
    if (this == &p) return *this;

    Limpa();
    Copia(p);
    
    return *this;
}

template<typename TipoItem>
void Pilha<TipoItem>::Copia(const Pilha& p) {
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
int Pilha<TipoItem>::Get_Tamanho() const { return tamanho; }

template<typename TipoItem>
void Pilha<TipoItem>::Empilha(TipoItem item){
    TipoCelula<TipoItem>* nova;
    nova = new TipoCelula<TipoItem>();
    nova->item = item;
    nova->prox = topo;
    topo = nova;
    tamanho++;
}

template<typename TipoItem>
TipoItem Pilha<TipoItem>::Desempilha(){
    if (tamanho == 0)
        throw "A pilha esta vazia!";

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
void Pilha<TipoItem>::Limpa(){
    while (tamanho != 0)
        Desempilha();
        
    this->topo = nullptr;
}