#ifndef ATRIBUTO_HPP
#define ATRIBUTO_HPP

#include <string>

class Atributo {
    private:
        unsigned int id;
        std::string nome;
    public:
        Atributo(unsigned int _id, std::string _nome); Atributo();
        Atributo(const Atributo &a);
        Atributo& operator= (const Atributo &a);
        ~Atributo();
        unsigned int Get_Id() const;
        const std::string& Get_Nome() const;
        void Set_Id(unsigned int _id);
        void Set_Nome(const std::string& _nome);
        
        friend std::ostream& operator<<(std::ostream& os, const Atributo& a);
};

#endif