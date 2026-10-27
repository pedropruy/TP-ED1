#include "../include/Entrada.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

// Definição da estrutura para organizar os lotes de teste
struct LoteTestes {
    int peso;
    std::vector<std::string> arquivos;
};

int main() {

    Forja forja;

    std::string linha;   
    while(std::getline(std::cin, linha)) {
        if (!linha.empty() && linha.back() == '\r')
            linha.pop_back();

        if (linha.empty()) continue; 

        try { Comando(forja, linha); }
        catch (char const* e) { std::cout << e << std::endl; }
    }

    return 0;
}