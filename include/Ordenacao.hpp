#ifndef ORDENACAO_HPP
#define ORDENACAO_HPP

struct Ranking { int id_item; double pontuacao; };
struct MetricasAnalise {
    long long comparacoes = 0;
    double tempo_execucao_ms = 0.0; 
};

void Insercao(Lista<Ranking>& lista, MetricasAnalise& m);

void MergeSort(Lista<Ranking>& lista, MetricasAnalise& m);

void QuickSort(Lista<Ranking>& lista, MetricasAnalise& m);

#endif