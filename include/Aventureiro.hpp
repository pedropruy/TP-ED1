#ifndef AVENTUREIRO_HPP
#define AVENTUREIRO_HPP

#include <string>
#include "Pilha.hpp"
#include "Item.hpp"

#define Pilha PilhaEncadeada
class Aventureiro {
    private:
        unsigned int id;
        std::string nome;
        Pilha<unsigned int> build;
    public:
        Aventureiro(unsigned int _id, const std::string& _nome); Aventureiro();
        unsigned int Get_Id() const;
        std::string Get_Nome() const;
        int Get_Tamanho_Build() const;
        void Set_Id(unsigned int _id);
        void Set_Nome(const std::string& _nome);
        void Equipar_Item(unsigned int _id);
        unsigned int Desequipar_Item(unsigned int _id);
        
        friend std::ostream& operator<<(std::ostream& os, const Aventureiro& a);
};

#endif