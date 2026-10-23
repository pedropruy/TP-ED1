//#include "Matriz_CSR.cpp"

MatrizEncadeada::MatrizEncadeada(int li, int co) {
    if (li < 0 || co < 0) throw "Tamanho invalido!";
    tamanho = 0;
    for (int i = 0; i < li; i++)
        cabLin.Insere_Final(new Celula{i, -1, 0, nullptr, nullptr});
    for (int j = 0; j < co; j++)
        cabCol.Insere_Final(new Celula{-1, j, 0, nullptr, nullptr});
}

MatrizEncadeada::~MatrizEncadeada() {
    for (int i = 0; i < cabLin.Get_Tamanho(); i++) { // pelas linhas
        Celula* p = cabLin.Get_Item(i);
        while (p != nullptr) {
            Celula* q = p->proxLin; 
            delete p;
            p = q;
        }
    }
    for (int j = 0; j < cabCol.Get_Tamanho(); j++) delete cabCol.Get_Item(j);
}

valor MatrizEncadeada::Get(int i, int j) const {
    if (i < 0 || i >= cabLin.Get_Tamanho()
     || j < 0 || j >= cabCol.Get_Tamanho()) throw "Indice invalido!";
    Celula* ant = AntLinha(i, j);
    Celula* p = ant->proxLin;
    if (p != nullptr && p->col == j) return p->val;
    return 0;
}

void MatrizEncadeada::Get_Dimensoes(int& lin, int& col) {
    lin = this->cabLin.Get_Tamanho(); col = this->cabCol.Get_Tamanho();
}

void MatrizEncadeada::Set(int i, int j, valor v) {
    if (i < 0 || i >= cabLin.Get_Tamanho()
     || j < 0 || j >= cabCol.Get_Tamanho()) throw "Indice invalido!";
    Celula* antL = AntLinha(i, j);
    Celula* antC;
    Celula* p = antL->proxLin;
    if (p != nullptr && p->col == j) {  // ja existe
        if (v != 0) { p->val = v; return; }
        antC = AntColuna(i, j);
        antL->proxLin = p->proxLin; // desliga da linha
        antC->proxCol = p->proxCol; // desliga da coluna
        delete p; tamanho --;
        return;
    }
    if (v == 0) return;
    antC = AntColuna(i, j);
    Celula* nova = new Celula{i, j, v, antL->proxLin, antC->proxCol};
    antL->proxLin = nova; // liga na linha
    antC->proxCol = nova; // liga na coluna
    tamanho++;
}

void MatrizEncadeada::Adicionar_Linha() {
    cabLin.Insere_Final(new Celula{cabLin.Get_Tamanho(), -1, 0, nullptr, nullptr});
}

void MatrizEncadeada::Adicionar_Coluna() {
    cabCol.Insere_Final(new Celula{-1, cabCol.Get_Tamanho(), 0, nullptr, nullptr});
}

int MatrizEncadeada::Soma_Coluna(int j) const {
    if (j < 0 || j >= cabCol.Get_Tamanho()) throw "Indice invalido!";

    valor total = 0;
    // Começa do primeiro nó real da coluna j
    Celula* p = cabCol.Get_Item(j)->proxCol; 
    
    // Desce pela coluna somando os valores
    while (p != nullptr) { total += p->val; p = p->proxCol; }
    
    return total;
}

// ATENÇÂO: obj retornado deve fazer delete em algum momento
valor* MatrizEncadeada::Produto(const valor* v, int dim_v) {
    if (cabCol.Get_Tamanho() != dim_v) throw "Dimensoes incompativeis!"; 
    valor* vetor_res = new valor[cabLin.Get_Tamanho()];

    for (int i = 0; i < cabLin.Get_Tamanho(); i++) {
        vetor_res[i] = 0;
        Celula* p = cabLin.Get_Item(i)->proxLin;
        while (p != nullptr) {
            vetor_res[i] += p->val * v[p->col];
            p = p->proxLin;
        }
    }
    return vetor_res;
}

