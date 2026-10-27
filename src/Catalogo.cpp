#include "../include/Catalogo.hpp"

Catalogo::Catalogo() { matriz = new MatrizCSR(0,0); }

Catalogo::~Catalogo() { delete matriz; }

char Catalogo::Trocar_de_Modo(char modo) {
    bool COO = (dynamic_cast<MatrizCOO*>(matriz) != nullptr),
         CSR = (dynamic_cast<MatrizCSR*>(matriz) != nullptr),
         Encadeada = (dynamic_cast<MatrizEncadeada*>(matriz) != nullptr);

    // Se a matriz já estiver no modo retorna sem fazer nada
    if ((modo == 'T' && COO) || (modo == 'C' && CSR) ||
        (modo == 'L' && Encadeada)) return modo;

    int lin = 0, col = 0;
    matriz->Get_Dimensoes(lin, col);
    Matriz* nova = nullptr;

    // Cria o objeto de destino baseado unicamente no modo solicitado
    if (modo == 'T') nova = new MatrizCOO(lin, col);
    else if (modo == 'C') nova = new MatrizCSR(lin, col);
    else if (modo == 'L') nova = new MatrizEncadeada(lin, col);
    else return modo; // Modo inválido

    matriz->Converter_Matriz(*nova, modo);
    delete matriz;
    matriz = nova;
    return modo;
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

Analise Catalogo::Get_Analise() { return matriz->Get_Analise(); }
void Catalogo::Zerar_Analise() { matriz->Zerar_Analise(); }
long long Catalogo::Bytes_Usados() { return matriz->Bytes_Usados(); }

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