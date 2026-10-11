#include "Atributo.hpp"
#include <iostream>

Atributo::Atributo(unsigned int _id, std::string _nome) : id(_id), nome(_nome) {}
Atributo::Atributo() : id(-1), nome("ERRO") {}
Atributo::Atributo(const Atributo &a) : id(a.id), nome(a.nome) {}
Atributo& Atributo::operator= (const Atributo &a) {
    if (this == &a) return *this;
    this->id = a.id;
    this->nome = a.nome;
    return *this; 
}
Atributo::~Atributo() {}

unsigned int Atributo::Get_Id() { return id; }
std::string Atributo::Get_Nome() { return nome; }

void Atributo::Set_Id(unsigned int _id) { id = _id; }
void Atributo::Set_Nome(std::string _nome) { nome = _nome; }

std::ostream& operator<<(std::ostream& os, const Atributo& a) {
    os << a.id << ":" << a.nome;
    return os;
}