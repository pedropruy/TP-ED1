#include "../include/Forja.hpp"
#include <cmath>
#include <iomanip>
#include <chrono>

const std::string& Forja::Get_Nome_Item(int ind) {
    if (ind < 0 || ind >= itens.Get_Tamanho())
        throw "Indices invalidos!";
    return itens.Get_Item(ind).Get_Nome();
}

const std::string& Forja::Get_Nome_Atributo(int ind) {
    if (ind < 0 || ind >= atributos.Get_Tamanho())
        throw "Indices invalidos!";
    return atributos.Get_Item(ind).Get_Nome();
}

const std::string& Forja::Get_Nome_Aventureiro(int ind) {
    if (ind < 0 || ind >= aventureiros.Get_Tamanho())
        throw "Indices invalidos!";
    return aventureiros.Get_Item(ind).Get_Nome();
}

Analise Forja::Get_Analise_Catalogo() { return catalogo.Get_Analise(); }
Analise Forja::Get_Analise_Forja() const { return ana; }

Analise Forja::Get_Analise_Total() {
    Analise total = catalogo.Get_Analise();
    total += ana;
    total += ordem.ana_ord;
    total += encomendas.Get_Analise();
    return total;
}

long long Forja::Bytes_Fila() const { return encomendas.Bytes_Usados(); }

void Forja::Zerar_Analise() {
    catalogo.Zerar_Analise();
    ana.Zerar();
    ordem.ana_ord.Zerar();
    encomendas.Zerar_Analise();
}

void Forja::Configurar(char _ordenacao, bool _build_imediata) {
    ordenacao = _ordenacao; build_imediata = _build_imediata;
}

void Forja::Ordenar(Lista<Ranking>& lista) {
    switch (ordenacao) {
        case 'M': ordem.MergeSort(lista); break;
        case 'Q': ordem.QuickSort(lista); break;
        default:  ordem.Insercao(lista);  break;
    }
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
    if (build_imediata) {
        int valor_antigo = catalogo.Get_Celula(id_i, id_a);
        int diferenca = valor - valor_antigo;
        if (diferenca != 0) {
            for (int i = 0; i < aventureiros.Get_Tamanho(); i++) {
                Aventureiro& a = aventureiros.Get_Item(i);
                Lista<unsigned int> build;
                a.Copia_Build(build);
                CONTA(ana, celulas_visitadas, 1 + build.Get_Tamanho()); // 1 aventureiro + sua build
                int ocorrencias = 0;
                for (int j = 0; j < build.Get_Tamanho(); j++)
                    if (build.Get_Item(j) == (unsigned int)id_i)
                        ocorrencias++;
                if (ocorrencias > 0)
                    a.Soma_Atributo(id_a, diferenca * ocorrencias);
            }
        }
    }
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

    Lista<Consulta> lista;
    while (forjadas < turnos && encomendas.Get_Tamanho() > 0) {
        p = encomendas.Desenfileira();
        Aventureiro &a = aventureiros.Get_Item(p.id_aventureiro);
        
        if (build_imediata) {
            catalogo.Percurso_Linha(p.id_item, lista);
            CONTA(ana, celulas_visitadas, lista.Get_Tamanho());
            a.Atualizar_Atributo(lista, 1);
            lista.Limpa();
        }

        a.Equipar_Item(p.id_item);
        atendidas.Insere_Final(p);
        forjadas++;
    }
    return forjadas;
}
        
int Forja::Desequipar(int id_v) {
    if (id_v < 0 || id_v >= aventureiros.Get_Tamanho()) throw "Indices invalidos!";
    Aventureiro& a = aventureiros.Get_Item(id_v);
    if (a.Get_Tamanho_Build() == 0) return -1;
    int id_item = a.Desequipar_Item();

    if (build_imediata) {
        Lista<Consulta> lista;
        catalogo.Percurso_Linha(id_item, lista);
        CONTA(ana, celulas_visitadas, lista.Get_Tamanho());
        a.Atualizar_Atributo(lista, -1);
    }

    return id_item;
}
        
void Forja::Consulta_Item(int id_i, Lista<Consulta>& lista) const {
    catalogo.Percurso_Linha(id_i, lista);
}
        
