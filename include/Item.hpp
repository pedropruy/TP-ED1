#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {
    private:
        unsigned int id;
        std::string nome;
    public:
        Item(unsigned int _id, std::string _nome); Item();
        Item(const Item &i);
        Item& operator= (const Item &i);
        ~Item();
        unsigned int Get_Id();
        std::string Get_Nome();
        void Set_Id(unsigned int _id);
        void Set_Nome(std::string _nome);
        
        friend std::ostream& operator<<(std::ostream& os, const Item& i);
};

#endif