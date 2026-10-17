#include "Lista.hpp"
#include "Ordenacao.hpp"
#include <cmath>

void Insercao (Lista<Ranking>& lista) {
    int i, j;
    Ranking item_i;
    
    for (i = 1; i < lista.Get_Tamanho(); i++) {
        item_i = lista.Get_Item(i);
        j = i - 1;

        // Round assim garante que estaremos comparando até 6 casas decimais
        long long val_i = std::round(item_i.pontuacao * 1000000.0);
        while (j >= 0) {
            Ranking item_j = lista.Get_Item(j);            
            long long val_j = std::round(item_j.pontuacao * 1000000.0);

            // Valor ser maior OU Se for o mesmo valor -> id é menor
            if (val_i > val_j || (val_i == val_j && item_i.id_item < item_j.id_item)) {
                lista.Set_Item(item_j, j + 1); j--;
            } else break;
        }
        // Insere o r na posição onde foi trocada
        lista.Set_Item(item_i, j+1);
    }
}

void Merge(Lista<Ranking>& v, int e, int meio, int d, Ranking* aux) {
    int i = e, j = meio + 1, k = e;
    
    while (i <= meio && j <= d) {
        Ranking item_i = v.Get_Item(i);
        Ranking item_j = v.Get_Item(j);
        
        long long val_i = std::round(item_i.pontuacao * 1000000.0);
        long long val_j = std::round(item_j.pontuacao * 1000000.0);
        
        // Valor ser maior OU Se for o mesmo valor -> id é menor
        if (val_i > val_j || (val_i == val_j && item_i.id_item < item_j.id_item)) {
            aux[k++] = item_i; i++;
        } else { aux[k++] = item_j; j++; }
    }
    
    // Coloca o que sobrou no fim do vetor
    while (i <= meio) aux[k++] = v.Get_Item(i++);
    while (j <= d) aux[k++] = v.Get_Item(j++);
    
    // Copia os valores de aux para a lista original
    for (k = e; k <= d; k++) v.Set_Item(aux[k], k);
}

void Passo_Recursivo(Lista<Ranking>& lista, int e, int d, Ranking* aux) {
    if (e < d) {
        int meio = e + (d - e) / 2;
        Passo_Recursivo(lista, e, meio, aux);
        Passo_Recursivo(lista, meio + 1, d, aux);
        Merge(lista, e, meio, d, aux);
    }
}

void MergeSort(Lista<Ranking>& lista) {
    int tamanho = lista.Get_Tamanho();
    
    if (tamanho > 1) {
        // Alocamos vetor aux com tamanho exato e já deletamos ele
        Ranking* aux = new Ranking[tamanho];
        Passo_Recursivo(lista, 0, tamanho - 1, aux);
        delete[] aux; 
    }
}

int Particao_Lomuto(Lista<Ranking>& lista, int p, int r) {
    Ranking x = lista.Get_Item(r); // pivô: o último elemento
    long long val_x = std::round(x.pontuacao * 1000000.0);
    
    int i = p - 1;
    
    for (int j = p; j < r; j++) {
        Ranking item_j = lista.Get_Item(j);
        long long val_j = std::round(item_j.pontuacao * 1000000.0);
        
        // Valor ser maior OU Se for o mesmo valor -> id é menor
        if (val_j > val_x || (val_j == val_x && item_j.id_item < x.id_item)) {
            i++;
            // invertendo o lugar de item_j com item_w
            Ranking w = lista.Get_Item(i);
            lista.Set_Item(item_j, i);
            lista.Set_Item(w, j);
        }
    }
    
    // colocando w na posição de pivô
    Ranking w = lista.Get_Item(i + 1);
    lista.Set_Item(lista.Get_Item(r), i + 1);
    lista.Set_Item(w, r);
    
    return i + 1; // retornando a posição do pivô
}

void Ordena(int Esq, int Dir, Lista<Ranking>& lista) {
    if (Esq < Dir) {
        int q = Particao_Lomuto(lista, Esq, Dir);
        // Como estamos usando Partição de Lomuto, q já está na posição correta
        Ordena(Esq, q - 1, lista);
        Ordena(q + 1, Dir, lista);
    }
}

void QuickSort(Lista<Ranking>& lista) { 
    if (lista.Get_Tamanho() <= 1) return;
    Ordena(0, lista.Get_Tamanho() - 1, lista); 
}