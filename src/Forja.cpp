#include "Forja.hpp"
#include <cmath>

const std::string& Forja::Nome_Item(int ind) {
    if (ind < 0 || ind >= itens.Get_Tamanho())
        throw "Indices invalidos!";
    return itens.Get_Item(ind).Get_Nome();
}

const std::string& Forja::Nome_Atributo(int ind) {
    if (ind < 0 || ind >= atributos.Get_Tamanho())
        throw "Indices invalidos!";
    return atributos.Get_Item(ind).Get_Nome();
}

const std::string& Forja::Nome_Aventureiro(int ind) {
    if (ind < 0 || ind >= aventureiros.Get_Tamanho())
        throw "Indices invalidos!";
    return aventureiros.Get_Item(ind).Get_Nome();
}

char Forja::Modo(char modo) { return catalogo.Trocar_de_Modo(modo); }

int Forja::Cadastro_Atributo(const std::string& nome) {
    int id_a = atributos.Get_Tamanho();
    atributos.Insere_Final(Atributo(id_a, nome));
    catalogo.Novo_Atributo();
    return id_a;
}
       
int Forja::Cadastro_Item(const std::string& nome) {
    int id_i = itens.Get_Tamanho();
    itens.Insere_Final(Item(id_i, nome));
    catalogo.Novo_Item();
    return id_i;
}
        
void Forja::Definir_Modificador(int id_i, int id_a, int valor) {
    if (id_i < 0 || id_i >= itens.Get_Tamanho()
     || id_a < 0 || id_a >= atributos.Get_Tamanho()) throw "Indices invalidos!";
    catalogo.Set_Celula(id_i, id_a, valor);
}
        
int Forja::Cadastro_Aventureiro(const std::string& nome) {
    int id_v = aventureiros.Get_Tamanho();
    aventureiros.Insere_Final(Aventureiro(id_v, nome));
    return id_v;
}
        
int Forja::Adiciona_Encomenda(int id_v, int id_i) {
    if (id_v < 0 || id_v >= aventureiros.Get_Tamanho()
     || id_i < 0 || id_i >= itens.Get_Tamanho()) throw "Indices invalidos!";
    Pedido p; p.id_aventureiro = id_v; p.id_item = id_i;
    encomendas.Enfileira(p);
    return encomendas.Get_Tamanho();
}
        
int Forja::Turnos_de_Trabalho(int turnos, Lista<Pedido>& atendidas) {
    if (turnos < 0) throw "Numero de turnos invalidos!";
    Pedido p;
    int forjadas = 0;

    while (forjadas < turnos && encomendas.Get_Tamanho() > 0) {
        p = encomendas.Desenfileira();
        aventureiros.Get_Item(p.id_aventureiro).Equipar_Item(p.id_item);
        atendidas.Insere_Final(p);
        forjadas++;
    }
    return forjadas;
}
        
int Forja::Desequipar(int id_v) {
    if (id_v < 0 || id_v >= aventureiros.Get_Tamanho()) throw "Indices invalidos!";
    Aventureiro& a = aventureiros.Get_Item(id_v);
    if (a.Get_Tamanho_Build() == 0) return -1;
    return itens.Get_Item(a.Desequipar_Item()).Get_Id();
}
        
void Forja::Consulta_Item(int id_i, Lista<Consulta>& lista) const {
    catalogo.Percurso_Linha(id_i, lista);
}
        
void Forja::Consulta_Atributo(int id_a, Lista<Consulta>& lista) const {
    catalogo.Percurso_Coluna(id_a, lista);

}
        
void Forja::Consulta_Atributo_Intervalo(int id_a, int min, int max, Lista<Consulta>& lista) const {
    catalogo.Percurso_Linha(id_a, lista);
    std::cout << "Tem que fazer algo!" << std::endl;

    // Função para ordenar lista entre válidos e inválidos
}
        
void Forja::Consulta_Build(int id_v, Lista<Consulta>& lista) {
    Obter_Build(id_v, lista);
}

