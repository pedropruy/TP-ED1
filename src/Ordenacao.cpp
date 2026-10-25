#include "../include/Lista.hpp"
#include "../include/Ordenacao.hpp"
#include <cmath>

void Ordenacao::Insercao (Lista<Ranking>& lista) {
    int i, j;
    Ranking item_i;
    
    for (i = 1; i < lista.Get_Tamanho(); i++) {
        item_i = lista.Get_Item(i);
        j = i - 1;

        // Round assim garante que estaremos comparando até 6 casas decimais
        long long val_i = std::round(item_i.pontuacao * 1000000.0);
        while (j >= 0) {
            CONTA(ana_ord, comparacoes_ord, 1);
            Ranking item_j = lista.Get_Item(j);            
            long long val_j = std::round(item_j.pontuacao * 1000000.0);

            // Valor ser maior OU Se for o mesmo valor -> id é menor
            if (val_i > val_j || (val_i == val_j && item_i.id_item < item_j.id_item)) {
                CONTA(ana_ord, movimentos_ord, 1);
                lista.Set_Item(item_j, j + 1); j--;
            } else break;
        }
        // Insere o r na posição onde foi trocada
        CONTA(ana_ord, movimentos_ord, 1);
        lista.Set_Item(item_i, j+1);
    }
}

void Ordenacao::Merge(Lista<Ranking>& v, int e, int meio, int d, Ranking* aux) {
    int i = e, j = meio + 1, k = e;
    
    while (i <= meio && j <= d) {
        CONTA(ana_ord, comparacoes_ord, 1);
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
    
    // d-e+1 escritas em aux e d-e+1 na cópia de volta
    CONTA(ana_ord, movimentos_ord, 2 * (d - e + 1));
    // Copia os valores de aux para a lista original
    for (k = e; k <= d; k++) v.Set_Item(aux[k], k);
}

void Ordenacao::Passo_Recursivo(Lista<Ranking>& lista, int e, int d, Ranking* aux) {
    if (e < d) {
        int meio = e + (d - e) / 2;
        Passo_Recursivo(lista, e, meio, aux);
        Passo_Recursivo(lista, meio + 1, d, aux);
        Merge(lista, e, meio, d, aux);
    }
}

void Ordenacao::MergeSort(Lista<Ranking>& lista) {

    int tamanho = lista.Get_Tamanho();
    
    if (tamanho > 1) {
        // Alocamos vetor aux com tamanho exato e já deletamos ele
        Ranking* aux = new Ranking[tamanho];
        Passo_Recursivo(lista, 0, tamanho - 1, aux);
        delete[] aux; 
    }
}

int Ordenacao::Particao_Lomuto(Lista<Ranking>& lista, int p, int r) {
    // Iremos escolher o pivô sempre ao meio
    int pos_pivo = p + (r - p) / 2;
    // Troca de lugar o pivô meio com o do fim
    CONTA(ana_ord, movimentos_ord, 2); // troca pivô com o último
    Ranking temp_pivo = lista.Get_Item(pos_pivo);
    Ranking temp_fim = lista.Get_Item(r);
    lista.Set_Item(temp_fim, pos_pivo);
    lista.Set_Item(temp_pivo, r);

    Ranking x = lista.Get_Item(r); // pivô: número do meio
    long long val_x = std::round(x.pontuacao * 1000000.0);
    
    int i = p - 1;
    
    for (int j = p; j < r; j++) {
        Ranking item_j = lista.Get_Item(j);
        long long val_j = std::round(item_j.pontuacao * 1000000.0);

        // Valor ser maior OU Se for o mesmo valor -> id é menor
        CONTA(ana_ord, comparacoes_ord, 1);
        if (val_j > val_x || (val_j == val_x && item_j.id_item < x.id_item)) {
            i++;
            CONTA(ana_ord, movimentos_ord, 2); // troca
            // invertendo o lugar de item_j com item_w
            Ranking w = lista.Get_Item(i);
            lista.Set_Item(item_j, i);
            lista.Set_Item(w, j);
        }
    }
    
    // colocando w na posição de pivô
    CONTA(ana_ord, movimentos_ord, 2); // coloca o pivô na posição final
    Ranking w = lista.Get_Item(i + 1);
    lista.Set_Item(lista.Get_Item(r), i + 1);
    lista.Set_Item(w, r);
    
    return i + 1; // retornando a posição do pivô
}

void Ordenacao::Ordena(int Esq, int Dir, Lista<Ranking>& lista) {
    if (Esq < Dir) {
        int q = Particao_Lomuto(lista, Esq, Dir);
        // Como estamos usando Partição de Lomuto, q já está na posição correta
        Ordena(Esq, q - 1, lista);
        Ordena(q + 1, Dir, lista);
    }
}

void Ordenacao::QuickSort(Lista<Ranking>& lista) { 

    if (lista.Get_Tamanho() <= 1) return;
    Ordena(0, lista.Get_Tamanho() - 1, lista); 

}

int Ordenacao::Particao_Lomuto(Lista<Consulta>& lista, int p, int r) {
    // Iremos escolher o pivô sempre ao meio
    int pos_pivo = p + (r - p) / 2;
    // Troca de lugar o pivô meio com o do fim
    CONTA(ana_ord, movimentos_ord, 2); // troca pivô com o último
    Consulta temp_pivo = lista.Get_Item(pos_pivo);
    Consulta temp_fim = lista.Get_Item(r);
    lista.Set_Item(temp_fim, pos_pivo);
    lista.Set_Item(temp_pivo, r);

    Consulta x = lista.Get_Item(r); // pivô: número do meio
    int ind_x = x.id_objeto;
    
    int i = p - 1;
    
    for (int j = p; j < r; j++) {
        Consulta item_j = lista.Get_Item(j);
        int ind_j = item_j.id_objeto;

        CONTA(ana_ord, comparacoes_ord, 1);
        // Se indice for menor inverte de lugar
        if (ind_j < ind_x) {
            i++;
            CONTA(ana_ord, movimentos_ord, 2); // troca
            // invertendo o lugar de item_j com item_w
            Consulta w = lista.Get_Item(i);
            lista.Set_Item(item_j, i);
            lista.Set_Item(w, j);
        }
    }
    
    // colocando w na posição de pivô
    CONTA(ana_ord, movimentos_ord, 2); // coloca o pivô na posição final
    Consulta w = lista.Get_Item(i + 1);
    lista.Set_Item(lista.Get_Item(r), i + 1);
    lista.Set_Item(w, r);
    
    return i + 1; // retornando a posição do pivô
}

void Ordenacao::Ordena(int Esq, int Dir, Lista<Consulta>& lista) {
    if (Esq < Dir) {
        int q = Particao_Lomuto(lista, Esq, Dir);
        // Como estamos usando Partição de Lomuto, q já está na posição correta
        Ordena(Esq, q - 1, lista);
        Ordena(q + 1, Dir, lista);
    }
}

void Ordenacao::QuickSort(Lista<Consulta>& lista) { 

    if (lista.Get_Tamanho() <= 1) return;
    Ordena(0, lista.Get_Tamanho() - 1, lista);

}