void MatrizEncadeada::Somar_Linha(int i, int* vetor, int sinal) {
    Celula* p = cabLin.Get_Item(i)->proxLin;
    while (p != nullptr) {
        vetor[p->col] += (p->val * sinal);
        p = p->proxLin;
    }
}

void MatrizEncadeada::Percorrer_Linha(int i, Lista<Consulta>& resultados) {
    Celula* p = cabLin.Get_Item(i)->proxLin;
    while (p != nullptr) {
        Consulta c = {p->col, p->val};
        resultados.Insere_Final(c);
        p = p->proxLin;
    }
}

void MatrizEncadeada::Percorrer_Coluna(int j, Lista<Consulta>& resultados) {
    Celula* p = cabCol.Get_Item(j)->proxCol;
    while (p != nullptr) {
        Consulta c = {p->lin, p->val};
        resultados.Insere_Final(c);
        p = p->proxCol;
    }
}

void MatrizEncadeada::Converter_em_COO(Matriz& m) {
    MatrizCOO* mo = dynamic_cast<MatrizCOO*>(&m);
    if (mo == nullptr) throw "Classe Matriz invalida!";

    if (mo->c != this->cabCol.Get_Tamanho() ||
        mo->l != this->cabLin.Get_Tamanho()) throw "Dimensoes invalidas!";

    // Limpa Lista de tripletas antes de inserir no final da lista
    mo->tripletas.Limpa();

    mo->l = this->cabLin.Get_Tamanho();
    mo->c = this->cabCol.Get_Tamanho();
    Tripleta aux;

    for (int i = 0; i < cabLin.Get_Tamanho(); i++)
        // Acesso proxLin por item da linha
        for (Celula* p = cabLin.Get_Item(i)->proxLin; p != nullptr; p = p->proxLin) {
            aux.lin = p->lin; aux.col = p->col; aux.val = p->val;
            mo->tripletas.Insere_Final(aux);
        }
}

void MatrizEncadeada::Converter_em_CSR(Matriz& m) {
    MatrizCSR* mc = dynamic_cast<MatrizCSR*>(&m);
    if (mc == nullptr) throw "Classe Matriz invalida!";

    if (mc->c != this->cabCol.Get_Tamanho() ||
        mc->l != this->cabLin.Get_Tamanho()) throw "Dimensoes invalidas!";

    mc->colunas.Limpa(); mc->valores.Limpa();
    mc->tamanho = 0;

    mc->linhas.Limpa();
    for (int i = 0; i <= mc->l; i++) {
        mc->linhas.Insere_Final(0);
    }

    for (int i = 0; i < cabLin.Get_Tamanho(); i++) {
        for (Celula* p = cabLin.Get_Item(i)->proxLin; p != nullptr; p = p->proxLin) {
            mc->colunas.Insere_Final(p->col);
            mc->valores.Insere_Final(p->val);
            mc->tamanho++;
            for (int r = p->lin + 1; r <= mc->l; r++)
                mc->linhas.Set_Item(mc->linhas.Get_Item(r) + 1, r);
        }
    }
}

void MatrizEncadeada::Converter_Matriz(Matriz& m, char tipo) {
    switch (tipo) { 
        case 'T':
            Converter_em_COO(m);
            break;
        
        case 'C':
            Converter_em_CSR(m);
            break;

        case 'L':
            break;

        default:
            break;
    }
}

void MatrizEncadeada::Imprime() const {
    for (int i = 0; i < cabLin.Get_Tamanho(); i++) {
        Celula* p = cabLin.Get_Item(i)->proxLin; 
        for (int j = 0; j < cabCol.Get_Tamanho(); j++) {
            if (p != nullptr && p->col == j) {
                std::cout << p->val << " ";
                p = p->proxLin;
            } else std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}

Celula* MatrizEncadeada::AntLinha(int i, int j) const {
    Celula* p = cabLin.Get_Item(i);
    while (p->proxLin != nullptr&& p->proxLin->col < j)
        p = p->proxLin;
    return p;
}

Celula* MatrizEncadeada::AntColuna(int i, int j) const {
    Celula* p = cabCol.Get_Item(j);
    while (p->proxCol != nullptr && p->proxCol->lin < i)
        p = p->proxCol;
    return p;
}