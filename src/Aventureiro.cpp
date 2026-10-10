#include "Aventureiro.hpp"

Aventureiro::Aventureiro(unsigned int _id, std::string _nome) : id(_id), nome(_nome) {}
Aventureiro::~Aventureiro() {}

unsigned int Aventureiro::Get_Id() { return id; }
std::string Aventureiro::Get_Nome() { return nome; }

void Aventureiro::Set_Id(unsigned int _id) { id = _id; }
void Aventureiro::Set_Nome(std::string _nome) { nome = _nome; }