#ifndef ATRIBUTO_HPP
#define ATRIBUTO_HPP

#include <string>

class Atributo {
    private:
        unsigned int id;
        std::string nome;
    public:
        Atributo(unsigned int _id, std::string _nome);
        Atributo();
        Atributo(const Atributo &a);
        Atributo& operator= (const Atributo &a);
        ~Atributo();
        unsigned int Get_Id();
        std::string Get_Nome();
        void Set_Id(unsigned int _id);
        void Set_Nome(std::string _nome);
        
        friend std::ostream& operator<<(std::ostream& os, const Atributo& a);
};

#endif