#ifndef ORDENACAO_HPP
#define ORDENACAO_HPP

#include "Matriz.hpp"

struct Ranking { int id_item; double pontuacao; };
struct MetricasAnalise {
    long long comparacoes = 0;
    double tempo_execucao_ms = 0.0; 
};

void Insercao(Lista<Ranking>& lista, MetricasAnalise& m);

void MergeSort(Lista<Ranking>& lista, MetricasAnalise& m);

void QuickSort(Lista<Ranking>& lista, MetricasAnalise& m);
// Altera a ordenação pois agr tem q verificar por id e não por valor
void QuickSort(Lista<Consulta>& lista, MetricasAnalise& m);

#endif