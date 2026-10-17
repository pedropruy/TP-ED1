#ifndef ORDENACAO_HPP
#define ORDENACAO_HPP

struct Ranking { int id_item; double pontuacao; };

void Insercao(Lista<Ranking>& lista);

void MergeSort(Lista<Ranking>& lista);

void QuickSort(Lista<Ranking>& lista);

#endif