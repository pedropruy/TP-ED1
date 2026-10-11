#include "Aventureiro.hpp"
#include <iostream>

Aventureiro::Aventureiro(unsigned int _id, const std::string& _nome) : id(_id), nome(_nome) {}
Aventureiro::Aventureiro() : id(-1), nome("ERRO") {}
Aventureiro::Aventureiro(const Aventureiro &a) : id(a.id), nome(a.nome), build(a.build) {}
Aventureiro& Aventureiro::operator= (const Aventureiro &a) {
    if (this == &a) return *this;
    this->id = a.id;
    this->nome = a.nome;
    this->build = a.build;
    return *this;
}
Aventureiro::~Aventureiro() {}

unsigned int Aventureiro::Get_Id() const { return id; }
std::string Aventureiro::Get_Nome() const { return nome; }
int Aventureiro::Get_Tamanho_Build() const { return build.Get_Tamanho(); }

void Aventureiro::Set_Id(unsigned int _id) { id = _id; }
void Aventureiro::Set_Nome(const std::string& _nome) { nome = _nome; }

void Aventureiro::Equipar_Item(unsigned int _id) { build.Empilha(_id); }
unsigned int Aventureiro::Desequipar_Item(unsigned int _id) { return build.Desempilha(); }

std::ostream& operator<<(std::ostream& os, const Aventureiro& a) {
    os << a.id << ":" << a.nome;
    if (a.Get_Tamanho_Build() != 0) os << ":Tam-" << a.Get_Tamanho_Build();
    else os << ":Tam-Vazio";
    return os;
}