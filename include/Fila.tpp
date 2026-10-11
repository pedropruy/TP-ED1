template<typename TipoItem>
Fila<TipoItem>::Fila() {
    frente = new TipoCelula<TipoItem>(); // célula cabeça
    tras = frente;
    tamanho = 0;
}

template<typename TipoItem>
Fila<TipoItem>::~Fila() {
    Limpa();
    delete frente;
}

template<typename TipoItem>
int Fila<TipoItem>::Get_Tamanho() const { return tamanho; }

template<typename TipoItem>
void Fila<TipoItem>::Enfileira(TipoItem item) {
    TipoCelula<TipoItem>* nova;
    nova = new TipoCelula<TipoItem>();
    nova->item = item;
    tras->prox = nova;
    tras = nova;
    tamanho++;
}

template<typename TipoItem>
TipoItem Fila<TipoItem>::Desenfileira() {
    if (tamanho == 0)
        throw "Fila está vazia!";

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
void Fila<TipoItem>::Limpa(){
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