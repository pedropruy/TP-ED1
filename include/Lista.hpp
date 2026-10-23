#ifndef LISTA_HPP
#define LISTA_HPP

template<typename TipoItem>
class Lista {
    private:
        int tamanho;
        int capacidade;
        TipoItem* itens;
        void Dobrar_Tamanho();
    public:
        Lista(); ~Lista();
        Lista(const Lista &l);
        Lista& operator= (const Lista &l);
        int Get_Tamanho(); int Get_Tamanho() const;
        TipoItem& Get_Item(int ind); TipoItem& Get_Item(int ind) const;
        void Set_Item(const TipoItem& item, int ind);
        void Insere_Inicio(const TipoItem& item);
        void Insere_Final(const TipoItem& item);
        void Insere_Posicao(const TipoItem& item, int pos);
        TipoItem Remove_Inicio();
        TipoItem Remove_Final();
        TipoItem Remove_Posicao(int pos);
        TipoItem Pesquisa(int valor);
        void Imprime();
        void Limpa();
};

#include "../src/Lista.cpp"

#endif