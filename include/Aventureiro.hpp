#ifndef AVENTUREIRO_HPP
#define AVENTUREIRO_HPP

#include <string>

class Aventureiro {
    private:
        unsigned int id;
        std::string nome;
    public:
        Aventureiro(unsigned int _id, std::string _nome);
        ~Aventureiro();
        unsigned int Get_Id();
        std::string Get_Nome();
        void Set_Id(unsigned int _id);
        void Set_Nome(std::string _nome);
};

#endif