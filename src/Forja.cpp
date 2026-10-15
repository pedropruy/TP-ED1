#include "Forja.hpp"


const std::string& Forja::Nome_Item(int ind) {
    if (ind < 0 || ind >= itens.Get_Tamanho()) throw "Indices invalidos!";
    return itens.Get_Item(ind).Get_Nome();
}

const std::string& Forja::Nome_Atributo(int ind) {
    if (ind < 0 || ind >= atributos.Get_Tamanho()) throw "Indices invalidos!";
    return atributos.Get_Item(ind).Get_Nome();
}

const std::string& Forja::Nome_Aventureiro(int ind) {
    if (ind < 0 || ind >= aventureiros.Get_Tamanho()) throw "Indices invalidos!";
    return aventureiros.Get_Item(ind).Get_Nome();
}

char Forja::Modo(char modo) { return catalogo.Trocar_de_Modo(modo); }

int Forja::Cadastro_Atributo(const std::string& nome) {
    int id_a = atributos.Get_Tamanho();
    atributos.Insere_Final(Atributo(id_a, nome));
    catalogo.Novo_Atributo();
    return id_a;
}
       
int Forja::Cadastro_Item(const std::string& nome) {
    int id_i = itens.Get_Tamanho();
    itens.Insere_Final(Item(id_i, nome));
    catalogo.Novo_Item();
    return id_i;
}
        
void Forja::Definir_Modificador(int id_i, int id_a, int valor) {
    if (id_i < 0 || id_i >= itens.Get_Tamanho()
     || id_a < 0 || id_a >= atributos.Get_Tamanho()) throw "Indices invalidos!";
    catalogo.Set_Celula(id_i, id_a, valor);
}
        
int Forja::Cadastro_Aventureiro(const std::string& nome) {
    int id_v = aventureiros.Get_Tamanho();
    aventureiros.Insere_Final(Aventureiro(id_v, nome));
    return id_v;
}
        
int Forja::Adiciona_Encomenda(int id_v, int id_i) {
    if (id_v < 0 || id_v >= aventureiros.Get_Tamanho()
     || id_i < 0 || id_i >= itens.Get_Tamanho()) throw "Indices invalidos!";
    Pedido p; p.id_aventureiro = id_v; p.id_item = id_i;
    encomendas.Enfileira(p);
    return encomendas.Get_Tamanho();
}
        
int Forja::Turnos_de_Trabalho(int turnos, Lista<Pedido>& atendidas) {
    if (turnos < 0) throw "Numero de turnos invalidos!";
    Pedido p;
    int forjadas = 0;

    while (forjadas < turnos && encomendas.Get_Tamanho() > 0) {
        Pedido p = encomendas.Desenfileira();
        aventureiros.Get_Item(p.id_aventureiro).Equipar_Item(p.id_item);
        atendidas.Insere_Final(p);
        forjadas++;
    }
    return forjadas;
}
        
int Forja::Desequipar(int id_v) {
    if (id_v < 0 || id_v >= aventureiros.Get_Tamanho()) throw "Indices invalidos!";
    Aventureiro& a = aventureiros.Get_Item(id_v);
    if (a.Get_Tamanho_Build() == 0) return -1;
    return itens.Get_Item(a.Desequipar_Item()).Get_Id();
}
        
void Forja::Consulta_Item(int id_i, Lista<Consulta>& lista) const {
    catalogo.Percurso_Linha(id_i, lista);
}
        
void Forja::Consulta_Atributo(int id_a, Lista<Consulta>& lista) const {
    catalogo.Percurso_Coluna(id_a, lista);

}
        
void Forja::Consulta_Atributo_Intervalo(int id_a, int min, int max, Lista<Consulta>& lista) const {
    catalogo.Percurso_Linha(id_a, lista);
    // Função para ordenar lista entre válidos e inválidos
}
        
Lista<Consulta> Forja::Consulta_Build(int id_v) const {

}
        
Lista<Consulta> Forja::Consulta_Recomendacao(int id_a, int n, Lista<std::string>& metricas,
                                   Lista<double>& pesos) {}

void Forja::Imprime() const { catalogo.Imprime(); }

double Forja::Poder(int id_i) {}

double Forja::Equilibrio(int id_i) {}

double Forja::Sinergia(int id_i, int id_v) {}