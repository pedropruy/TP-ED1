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
    // Preencha os nomes dos 18 arquivos nas suas categorias
    std::vector<LoteTestes> lotes = {
        { 0, {"85.txt"} }
    };

    for (const auto& lote : lotes) {

        if (lote.arquivos.empty()) continue;

        for (const auto& nome_arquivo : lote.arquivos) {
            std::ifstream arq(nome_arquivo);
            if (!arq.is_open()) {
                std::cout << "Erro ao abrir arquivo: " << nome_arquivo << "\n";
                break; 
            }

            Forja forja; // Forja limpa para isolar cada teste
            std::string linha;
            
            while (std::getline(arq, linha)) {
                if (!linha.empty() && linha.back() == '\r')
                    linha.pop_back();

                if (linha.empty()) continue;

                try { Comando(forja, linha); }
                catch (char const* e) { 
                    std::cout << e << std::endl;
                }
            }

            arq.close();
        }
    }

    return 0;
}