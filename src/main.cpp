#include "Forja.hpp"
#include "Entrada.hpp"
#include <iostream>
#include <fstream>

int main() {
    /*try {
        Forja f;
        std::cout << f.Modo('L') << std::endl;
        f.Cadastro_Atributo("Forca");
        f.Cadastro_Atributo("Carisma");
        f.Cadastro_Atributo("Furtividade");
        f.Cadastro_Item("MachadoGenerico");
        f.Cadastro_Item("BarbaPosticaDePrestigio");
        f.Cadastro_Item("BotasSilenciosas");
        f.Cadastro_Item("ElmoDoPrimo");
        f.Definir_Modificador(0,0,5);
        f.Definir_Modificador(1,1,7);
        f.Definir_Modificador(1,2,-3);
        f.Definir_Modificador(2,2,4);
        f.Definir_Modificador(3,0,2);
        f.Definir_Modificador(3,1,2);
        f.Imprime();
        std::cout << "================" << std::endl;
        f.Cadastro_Aventureiro("Blibblon");
        f.Cadastro_Aventureiro("Grunilda");
        Lista<Consulta> lista;
        f.Consulta_Item(1,lista);
        for (int i = 0; i < lista.Get_Tamanho(); i++) {
            std::cout << lista.Get_Item(i).id_objeto << ":" << lista.Get_Item(i).valor << std::endl;
        }
        std::cout << "================" << std::endl;
        lista.Limpa();
        f.Consulta_Atributo(2,lista);
        for (int i = 0; i < lista.Get_Tamanho(); i++) {
            std::cout << lista.Get_Item(i).id_objeto << ":" << lista.Get_Item(i).valor << std::endl;
        }
        std::cout << "================" << std::endl;
        f.Adiciona_Encomenda(0,0);
        f.Adiciona_Encomenda(1,1);
        f.Adiciona_Encomenda(0,3);
        Lista<Pedido> pedidos;
        f.Turnos_de_Trabalho(2,pedidos);
        for (int i = 0; i < pedidos.Get_Tamanho(); i++) {
            std::cout << pedidos.Get_Item(i).id_aventureiro << ":" << pedidos.Get_Item(i).id_item << std::endl;
        }

    
    } catch (char const* e) { std::cout << e << std::endl; }*/

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

    std::cout << "fim" << std::endl;

    arq.close();

    return 0;
}