void Forja::Consulta_Recomendacao(int id_v, int n, Lista<Metrica>& metricas,
                                  Lista<Ranking>& recomendacao) {
    Lista<Consulta> atributos_v;
    Obter_Build(id_v, atributos_v);
    int i; double norma_build = 0;
    for (i = 0; i < atributos_v.Get_Tamanho(); i++) {
        double valor = atributos_v.Get_Item(i).valor;
        norma_build += valor * valor;
    }
    norma_build = sqrt(norma_build);

    // total = lista que nunca será ordenada
    Lista<Ranking> aux, total;
    for (i = 0; i < itens.Get_Tamanho(); i++) {
        Ranking r; r.id_item = i; r.pontuacao = 0.0;
        aux.Insere_Final(r); total.Insere_Final(r);
    }

    int j, N = itens.Get_Tamanho();
    for (i = 0; i < metricas.Get_Tamanho(); i++) {
        Metrica& m = metricas.Get_Item(i);
        for (j = 0; j < N; j++) {
            // variável r é usada para alterar o valor dos itens, mas não os ids
            Ranking& r = aux.Get_Item(j);
            if (m.enum_metrica == PODER) { r.pontuacao = Poder(r.id_item);
            } else if (m.enum_metrica == EQUILIBRIO) { r.pontuacao = Equilibrio(r.id_item);
            } else r.pontuacao = Sinergia(id_v, r.id_item, atributos_v, norma_build);
        }
        // inserção(aux) 
        Insercao(aux);

        for (j = 0; j < N; j++) {
            total.Get_Item(aux.Get_Item(j).id_item).pontuacao += (N-j) * m.peso;
        }
    }

    Lista<bool> equipado;  // guarda todos os itens e define se eles estão equipados
    Lista<unsigned int> build;  // guarda id dos itens equipados
    aventureiros.Get_Item(id_v).Copia_Build(build);
    for (i = 0; i < N; i++) equipado.Insere_Final(false);
    for (i = 0; i < build.Get_Tamanho(); i++)
        equipado.Get_Item(build.Get_Item(i)) = true;

    Insercao(total);
    recomendacao.Limpa();
    for (j = 0; j < N && recomendacao.Get_Tamanho() < n; j++)
        if (!equipado.Get_Item(total.Get_Item(j).id_item))
            recomendacao.Insere_Final(total.Get_Item(j));
}

void Forja::Insercao(Lista<Ranking>& lista) {
    int i, j;
    Ranking r;
    
    for (i = 1; i < lista.Get_Tamanho(); i++) {
        r = lista.Get_Item(i);
        j = i - 1;

        // Round assim garante que estaremos comparando até 6 casas decimais
        long long val_r = std::round(r.pontuacao * 1000000.0);
        while (j >= 0) {
            Ranking item_j = lista.Get_Item(j);            
            long long val_j = std::round(item_j.pontuacao * 1000000.0);

            bool deve_trocar = false;

            // Compara valor e id
            if (val_r > val_j) deve_trocar = true;
            else if (val_r == val_j && r.id_item < item_j.id_item)
                deve_trocar = true;

            if (deve_trocar) {
                lista.Set_Item(item_j, j + 1); j--;
            } else break;
        }
        // Insere o r na posição onde foi trocada
        lista.Set_Item(r, j+1);
    }
}

void Forja::Imprime() const { catalogo.Imprime(); }

double Forja::Poder(int id_i) {
    if (id_i < 0 || id_i >= itens.Get_Tamanho())
        throw "Indices invalidos!";
    Lista<Consulta> lista;
    catalogo.Percurso_Linha(id_i, lista);
    double total = 0;
    for(int i = 0; i < lista.Get_Tamanho(); i++) {
        Consulta& c = lista.Get_Item(i);
        total += (double)c.valor; 
    }
    return total;
}

