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
int Pilha<TipoItem>::Get_Tamanho() { return tamanho; }

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
}