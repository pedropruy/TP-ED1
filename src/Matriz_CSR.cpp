#include "../include/Matriz.hpp"

MatrizCSR::MatrizCSR(int linhas_, int colunas_) : l(linhas_), c(colunas_) {
    tamanho = 0;
    // Vetor linhas sempre guardará dimensões l+1
    for (int i = 0; i <= l; i++) {
        linhas.Insere_Final(0);
    }
}

valor MatrizCSR::Get(int i, int j) const {
    if (i < 0 || i >= l || j < 0 || j >= c)
        throw "Posicao invalida";

    for (int p = linhas.Get_Item(i); p < linhas.Get_Item(i+1); p++)
        if (colunas.Get_Item(p) == j) return valores.Get_Item(p);

    return 0;
}

void MatrizCSR::Get_Dimensoes(int &lin, int &col) {
    lin = this->l; col = this->c;
}

void MatrizCSR::Set(int i, int j, valor v) {
    if (i < 0 || i >= l || j < 0 || j >= c)
        throw "Posicao invalida";

    int p = linhas.Get_Item(i);
    while (p < linhas.Get_Item(i + 1) && colunas.Get_Item(p) < j) p++;

    if (p < linhas.Get_Item(i + 1) && colunas.Get_Item(p) == j) { // O elemento já existe
        if (v == 0) RemoveElemento(i, p);

        else valores.Set_Item(v, p);

    } else if (v != 0) InsereElemento(i, j, p, v);
}

void MatrizCSR::Adicionar_Linha() {
    int valor_copia = linhas.Get_Item(l);
    linhas.Insere_Final(valor_copia);
    l++;
}
void MatrizCSR::Adicionar_Coluna() { c++; }

void MatrizCSR::Somar_Linha(int id_i, int* vetor, int sinal) {
    if (id_i < 0 || id_i >= l) throw "Indice de linha invalido!";

    // No vetor colunas/valores o índice da linha está guardado em i e i+1 no vetor linhas
    // Se i == i+1, então não tem valores acima de 0 na linha
    int inicio = linhas.Get_Item(id_i);
    int fim = linhas.Get_Item(id_i + 1);

    for (int k = inicio; k < fim; k++)
        vetor[colunas.Get_Item(k)] += valores.Get_Item(k) * sinal;
}

void MatrizCSR::Percorrer_Linha(int i, Lista<Consulta>& resultados) {
    if (i < 0 || i >= l) throw "Indice de linha invalido!";
    resultados.Limpa();

    // No vetor colunas/valores o índice da linha está guardado em i e i+1 no vetor linhas
    // Se i == i+1, então não tem valores acima de 0 na linha
    int inicio = linhas.Get_Item(i);
    int fim = linhas.Get_Item(i + 1);

    for (int k = inicio; k < fim; k++) {
        Consulta cons = {colunas.Get_Item(k), valores.Get_Item(k)};
        resultados.Insere_Final(cons);
    }
}

void MatrizCSR::Percorrer_Coluna(int j, Lista<Consulta>& resultados) {
    if (j < 0 || j >= c) throw "Indice de coluna invalido!";
    resultados.Limpa();

    // Como o vetor é CSR, teremos que percorrer toda a matriz
    for (int i = 0; i < l; i++) {
        int inicio = linhas.Get_Item(i);
        int fim = linhas.Get_Item(i + 1);

        for (int k = inicio; k < fim; k++) {
            if (colunas.Get_Item(k) == j) {
                Consulta cons = {i, valores.Get_Item(k)};
                resultados.Insere_Final(cons);
                break; // Existe apenas um valor da coluna por linha
            }
        }
    }
}

void MatrizCSR::Converter_em_COO(Matriz& m) {
    MatrizCOO* mo = dynamic_cast<MatrizCOO*>(&m);
    if (mo == nullptr) throw "Classe Matriz invalida!";

    if (mo->c != this->c || mo->l != this->l) throw "Dimensoes invalidas!";

    mo->tripletas.Limpa();
    for (int i = 0; i < this->l; i++) {
        int inicio = linhas.Get_Item(i);
        int fim = linhas.Get_Item(i + 1);

        for (int p = inicio; p < fim; p++) {
            int j = colunas.Get_Item(p);
            valor val = valores.Get_Item(p);
            mo->Set(i, j, val);
        }
    }
}

void MatrizCSR::Converter_em_Encadeada(Matriz& m) {
    MatrizEncadeada* me = dynamic_cast<MatrizEncadeada*>(&m);
    if (me == nullptr) throw "Classe Matriz invalida!";

    if (me->cabCol.Get_Tamanho() != this->c ||
        me->cabLin.Get_Tamanho() != this->l) throw "Dimensoes invalidas!";

    for (int i = 0; i < this->l; i++) {
        int inicio = linhas.Get_Item(i);
        int fim = linhas.Get_Item(i + 1);

        for (int p = inicio; p < fim; p++) {
            int j = colunas.Get_Item(p);
            valor val = valores.Get_Item(p);
            me->Set(i, j, val);
        }
    }
}

void MatrizCSR::Converter_Matriz(Matriz& m, char tipo) {
    switch (tipo) {
        case 'T':
            Converter_em_COO(m);
            break;

        case 'C':
            break;
        
        case 'L':
            Converter_em_Encadeada(m);
            break;

        default:
            throw "Tipo de matriz desconhecido!";
    }
}

void MatrizCSR::Imprime() const {
    int p = 0;
    for (int i = 0; i < l-1; i++) {
        for (int j = 0; j < c; j++) {
            if (p < linhas.Get_Item(i+1) && colunas.Get_Item(p) == j) {
                std::cout << valores.Get_Item(p) << " "; p++;
            } else std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}

void MatrizCSR::InsereElemento(int i, int j, int p, valor v) {
    // Função de Lista começa de 1, enquanto int p começa do 0
    colunas.Insere_Posicao(j, p + 1);
    valores.Insere_Posicao(v, p + 1);

    tamanho++;

    // Soma mais 1 na lista de linhas
    for (int r = i + 1; r <= l; r++) {
        linhas.Set_Item(linhas.Get_Item(r) + 1, r);
    }
}

void MatrizCSR::RemoveElemento(int i, int p) {
    // Função de Lista começa de 1, enquanto int p começa do 0
    colunas.Remove_Posicao(p + 1);
    valores.Remove_Posicao(p + 1);

    tamanho--;

    // Remove menos 1 na lista de linhas
    for (int r = i + 1; r <= l; r++) {
        linhas.Set_Item(linhas.Get_Item(r) - 1, r);
    }
}