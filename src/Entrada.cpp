#include "Forja.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

/*void Main_Fake() {
    std::ifstream arq("../bin/entrada.txt");
    if(!arq.is_open()) {
        std::cout << "Erro ao abrir arquivo de entrada\n";
        return;
    }

    Catalogo catalogo;

    std::string linha;   
    try {
        while(std::getline(std::cin, linha)) { 
            if (linha.empty()) continue; // caso tenha uma linha vazia

            Comando(catalogo, linha);
        }
    } catch (std::exception& e) { e.what(); }

    std::cout << "fim" << std::endl;

    arq.close();
}*/

void Terminal_Modo(Forja& j, std::stringstream& ss) {
    char modo;
    ss >> modo;
    if (modo == 'L' || modo == 'T') 
        std::cout << "E " << j.Modo(modo) << std::endl;
    else std::cout << "Modo invalido!" << std::endl;
}

void Terminal_Atributo(Forja& j, std::stringstream& ss) {
    std::string nome;
    ss >> nome;
    std::cout << "I " << j.Cadastro_Atributo(nome) << std::endl;
}

void Terminal_Item(Forja& j, std::stringstream& ss) {
    std::string nome;
    ss >> nome;
    std::cout << "I " << j.Cadastro_Item(nome) << std::endl;
}

void Terminal_Modificador(Forja& j, std::stringstream& ss) {
    int id_i, id_a, valor;
    ss >> id_i; ss >> id_a; ss >> valor;
    j.Definir_Modificador(id_i, id_a, valor);
    std::cout << "M " << j.Nome_Item(id_i) << " " 
              << j.Nome_Atributo(id_a) << " " << valor << std::endl;
}

void Terminal_Aventureiro(Forja& j, std::stringstream& ss) {
    std::string nome;
    ss >> nome;
    std::cout << "H " << j.Cadastro_Aventureiro(nome) << std::endl;
}

void Terminal_Encomenda(Forja& j, std::stringstream& ss) {
    int id_v, id_i;
    ss >> id_v; ss >> id_i;
    std::cout << "F " << j.Adiciona_Encomenda(id_v, id_i) << std::endl;
}

void Terminal_Forjada(Forja& j, std::stringstream& ss) {
    int turnos; ss >> turnos;
    Lista<Pedido> atendidos;

    // turnos => vira turnos que passaram
    turnos = j.Turnos_de_Trabalho(turnos, atendidos);
    std::cout << "Z " << turnos << std::endl;
    
    for (int i = 1; i <= turnos; i++) {
        Pedido& pedido = atendidos.Get_Item(i-1); // i começa em 1
        std::cout << "endomenda_" << i << " " << pedido.id_aventureiro
                  << " " << pedido.id_item << " "; 
    }
    if(turnos > 0) std::cout << std::endl;
}

void Terminal_Desequipar(Forja& j, std::stringstream& ss) {
    int id_v; ss >> id_v;
    int id_i = j.Desequipar(id_v);
    if (id_i == -1)
        std::cout << "D " << j.Nome_Aventureiro(id_v) << " VAZIO" << std::endl;
    else
        std::cout << "D " << j.Nome_Aventureiro(id_v) << " " << j.Nome_Item(id_i) << std::endl;
}

void Terminal_Consulta_Item(Forja& j, std::stringstream& ss) {
    int id_i; ss >> id_i;

    Lista<Consulta> atributos;
    j.Consulta_Item(id_i, atributos);
    std::cout << "LI " << j.Nome_Item(id_i);

    if (atributos.Get_Tamanho() == 0) {
        std::cout << " VAZIO" << std::endl;
        return;
    }

    for (int i = 1; i <= atributos.Get_Tamanho(); i++) {
        Consulta& consulta = atributos.Get_Item(i-1); // i começa em 1
        std::cout << " atributo_" << i << " " << consulta.id_objeto
                  << " " << consulta.valor;
    }
    std::cout << std::endl;
}

void Terminal_Consulta_Atributo(Forja& j, std::stringstream& ss) {
    int id_a; ss >> id_a;

    Lista<Consulta> itens;
    j.Consulta_Atributo(id_a, itens);
    std::cout << "LA " << j.Nome_Atributo(id_a);

    if (itens.Get_Tamanho() == 0) {
        std::cout << " VAZIO" << std::endl;
        return;
    }

    for (int i = 1; i <= itens.Get_Tamanho(); i++) {
        Consulta& consulta = itens.Get_Item(i-1); // i começa em 1
        std::cout << " item_" << i << " " << consulta.id_objeto
                  << " " << consulta.valor;
    }
    std::cout << std::endl;
}

