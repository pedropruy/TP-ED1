#include "Item.hpp"
#include <iostream>

Item::Item(unsigned int _id, std::string _nome) : id(_id), nome(_nome) {}
Item::Item() : id(0), nome("ERRO") {}
Item::Item(const Item &i) : id(i.id), nome(i.nome) {}
Item& Item::operator= (const Item &i) {
    if (this == &i) return *this;
    this->id = i.id;
    this->nome = i.nome;
    return *this; 
}
Item::~Item() {}

unsigned int Item::Get_Id() { return id; }
std::string Item::Get_Nome() { return nome; }

void Item::Set_Id(unsigned int _id) { id = _id; }
void Item::Set_Nome(std::string _nome) { nome = _nome; }

std::ostream& operator<<(std::ostream& os, const Item& i) {
    os << i.id << ":" << i.nome;
    return os;
}