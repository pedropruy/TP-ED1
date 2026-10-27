#include "../include/Forja.hpp"
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
        { 20,  {"C2075.txt", "C2025.txt", "T2075.txt", "T2025.txt", "L2075.txt", "L2025.txt"} }
    };

    for (const auto& lote : lotes) {
        double soma_tempo_ms = 0.0;
        Analise soma_analise; // Inicializado com zeros

        if (lote.arquivos.empty()) continue;

        for (const auto& nome_arquivo : lote.arquivos) {
            std::ifstream arq(nome_arquivo);
            if (!arq.is_open()) {
                std::cout << "Erro ao abrir arquivo: " << nome_arquivo << "\n";
                continue; 
            }

            Forja forja; // Forja limpa para isolar cada teste
            std::string linha;

            auto inicio = std::chrono::high_resolution_clock::now();
            
            while (std::getline(arq, linha)) {
                if (!linha.empty() && linha.back() == '\r')
                    linha.pop_back();

                if (linha.empty()) continue;

                try { Comando(forja, linha); }
                catch (char const* e) { 
                    // Omitindo std::cout do erro para não poluir a saída das médias
                }
            }
            
            auto fim = std::chrono::high_resolution_clock::now();
            soma_tempo_ms += std::chrono::duration<double, std::milli>(fim - inicio).count();
            
            soma_analise += forja.Get_Analise_Pilha();
            arq.close();
        }

        int qtd = lote.arquivos.size();
        std::cout << "\n=== MÉDIAS PARA O PESO: " << lote.peso << " ITENS (" << qtd << " arquivos) ===\n";
        std::cout << "Tempo médio de execução: " << (soma_tempo_ms / qtd) << " ms\n";

        // Divisão manual dos campos para viabilizar a impressão
        soma_analise /= qtd;

        // Imprime utilizando o overload de << existente em Analise.hpp
        std::cout << soma_analise << std::endl;
    }

    return 0;
}