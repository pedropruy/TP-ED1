#include "Item.hpp"

Item::Item(unsigned int _id, std::string _nome) : id(_id), nome(_nome) {}
Item::~Item() {}

unsigned int Item::Get_Id() { return id; }
std::string Item::Get_Nome() { return nome; }

void Item::Set_Id(unsigned int _id) { id = _id; }
void Item::Set_Nome(std::string _nome) { nome = _nome; }