#ifndef LISTA_HPP
#define LISTA_HPP

template<typename TipoItem>
class Lista {
    public:
        Lista(); ~Lista();
        int Get_Tamanho();
        TipoItem& Get_Item(int pos);
        void Set_Item(const TipoItem& item, int pos);
        void Insere_Inicio(const TipoItem& item);
        void Insere_Final(const TipoItem& item);
        void Insere_Posicao(const TipoItem& item, int pos);
        TipoItem Remove_Inicio();
        TipoItem Remove_Final();
        TipoItem Remove_Posicao(int pos);
        TipoItem Pesquisa(int valor);
        void Imprime();
        void Limpa();
    private:
        int tamanho;
        int capacidade;
        TipoItem* itens;
        void Dobrar_Tamanho();
};

#include "Lista.tpp"

#endif