double Forja::Equilibrio(int id_i) {
    if (id_i < 0 || id_i >= itens.Get_Tamanho())
        throw "Indices invalidos!";
    if (atributos.Get_Tamanho() == 0) return 1.0;

    Lista<Consulta> lista; // Guarda id_atributos e valor do item
    catalogo.Percurso_Linha(id_i, lista);
    if (lista.Get_Tamanho() == 0) return 1.0;

    /*double media = Poder(id_i) / atributos.Get_Tamanho();
    Consulta c = lista.Remove_Final();
    double somatorio = 0;
    for (int i = atributos.Get_Tamanho()-1; i >= 0; i--) {
        if (c.id_objeto == i) {
            somatorio += (c.valor - media)*(c.valor - media);
            if (lista.Get_Tamanho() > 0) c = lista.Remove_Final();
            else c.id_objeto = -1; // id negativo nunca irá passar do primeiro if
        } else somatorio += (media*media);
    }

    somatorio /= atributos.Get_Tamanho();
    if (somatorio < 0) somatorio = 0;
    return 1.0 / (1.0 + sqrt(somatorio));*/

    double s1 = 0, s2 = 0;
    for (int k = 0; k < lista.Get_Tamanho(); k++) {
        double v = lista.Get_Item(k).valor;
        s1 += v; s2 += v * v;
    }
    double T = atributos.Get_Tamanho();
    double media = s1 / T;
    double variancia = s2 / T - media * media;
    if (variancia < 0) variancia = 0; // ruído de ponto flutuante
    return 1.0 / (1.0 + sqrt(variancia));
}

// Build não é passado por referência porque iremos usar build por item
double Forja::Sinergia(int id_v, int id_i, Lista<Consulta> build, double norma_build) {
    if (id_v < 0 || id_v >= aventureiros.Get_Tamanho() ||
        id_i < 0 || id_i >= itens.Get_Tamanho())
        throw "Indices invalidos!";
    if (build.Get_Tamanho() == 0) return 0.0;
    
    Lista<Consulta> item;
    catalogo.Percurso_Linha(id_i, item);
    if (item.Get_Tamanho() == 0) return 0.0;
    
    /*Consulta i = item.Remove_Final();
    Consulta b = build.Remove_Final();
    double somatorio_vb = 0, somatorio_vv = 0, somatorio_bb = 0;
    double valor_i, valor_b;
    for (int k = atributos.Get_Tamanho()-1; k >= 0; k--) {
        // Checa se id bate com k associa valor e passa para o valor anterior
        if (i.id_objeto == k) {
            valor_i = i.valor;
            if (item.Get_Tamanho() > 0) i = item.Remove_Final();
            else i.id_objeto = -1; // id negativo nunca irá passar do primeiro if
        } else valor_i = 0;
        if (b.id_objeto == k) {
            valor_b = b.valor;
            if (build.Get_Tamanho() > 0) b = build.Remove_Final();
            else b.id_objeto = -1; // id negativo nunca irá passar do primeiro if
        } else valor_b = 0;

        // Se o valor for diferente de zero adiciona ao somatório
        if (valor_i != 0 || valor_b != 0) somatorio_vb += valor_i*valor_b;
        if (valor_i != 0) somatorio_vv += valor_i*valor_i;
        if (valor_b != 0) somatorio_bb += valor_b*valor_b;
    }
    return somatorio_vb / (sqrt(somatorio_vv)*sqrt(somatorio_bb));*/
    int a = 0, b = 0; double vb = 0.0, vv = 0.0;
    for (int k = 0; k < item.Get_Tamanho(); k++) {
        double v = item.Get_Item(k).valor; vv += v * v;
    }
    while (a < item.Get_Tamanho() && b < build.Get_Tamanho()) {
        int ia = item.Get_Item(a).id_objeto, ib = build.Get_Item(b).id_objeto;
        if (ia == ib) {
            vb += (double)item.Get_Item(a).valor * build.Get_Item(b).valor;
            a++; b++;
        } else if (ia < ib) a++;
        else b++;
    }
    if (vv == 0.0 || norma_build == 0.0) return 0.0;
    return vb / (sqrt(vv) * norma_build);
}

void Forja::Obter_Build(int id_v, Lista<Consulta>& build) {
    build.Limpa();

    Lista<unsigned int> itens_equipados;
    aventureiros.Get_Item(id_v).Copia_Build(itens_equipados);
    int tam_atributos = atributos.Get_Tamanho();
    int* build_temporario = new int[tam_atributos];
    for (int i = 0; i < tam_atributos; i++)
        build_temporario[i] = 0;
    for (int i = 0; i < itens_equipados.Get_Tamanho(); i++)
        catalogo.Somar_Linha(itens_equipados.Get_Item(i), build_temporario);

    Consulta c;
    for (int i = 0; i < tam_atributos; i++)
        if (build_temporario[i] != 0) {
            c.id_objeto = i; c.valor = build_temporario[i];
            build.Insere_Final(c);
        } 
    delete[] build_temporario;
}