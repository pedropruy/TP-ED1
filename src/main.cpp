#include "Forja.hpp"
#include "Entrada.hpp"
#include <iostream>
#include <fstream>

int main() {
    std::ifstream arq("entrada.txt");
    if(!arq.is_open()) {
        std::cout << "Erro ao abrir arquivo de entrada\n";
        return 0;
    }

    Forja forja;

    std::string linha;   
    try {
        while(std::getline(arq, linha)) { 
            if (linha.empty()) break; // caso tenha uma linha vazia

            Comando(forja, linha);
        }
    } catch (char const* e) { std::cout << e << std::endl; }

    arq.close();

    return 0;
}