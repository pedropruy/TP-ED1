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
        { 25, {"C25.txt", "T25.txt", "L25.txt"} },
        { 75, {"C75.txt", "T75.txt", "L75.txt"} }
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
                    // Omitindo std::cout do erro para não poluir a saída das médias
                }
            }

            arq.close();
        }
        Terminal_Media_Operacoes();
    }

    return 0;
}