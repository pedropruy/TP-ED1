#include "../include/Entrada.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>

static RegistroTempo tempo_E, tempo_M, tempo_F, tempo_Z,
                     tempo_D, tempo_LI, tempo_LA, tempo_LH,
                     tempo_LF, tempo_Q;

void Terminal_Modo(Forja& j, std::stringstream& ss) {
    char modo;
    ss >> modo;

    if (modo == 'L' || modo == 'T' || modo == 'C') {
        long long Bytes_Antes = j.Get_Bytes_Matriz();
        auto inicio = std::chrono::high_resolution_clock::now();
        
        char novo_modo = j.Modo(modo); 
        
        auto fim = std::chrono::high_resolution_clock::now();
        tempo_E.total_ms = std::chrono::duration<double, std::milli>(fim - inicio).count();

        std::cout << "E " << novo_modo << std::endl;
        /*std::cout << "Tempo E - " << tempo_E.total_ms << std::endl;

        long long Bytes_Depois = j.Get_Bytes_Matriz();
        std::cout << "B_Antes: " << Bytes_Antes << std::endl
                  << "B_Depois: " << Bytes_Depois << std::endl
                  << "Pico_Estimado: " << (Bytes_Antes + Bytes_Depois) << std::endl
                  << j.Get_Analise_Catalogo() << std::endl;*/
    } else std::cout << "Modo invalido!" << std::endl;
    
    j.Zerar_Analise();
}

void Terminal_Atributo(Forja& j, std::stringstream& ss) {
    std::string nome;
    ss >> nome;
    std::cout << "A " << j.Cadastro_Atributo(nome) << std::endl;
}

void Terminal_Item(Forja& j, std::stringstream& ss) {
    std::string nome;
    ss >> nome;
    std::cout << "I " << j.Cadastro_Item(nome) << std::endl;
}

void Terminal_Modificador(Forja& j, std::stringstream& ss) {
    int id_i, id_a, valor;
    ss >> id_i; ss >> id_a; ss >> valor;

    auto inicio = std::chrono::high_resolution_clock::now();

    j.Definir_Modificador(id_i, id_a, valor);

    auto fim = std::chrono::high_resolution_clock::now();
    tempo_M.total_ms += std::chrono::duration<double, std::micro>(fim - inicio).count();
    tempo_M.chamadas++;

    std::cout << "M " << j.Get_Nome_Item(id_i) << " " 
              << j.Get_Nome_Atributo(id_a) << " " << valor << std::endl;
}

void Terminal_Aventureiro(Forja& j, std::stringstream& ss) {
    std::string nome;
    ss >> nome;
    std::cout << "H " << j.Cadastro_Aventureiro(nome) << std::endl;
}

void Terminal_Encomenda(Forja& j, std::stringstream& ss) {
    int id_v, id_i;
    ss >> id_v; ss >> id_i;
    
    auto inicio = std::chrono::high_resolution_clock::now();

    int posicao = j.Adiciona_Encomenda(id_v, id_i);

    auto fim = std::chrono::high_resolution_clock::now();
    tempo_F.total_ms += std::chrono::duration<double, std::micro>(fim - inicio).count();
    tempo_F.chamadas++;

    std::cout << "F " << posicao << std::endl;
}

void Terminal_Forjada(Forja& j, std::stringstream& ss) {
    int turnos; ss >> turnos;
    Lista<Pedido> atendidos;

    auto inicio = std::chrono::high_resolution_clock::now();
    // turnos => vira turnos que passaram
    turnos = j.Turnos_de_Trabalho(turnos, atendidos);

    auto fim = std::chrono::high_resolution_clock::now();
    tempo_Z.total_ms += std::chrono::duration<double, std::micro>(fim - inicio).count();
    tempo_Z.chamadas++;
    std::cout << "Z " << turnos << std::endl;
    
    for (int i = 1; i <= turnos; i++) {
        Pedido& pedido = atendidos.Get_Item(i-1); // i começa em 1
        std::cout << "encomenda_" << i << " " << pedido.id_aventureiro
                  << " " << pedido.id_item; 
        if (i < turnos) std::cout << " ";
    }
    if(turnos > 0) std::cout << std::endl;
}

void Terminal_Desequipar(Forja& j, std::stringstream& ss) {
    int id_v; ss >> id_v;

    auto inicio = std::chrono::high_resolution_clock::now();
    
    int id_i = j.Desequipar(id_v);

    auto fim = std::chrono::high_resolution_clock::now();
    tempo_D.total_ms += std::chrono::duration<double, std::micro>(fim - inicio).count();
    tempo_D.chamadas++;

    if (id_i == -1)
        std::cout << "D " << j.Get_Nome_Aventureiro(id_v) << " VAZIO" << std::endl;
    else
        std::cout << "D " << j.Get_Nome_Aventureiro(id_v) << " " << j.Get_Nome_Item(id_i) << std::endl;
}