void Forja::Consulta_Atributo(int id_a, Lista<Consulta>& lista) const {
    catalogo.Percurso_Coluna(id_a, lista);

}
    
void Forja::Consulta_Atributo_Intervalo(int id_a, int min, int max, Lista<Consulta>& lista) const {
    lista.Limpa();
    Lista<Consulta> total;
    catalogo.Percurso_Coluna(id_a, total);

    // Caso intervalo abrangir 0, temos que incluir os ids em total
    if (min <= 0 && max >= 0) {
        bool* tem_valor = new bool[itens.Get_Tamanho()]{false};
        CONTA(ana, alocacoes, 1);
        // inicializa N posições, marca os levantados e varre os N itens
        CONTA(ana, celulas_visitadas, total.Get_Tamanho() + 2 * itens.Get_Tamanho());
        for (int i = 0; i < total.Get_Tamanho(); i++) {
            tem_valor[total.Get_Item(i).id_objeto] = true;
        }
        for (int i = 0; i < itens.Get_Tamanho(); i++) {
            if (!tem_valor[i]) {
                Consulta c = {i, 0};
                total.Insere_Final(c);
            }
        }
        delete[] tem_valor;
        CONTA(ana, liberacoes, 1);
    }

    int tam = total.Get_Tamanho();
    if (tam == 0) return;

    // Extrai para um vetor temporario para ordenar por valor
    Consulta* consultas = new Consulta[tam];
    for (int i = 0; i < tam; i++) consultas[i] = total.Get_Item(i);
    CONTA(ana, alocacoes, 1); CONTA(ana, celulas_visitadas, tam);

    for (int i = 1; i < tam; i++) {
        Consulta chave = consultas[i];
        int j = i - 1;
        while (j >= 0 && consultas[j].valor > chave.valor) {
            CONTA(ordem.ana_ord, comparacoes_ord, 1); CONTA(ordem.ana_ord, movimentos_ord, 1);
            consultas[j + 1] = consultas[j];
            j--;
        }
        if (j >= 0) CONTA(ordem.ana_ord, comparacoes_ord, 1); // a comparação que encerrou o laço
        CONTA(ordem.ana_ord, movimentos_ord, 1);
        consultas[j + 1] = chave;
    }

    int id_min = Busca_Binaria(min, consultas, tam),
        id_max = Busca_Binaria(max, consultas, tam, true);

    // Insere vetor consulta na lista oficial
    if (id_min != -1 && id_max != -1 && id_min <= id_max)
        for (int i = id_min; i <= id_max; i++) 
            lista.Insere_Final(consultas[i]);
    delete[] consultas;
    CONTA(ana, liberacoes, 1);

   ordem.QuickSort(lista);
}

int Forja::Busca_Binaria(int valor, Consulta* c, int tam, bool maior) const {
    int esq = 0, dir = tam - 1, id = -1;
    
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        CONTA(ana, comparacoes_chave, 1);
        if(maior) {
            if (c[meio].valor <= valor) {
                id = meio;      // Salva candidato
                esq = meio + 1;     // Continua buscando mais à direita
            } else dir = meio - 1;
        } else {
            if (c[meio].valor >= valor) {
                id = meio;      // Salva candidato
                dir = meio - 1;     // Continua buscando mais à esquerda
            } else esq = meio + 1;
        }
    }

    return id;
}
        
void Forja::Consulta_Build(int id_v, Lista<Consulta>& lista) {
    Obter_Build(id_v, lista);
}

