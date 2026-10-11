#ifndef LISTA_HPP
#define LISTA_HPP

template<typename TipoItem, typename TipoChave>
class ListaEncadeada {
    public:
        ListaEncadeada(); ~ListaEncadeada();
        int Get_Tamanho();
        TipoItem Get_Item(int pos);
        void Set_Item(TipoItem item, int pos);
        void Insere_Inicio(TipoItem item);
        void Insere_Final(TipoItem item);
        void Insere_Posicao(TipoItem item, int pos);
        TipoItem Remove_Inicio();
        TipoItem Remove_Final();
        TipoItem Remove_Posicao(int pos);
        TipoItem Pesquisa(TipoChave c);
        void Imprime();
        void Limpa();
    private:
        int tamanho;
        TipoCelula* primeiro; // aponta para a cabeça
        TipoCelula* ultimo; // aponta para a última
        TipoCelula* Posiciona(int pos, bool antes); // posiciona ponteiro
};
// O(n) = Get, Set, RemoveFinal

//  Se usasse como índex talvez seria melhor ñ encadeada, pq só usaremos ela para acessar
// O(n) = 

#endif