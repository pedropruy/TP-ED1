#include <iostream>

template<typename TipoItem>
Lista<TipoItem>::Lista() {
    tamanho = 0;
    MAXTAM = 1;
    itens = new TipoItem[MAXTAM];
}

template<typename TipoItem>
Lista<TipoItem>::~Lista() { delete[] itens; }

template<typename TipoItem>
int Lista<TipoItem>::Get_Tamanho() { return tamanho; }


template<typename TipoItem>
TipoItem& Lista<TipoItem>::Get_Item(int id) {
    if ((id > tamanho-1) ||(id < 0)) throw "ERRO: Posicao Invalida!";
    return itens[id];
}

template<typename TipoItem>
void Lista<TipoItem>::Set_Item(const TipoItem& item, int pos) {
    if ((pos > tamanho) ||(pos <= 0)) throw "ERRO: Posicao Invalida!";
    itens[pos-1] = item;
}

template<typename TipoItem>
void Lista<TipoItem>::Insere_Inicio(const TipoItem& item) {
    if (tamanho == MAXTAM) Dobrar_Tamanho();
    tamanho++;
    int i;
    for (i = tamanho-1; i > 0; i--) itens[i] = itens[i-1];
    itens[0] = item;
}

template<typename TipoItem>
void Lista<TipoItem>::Insere_Final(const TipoItem& item) {
    if (tamanho == MAXTAM) Dobrar_Tamanho();
    itens[tamanho] = item;
    tamanho++;
}

template<typename TipoItem>
void Lista<TipoItem>::Insere_Posicao(const TipoItem& item, int pos) {
    if ((pos > tamanho+1) || (pos <= 0)) throw "ERRO: Posicao Invalida!";
    if (tamanho == MAXTAM) Dobrar_Tamanho();
    pos--; // posição no vetor = pos-1
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
    if ((pos > tamanho) ||(pos <= 0)) throw "ERRO: Posicao Invalida!";
    pos--; // posição no vetor = pos-1
    int i; TipoItem aux;
    aux = itens [pos];
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
    MAXTAM *= 2;
    TipoItem* novo_itens = new TipoItem[MAXTAM]; 
    
    for (int i = 0; i < tamanho; i++) {
        novo_itens[i] = itens[i];
    }
    
    delete[] itens;
    itens = novo_itens;
}