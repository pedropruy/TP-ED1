#ifndef ORDENACAO_HPP
#define ORDENACAO_HPP

#include "Matriz.hpp"

struct Ranking { int id_item; double pontuacao; };

class Ordenacao {
    public:
        Analise ana_ord;
        void Insercao(Lista<Ranking>& lista);
        void MergeSort(Lista<Ranking>& lista);
        void QuickSort(Lista<Ranking>& lista);
        // Altera a ordenação pois agr tem q verificar por id e não por valor
        void QuickSort(Lista<Consulta>& lista);
    private:
        void Passo_Recursivo(Lista<Ranking>& lista, int e, int d, Ranking* aux);
        void Merge(Lista<Ranking>& v, int e, int meio, int d, Ranking* aux);
        
        void Ordena(int Esq, int Dir, Lista<Ranking>& lista);
        int Particao_Lomuto(Lista<Ranking>& lista, int p, int r);

        void Ordena(int Esq, int Dir, Lista<Consulta>& lista);
        int Particao_Lomuto(Lista<Consulta>& lista, int p, int r);
};

#endif