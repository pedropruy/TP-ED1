#include <iostream>
#include <fstream>
#include <sstream>

void entrada() {
    std::ifstream arq("./design/moves.txt");
    if(!arq.is_open()) {
        std::cout << "Erro ao abrir arquivo de golpes\n";
        return;
    }


    std::string linha, token;
    
    while(std::getline(arq, linha)) {
        if (linha.empty()) continue;

        std::stringstream ss(linha);
        ss >> token; //lê a primeira palavra da linha

        if (token == "E") Modo_Armazenamento(ss);
        else if (token == "A")
        else if (token == "I")
        else if (token == "M")
        else if (token == "H")
        else if (token == "F")
        else if (token == "Z")
        else if (token == "D")
        else if (token == "LI")
        else if (token == "LA")
        else if (token == "LH")
        else if (token == "Q")
}