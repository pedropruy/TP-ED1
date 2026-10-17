#include "Catalogo.hpp"

Catalogo::Catalogo() { matriz = new MatrizCOO(0,0); }

Catalogo::~Catalogo() { delete matriz; }

char Catalogo::Trocar_de_Modo(char modo) {
    int lin = 0, col = 0;
    char novo_modo = 'X';
    matriz->Get_Dimensoes(lin, col);
    Matriz* nova;
    if (modo == 'L' && dynamic_cast<MatrizCOO*>(matriz) != nullptr) {
        nova = new MatrizEncadeada(lin, col);
        matriz->Converter_Matriz(*nova);
        novo_modo = 'L';
    } 
    else if (modo == 'T' && dynamic_cast<MatrizEncadeada*>(matriz) != nullptr) {
        nova = new MatrizCOO(lin, col);
        matriz->Converter_Matriz(*nova);
        novo_modo = 'T';
    } else return modo;
    delete matriz;
    matriz = nova;
    return novo_modo;
}
 
int Catalogo::Get_Tamanho_Atributos() const {
    int linhas, colunas;
    matriz->Get_Dimensoes(linhas, colunas);
    return colunas;
}

int Catalogo::Get_Tamanho_Itens() const {
    int linhas, colunas;
    matriz->Get_Dimensoes(linhas, colunas);
    return linhas;
}

int Catalogo::Get_Celula(int id_i, int id_a) const { return matriz->Get(id_i, id_a); }

void Catalogo::Set_Celula(int id_i, int id_a, int valor) { matriz->Set(id_i, id_a, valor); }

void Catalogo::Novo_Item() { matriz->Adicionar_Linha(); }

void Catalogo::Novo_Atributo() { matriz->Adicionar_Coluna(); }

void Catalogo::Remocao_Celula(int id_i, int id_a) { Set_Celula(id_i, id_a, 0); }

void Catalogo::Somar_Linha(int id_i, int* vetor) {
    matriz->Somar_Linha(id_i, vetor);
}

void Catalogo::Percurso_Linha(int id_i, Lista<Consulta>& resultados) const {
    matriz->Percorrer_Linha(id_i, resultados);
}

void Catalogo::Percurso_Coluna(int id_a, Lista<Consulta>& resultados) const {
    matriz->Percorrer_Coluna(id_a, resultados);
}

//double Catalogo::Produto_Interno(int id_i, const double* vetor_build) const {}

void Catalogo::Imprime() const { matriz->Imprime(); }