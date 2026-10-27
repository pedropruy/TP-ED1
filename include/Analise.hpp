#ifndef ANALISE_HPP
#define ANALISE_HPP

#include <iostream>

struct Analise {
    long long celulas_visitadas = 0; // células/posições examinadas em percursos e buscas lineares
    long long comparacoes_chave = 0; // comparações de chave (busca binária, localização de célula)
    long long saltos_ponteiro = 0; // acessos indiretos por ponteiro (modo L)
    long long deslocados = 0; // elementos movidos em vetor para manter a ordem
    long long copiados = 0; // elementos copiados ao crescer um vetor ou copiar uma estrutura
    long long limites_atualizados = 0; // posições do vetor de limites de linha reescritas (CSR)
    long long alocacoes = 0; // new de célula / crescimento de vetor
    long long liberacoes = 0; // delete de célula / vetor antigo liberado
    long long comparacoes_ord = 0; // comparações feitas pelas ordenações (Q, LF)
    long long movimentos_ord = 0; // movimentações feitas pelas ordenações
    long long pico_conversao = 0; // momento mais alto de bytes na conversao
 
    void Zerar() { *this = Analise(); }
 
    Analise& operator+=(const Analise& a) {
        celulas_visitadas += a.celulas_visitadas;
        comparacoes_chave += a.comparacoes_chave;
        saltos_ponteiro += a.saltos_ponteiro;
        deslocados += a.deslocados;
        copiados += a.copiados;
        limites_atualizados += a.limites_atualizados;
        alocacoes += a.alocacoes;
        liberacoes += a.liberacoes;
        comparacoes_ord += a.comparacoes_ord;
        movimentos_ord += a.movimentos_ord;
        pico_conversao += a.pico_conversao;
        return *this;
    }

    Analise& operator/=(const long long num) {
        celulas_visitadas /= num;
        comparacoes_chave /= num;
        saltos_ponteiro /= num;
        deslocados /= num;
        copiados /= num;
        limites_atualizados /= num;
        alocacoes /= num;
        liberacoes /= num;
        comparacoes_ord /= num;
        movimentos_ord /= num;
        pico_conversao /= num;
        return *this;
    }
 
    Analise operator-(const Analise& a) const {
        Analise r;
        r.celulas_visitadas = celulas_visitadas - a.celulas_visitadas;
        r.comparacoes_chave = comparacoes_chave - a.comparacoes_chave;
        r.saltos_ponteiro = saltos_ponteiro - a.saltos_ponteiro;
        r.deslocados = deslocados - a.deslocados;
        r.copiados = copiados - a.copiados;
        r.limites_atualizados = limites_atualizados - a.limites_atualizados;
        r.alocacoes = alocacoes - a.alocacoes;
        r.liberacoes = liberacoes - a.liberacoes;
        r.comparacoes_ord = comparacoes_ord - a.comparacoes_ord;
        r.movimentos_ord = movimentos_ord - a.movimentos_ord;
        r.pico_conversao = pico_conversao - a.pico_conversao;
        return r;
    }

    friend std::ostream& operator<<(std::ostream& os, const Analise& a) {
        os << "Celulas visitadas:    " << a.celulas_visitadas << std::endl
           << "Comparacoes p/ chave: " << a.comparacoes_chave << std::endl
           << "Saltos de ponteiro:   " << a.saltos_ponteiro << std::endl
           << "Celulas deslocadas:   " << a.deslocados << std::endl
           << "Elementos copiados:   " << a.copiados << std::endl
           << "Limites atualizados:  " << a.limites_atualizados << std::endl
           << "Quantas alocacoes:    " << a.alocacoes << std::endl
           << "Quantas liberacoes:   " << a.liberacoes << std::endl
           << "Comparacoes (ord):    " << a.comparacoes_ord << std::endl
           << "Movimentos (ord):     " << a.movimentos_ord << std::endl
           << "Pico de Bytes:        " << a.pico_conversao;
        return os;
    }
};
 
#ifdef ANALISES
    #define CONTA(obj, campo, n) ((obj).campo += (n))
    #define CONTA_VAR(var, n) ((var) += (n))
    #define DEFINE_VAR(obj, campo, n) ((obj).campo += (n))
#else
    #define CONTA(obj, campo, n) ((void)0)
    #define CONTA_VAR(var, n) ((void)0)
    #define DEFINE_VAR(obj, campo, n) ((void)0)
#endif
 
#endif