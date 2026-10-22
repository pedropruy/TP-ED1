#include "Aventureiro.hpp"
#include <iostream>

Aventureiro::Aventureiro(unsigned int _id, const std::string& _nome) : id(_id), nome(_nome) {}
Aventureiro::Aventureiro() : id(-1), nome("ERRO") {}

unsigned int Aventureiro::Get_Id() const { return id; }
const std::string& Aventureiro::Get_Nome() const { return nome; }
int Aventureiro::Get_Tamanho_Build() const { return build.Get_Tamanho(); }

void Aventureiro::Copia_Build(Lista<unsigned int>& lista) const { build.Percorrer_Pilha(lista); }
void Aventureiro::Copia_Atributo_Build(Lista<Consulta>& lista) const { 
    lista.Limpa();
    if (atributo_build.Get_Tamanho() == 0) return;
    
    Consulta c; 
    for (int i = 0; i < atributo_build.Get_Tamanho(); i++) {
        int valor = atributo_build.Get_Item(i);
        if (valor != 0) {
            c.id_objeto = i; c.valor = valor;
            lista.Insere_Final(c);
        }
    }
}

void Aventureiro::Set_Id(unsigned int _id) { id = _id; }
void Aventureiro::Set_Nome(const std::string& _nome) { nome = _nome; }

void Aventureiro::Equipar_Item(unsigned int _id) {
    build.Empilha(_id);
}

unsigned int Aventureiro::Desequipar_Item() {
    return build.Desempilha();
}

void Aventureiro::Soma_Atributo(int id_a, int valor) {
    while (atributo_build.Get_Tamanho() <= id_a)
        atributo_build.Insere_Final(0);  // que não existia vale zero
    atributo_build.Get_Item(id_a) += valor;
}

void Aventureiro::Atualizar_Atributo(const Lista<Consulta>& linha, int sinal) {
    for (int k = 0; k < linha.Get_Tamanho(); k++)
        Soma_Atributo(linha.Get_Item(k).id_objeto, sinal * linha.Get_Item(k).valor);
}

std::ostream& operator<<(std::ostream& os, const Aventureiro& a) {
    os << a.id << ":" << a.nome;
    if (a.Get_Tamanho_Build() != 0) os << ":Tam-" << a.Get_Tamanho_Build();
    else os << ":Tam-Vazio";
    return os;
}