void Terminal_Consulta_Atributo_Intervalo(Forja& j, std::stringstream& ss) {
    int id_a, val_min, val_max;
    ss >> id_a; ss >> val_min; ss >> val_max;

    Lista<Consulta> itens;
    j.Consulta_Atributo_Intervalo(id_a, val_min, val_max, itens);
    std::cout << "LF " << j.Nome_Atributo(id_a);

    if (itens.Get_Tamanho() == 0) {
        std::cout << " VAZIO" << std::endl;
        return;
    }

    for (int i = 1; i <= itens.Get_Tamanho(); i++) {
        Consulta& consulta = itens.Get_Item(i-1); // i começa em 1
        std::cout << " item_" << i << " " << consulta.id_objeto
                  << " " << consulta.valor;
    }
    std::cout << std::endl;
}

void Terminal_Consulta_Build(Forja& j, std::stringstream& ss) {
    int id_v; ss >> id_v;

    Lista<Consulta> atributos;
    j.Consulta_Build(id_v, atributos);
    std::cout << "LH " << j.Nome_Aventureiro(id_v);

    if (atributos.Get_Tamanho() == 0) {
        std::cout << " VAZIO" << std::endl;
        return;
    }

    for (int i = 1; i <= atributos.Get_Tamanho(); i++) {
        Consulta& consulta = atributos.Get_Item(i-1); // i começa em 1
        std::cout << " atributo_" << i << " " << consulta.id_objeto
                  << " " << consulta.valor;
    }
    std::cout << std::endl;
}

void Terminal_Consulta_Recomendacao(Forja& j, std::stringstream& ss) {
    int id_v, qtd_max, qtd_met;
    ss >> id_v; ss >> qtd_max; ss >> qtd_met;

    Lista<Metrica> metricas;
    std::string nome_metrica;
    bool sinergia = false;
    for (int i = 0; i < qtd_met; i++) {
        Metrica m;
        ss >> nome_metrica; ss >> m.peso;
        if (nome_metrica == "PODER") m.enum_metrica = 0;
        else if (nome_metrica == "EQUILIBRIO") m.enum_metrica = 1;
        else if (nome_metrica == "SINERGIA") { m.enum_metrica = 2; sinergia = true; }
        else throw "Metrica invalida";
        metricas.Insere_Final(m);
    }

    // enum_metrica = id_item   peso = pontucao
    Lista<Ranking> itens;
    j.Consulta_Recomendacao(id_v, qtd_max, metricas, itens, sinergia);

    if (itens.Get_Tamanho() == 0) return;

    for (int i = 0; i < itens.Get_Tamanho(); i++) {
        Ranking& resultado = itens.Get_Item(i);
        std::cout << "Q " << i+1 << " " << resultado.id_item
                  << " " << std::fixed << std::setprecision(2)
                  << resultado.pontuacao << std::endl;
    }
}

void Comando(Forja& j, std::string& linha) {
    std::string token; 
    std::stringstream ss(linha);
    ss >> token; //lê a primeira palavra da linha

    if (token == "E") Terminal_Modo(j, ss);
    else if (token == "A") Terminal_Atributo(j, ss);
    else if (token == "I") Terminal_Item(j, ss);
    else if (token == "M") Terminal_Modificador(j, ss);
    else if (token == "H") Terminal_Aventureiro(j, ss);
    else if (token == "F") Terminal_Encomenda(j, ss);
    else if (token == "Z") Terminal_Forjada(j, ss);
    else if (token == "D") Terminal_Desequipar(j, ss);
    else if (token == "LI") Terminal_Consulta_Item(j, ss);
    else if (token == "LA") Terminal_Consulta_Atributo(j, ss);
    else if (token == "LF") Terminal_Consulta_Atributo_Intervalo(j, ss);
    else if (token == "LH") Terminal_Consulta_Build(j, ss);
    else if (token == "Q") Terminal_Consulta_Recomendacao(j, ss);
    else std::cout << "Comando invalido!" << std::endl;
}