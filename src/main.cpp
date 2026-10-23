#include "Forja.hpp"
#include "Entrada.hpp"
#include <iostream>
#include <fstream>

int main() {
    std::ifstream arq("estresse.txt");
    if(!arq.is_open()) {
        std::cout << "Erro ao abrir arquivo de entrada\n";
        return 0;
    }

    Forja forja;

    std::string linha;   
    //while(std::getline(std::cin, linha)) { 
    while(std::getline(arq, linha)) {  
        if (!linha.empty() && linha.back() == '\r')
            linha.pop_back();

        if (linha.empty()) continue; 

        try { Comando(forja, linha); }
        catch (char const* e) { std::cout << e << std::endl; }
    }

    arq.close();

    return 0;
}