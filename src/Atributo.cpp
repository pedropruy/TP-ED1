#include "Atributo.hpp"

Atributo::Atributo(unsigned int _id, std::string _nome) : id(_id), nome(_nome) {}
Atributo::~Atributo() {}

unsigned int Atributo::Get_Id() { return id; }
std::string Atributo::Get_Nome() { return nome; }

void Atributo::Set_Id(unsigned int _id) { id = _id; }
void Atributo::Set_Nome(std::string _nome) { nome = _nome; }