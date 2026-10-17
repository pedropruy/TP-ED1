#ifndef AVENTUREIRO_HPP
#define AVENTUREIRO_HPP

#include <string>
#include "Pilha.hpp"
#include "Item.hpp"

#define Pilha Pilha
class Aventureiro {
    private:
        unsigned int id;
        std::string nome;
        Pilha<unsigned int> build;
    public:
        Aventureiro(unsigned int _id, const std::string& _nome); Aventureiro();
        unsigned int Get_Id() const;
        const std::string& Get_Nome() const;
        int Get_Tamanho_Build() const;
        void Copia_Build(Lista<unsigned int>& lista) const;
        void Set_Id(unsigned int _id);
        void Set_Nome(const std::string& _nome);
        void Equipar_Item(unsigned int _id);
        unsigned int Desequipar_Item();
        
        friend std::ostream& operator<<(std::ostream& os, const Aventureiro& a);
};

#endif