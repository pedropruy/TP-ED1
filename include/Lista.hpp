#ifndef LISTA_HPP
#define LISTA_HPP

#include "Analise.hpp"
 
template<typename TipoItem>
class Lista {
    private:
        int tamanho = 0;
        int capacidade = 1;
        TipoItem* itens = nullptr;
        void Dobrar_Tamanho();
 
        // Variáveis da análise experimental
        long long deslocados = 0;
        long long alocacoes = 0;
        long long liberacoes = 0;
        long long copiados = 0;
    public:
        Lista(); ~Lista();
        Lista(const Lista &l);
        Lista& operator= (const Lista &l);
        int Get_Tamanho(); int Get_Tamanho() const;
        Analise Get_Contadores() const; void Zerar_Contadores();
        int Get_Capacidade() const;
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
 
#include "../src/Lista.tpp"
 

#endif