void Forja::Consulta_Recomendacao(int id_v, int n, Lista<Metrica>& metricas,
                                  Lista<Ranking>& recomendacao, bool sinergia) {
    Lista<Consulta> atributos_v;
    Obter_Build(id_v, atributos_v);
    int i;
    
    double norma_build = 0;
    if (sinergia) {
        // Calcula raiz do tercerio somatório de sinergia
        for (i = 0; i < atributos_v.Get_Tamanho(); i++) {
            double valor = atributos_v.Get_Item(i).valor;
            norma_build += valor * valor;
        }
        norma_build = sqrt(norma_build);
    }

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

        Ordenar(aux);

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

    Ordenar(total);
    
    recomendacao.Limpa();
    for (j = 0; j < N && recomendacao.Get_Tamanho() < n; j++)
        if (!equipado.Get_Item(total.Get_Item(j).id_item))
            recomendacao.Insere_Final(total.Get_Item(j));
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

    int T = atributos.Get_Tamanho();
    if (T == 0) return 1.0;

    Lista<Consulta> lista; // Guarda id_atributos e valor do item
    catalogo.Percurso_Linha(id_i, lista);
    if (lista.Get_Tamanho() == 0) return 1.0;

    double media = Poder(id_i) / T;

    // Atributos sem célula: modificador igual a zero.
    int zeros = T - lista.Get_Tamanho();
    double somatorio = zeros * media * media; // Σ (0 - média)² = média² * qnts_zeros

    // Atributos com modificadores não nulos.
    for (int i = 0; i < lista.Get_Tamanho(); i++) {
        double v = lista.Get_Item(i).valor;
        double diferenca = v - media;
        somatorio += diferenca * diferenca;
    }

    double variancia = somatorio / T;
    if (variancia < 0) variancia = 0; // ruído de ponto flutuante

    return 1.0 / (1.0 + sqrt(variancia));
}

double Forja::Sinergia(int id_v, int id_i, Lista<Consulta>& build, double norma_build) {
    if (id_v < 0 || id_v >= aventureiros.Get_Tamanho() ||
        id_i < 0 || id_i >= itens.Get_Tamanho())
        throw "Indices invalidos!";
    if (build.Get_Tamanho() == 0) return 0.0;
    
    Lista<Consulta> i_atributo;
    catalogo.Percurso_Linha(id_i, i_atributo);
    if (i_atributo.Get_Tamanho() == 0) return 0.0;
    
     double vb = 0.0, vv = 0.0;
    // Calculando valor do atributo ao quadrado
    CONTA(ana, celulas_visitadas, i_atributo.Get_Tamanho());
    for (int k = 0; k < i_atributo.Get_Tamanho(); k++) {
        double v = i_atributo.Get_Item(k).valor; vv += v * v;
    }

    // atri_a = todos os atributos, atri_b = atributo não zero de aventureiro
    int atri_a = 0, atri_b = 0;
    while (atri_a < i_atributo.Get_Tamanho() && atri_b < build.Get_Tamanho()) {
        int id_a = i_atributo.Get_Item(atri_a).id_objeto,
            id_b = build.Get_Item(atri_b).id_objeto;
        CONTA(ana, comparacoes_chave, 1); // um passo da intercalação
        // Faremos checagem de três casos, pois se algum for zero, somatória não é alterada
        // Se item e build alteram esse atributo
        if (id_a == id_b) {
            vb += (double) (i_atributo.Get_Item(atri_a).valor * build.Get_Item(atri_b).valor);
            atri_a++; atri_b++;
        // Se apenas item altera atributo
        } else if (id_a < id_b) atri_a++;
        // Se apenas aventureiro teve atributo alterado
        else atri_b++;
    }

    // norma_build = bb
    if (vv == 0.0 || norma_build == 0.0) return 0.0;
    return vb / (sqrt(vv) * norma_build);
}

void Forja::Obter_Build(int id_v, Lista<Consulta>& build) {
    build.Limpa();

    if (build_imediata) {
        aventureiros.Get_Item(id_v).Copia_Atributo_Build(build);
        CONTA(ana, celulas_visitadas, build.Get_Tamanho()); // só o que foi devolvido
    } else {
        Lista<unsigned int> itens_equipados;
        aventureiros.Get_Item(id_v).Copia_Build(itens_equipados);
        int tam_atributos = atributos.Get_Tamanho();
        // Cria vetor de zera ele automaticamente
        int* build_temporario = new int[tam_atributos]{};
        CONTA(ana, alocacoes, 1);
        // copia da build + zerar o vetor (T) + varredura final (T)
        CONTA(ana, celulas_visitadas, itens_equipados.Get_Tamanho() + 2 * tam_atributos);

        for (int i = 0; i < itens_equipados.Get_Tamanho(); i++)
            catalogo.Somar_Linha(itens_equipados.Get_Item(i), build_temporario);

        for (int i = 0; i < tam_atributos; i++)
            if (build_temporario[i] != 0) {
                Consulta c = {i, build_temporario[i]};
                build.Insere_Final(c);
            } 
        delete[] build_temporario;
        CONTA(ana, liberacoes, 1);
    }
}