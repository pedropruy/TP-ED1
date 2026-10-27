#ifndef ENTRADA_HPP
#define ENTRADA_HPP

#include "Forja.hpp"
#include <iostream>

struct RegistroTempo {
    double total_ms = 0.0;
    int chamadas = 0;
};

void Terminal_Modo(Forja& j, std::stringstream& ss);

void Terminal_Atributo(Forja& j, std::stringstream& ss);

void Terminal_Item(Forja& j, std::stringstream& ss); 

void Terminal_Modificador(Forja& j, std::stringstream& ss);

void Terminal_Aventureiro(Forja& j, std::stringstream& ss);

void Terminal_Encomenda(Forja& j, std::stringstream& ss);

void Terminal_Forjada(Forja& j, std::stringstream& ss);

void Terminal_Desequipar(Forja& j, std::stringstream& ss);

void Terminal_Consulta_Item(Forja& j, std::stringstream& ss);

void Terminal_Consulta_Atributo(Forja& j, std::stringstream& ss);

void Terminal_Consulta_Atributo_Intervalo(Forja& j, std::stringstream& ss);

void Terminal_Consulta_Build(Forja& j, std::stringstream& ss);

void Terminal_Consulta_Recomendacao(Forja& j, std::stringstream& ss);

void Terminal_Configuracao(Forja& j, std::stringstream& ss);

void Terminal_Imprima_Analise(Forja& j, std::stringstream& ss);

void Terminal_Media_Operacoes();

void Comando(Forja& j, std::string& linha);

#endif