void Terminal_Consulta_Item(Forja& j, std::stringstream& ss) {
    int id_i; ss >> id_i;

    Lista<Consulta> atributos;
    auto inicio = std::chrono::high_resolution_clock::now();

    j.Consulta_Item(id_i, atributos);

    auto fim = std::chrono::high_resolution_clock::now();
    tempo_LI.total_ms += std::chrono::duration<double, std::micro>(fim - inicio).count();
    tempo_LI.chamadas++;

    std::cout << "LI " << j.Get_Nome_Item(id_i);

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
    auto inicio = std::chrono::high_resolution_clock::now();

    j.Consulta_Atributo(id_a, itens);

    auto fim = std::chrono::high_resolution_clock::now();
    tempo_LA.total_ms += std::chrono::duration<double, std::micro>(fim - inicio).count();
    tempo_LA.chamadas++;

    std::cout << "LA " << j.Get_Nome_Atributo(id_a);

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
    auto inicio = std::chrono::high_resolution_clock::now();

    j.Consulta_Atributo_Intervalo(id_a, val_min, val_max, itens);

    auto fim = std::chrono::high_resolution_clock::now();
    tempo_LF.total_ms += std::chrono::duration<double, std::micro>(fim - inicio).count();
    tempo_LF.chamadas++;

    std::cout << "LF " << j.Get_Nome_Atributo(id_a);

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

    auto inicio = std::chrono::high_resolution_clock::now();

    Lista<Consulta> atributos;
    j.Consulta_Build(id_v, atributos);
    std::cout << "LH " << j.Get_Nome_Aventureiro(id_v);

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

    auto fim = std::chrono::high_resolution_clock::now();
    tempo_LH.total_ms += std::chrono::duration<double, std::micro>(fim - inicio).count();
    tempo_LH.chamadas++;
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

    auto inicio = std::chrono::high_resolution_clock::now();

    j.Consulta_Recomendacao(id_v, qtd_max, metricas, itens, sinergia);

    auto fim = std::chrono::high_resolution_clock::now();
    tempo_Q.total_ms += std::chrono::duration<double, std::micro>(fim - inicio).count();
    tempo_Q.chamadas++;

    if (itens.Get_Tamanho() == 0) return;

    for (int i = 0; i < itens.Get_Tamanho(); i++) {
        Ranking& resultado = itens.Get_Item(i);
        std::cout << "Q " << i+1 << " " << resultado.id_item
                  << " " << std::fixed << std::setprecision(2)
                  << resultado.pontuacao << std::endl;
    }
}

void Terminal_Configuracao(Forja& j, std::stringstream& ss) {
    char ordenacao, modo_build;
    ss >> ordenacao; ss >> modo_build;

    if ((ordenacao == 'I' || ordenacao == 'M' || ordenacao == 'Q') &&
        (modo_build == 'I' || modo_build == 'S')) {
        bool imediata = (modo_build == 'I') ? true : false;
        j.Configurar(ordenacao, imediata);
    }
        
}

void Terminal_Imprima_Analise(Forja& j, std::stringstream& ss) {
    std::cout << j.Get_Analise_Total() << std::endl;
}

void Terminal_Media_Operacoes() {
    std::cout << "M - " << tempo_M.total_ms/tempo_M.chamadas << std::endl;
    std::cout << "F - " << tempo_F.total_ms/tempo_F.chamadas << std::endl;
    std::cout << "Z - " << tempo_Z.total_ms/tempo_Z.chamadas << std::endl;
    std::cout << "D - " << tempo_D.total_ms/tempo_D.chamadas << std::endl;
    std::cout << "LI - " << tempo_LI.total_ms/tempo_LI.chamadas << std::endl;
    std::cout << "LA - " << tempo_LA.total_ms/tempo_LA.chamadas << std::endl;
    std::cout << "LH - " << tempo_LH.total_ms/tempo_LH.chamadas << std::endl;
    std::cout << "LF - " << tempo_LF.total_ms/tempo_LF.chamadas << std::endl;
    std::cout << "Q - " << tempo_Q.total_ms/tempo_Q.chamadas << std::endl;
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
    else if (token == "C") Terminal_Configuracao(j, ss);
    else if (token == "P") Terminal_Imprima_Analise(j, ss);
    else std::cout << "Comando invalido!" << std::endl;

}