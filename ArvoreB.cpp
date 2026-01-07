#include "ArvoreB.h"

// --- Implementação do Nó ---
NoB::NoB(int _t, bool _eh_folha) {
    t = _t;
    eh_folha = _eh_folha;
}

int NoB::encontrarChave(int k) {
    int idx = 0;
    while (idx < chaves.size() && chaves[idx] < k) {
        idx++;
    }
    return idx;
}

// ... Métodos de Remoção ...
void NoB::remover(int k) {
    int idx = encontrarChave(k);

    if (idx < chaves.size() && chaves[idx] == k) {
        if (eh_folha)
            removerDaFolha(idx);
        else
            removerDeNaoFolha(idx);
    } 
    else {
        if (eh_folha) {
            // A chave não existe
            return;
        }

        bool flag = (idx == chaves.size());
        
        if (filhos[idx]->chaves.size() < t)
            preencher(idx);

        if (flag && idx > chaves.size())
            filhos[idx - 1]->remover(k);
        else
            filhos[idx]->remover(k);
    }
}

void NoB::removerDaFolha(int idx) {
    chaves.erase(chaves.begin() + idx);
}

void NoB::removerDeNaoFolha(int idx) {
    int k = chaves[idx];

    if (filhos[idx]->chaves.size() >= t) {
        int pred = obterPredecessor(idx);
        chaves[idx] = pred;
        filhos[idx]->remover(pred);
    }
    else if (filhos[idx + 1]->chaves.size() >= t) {
        int suc = obterSucessor(idx);
        chaves[idx] = suc;
        filhos[idx + 1]->remover(suc);
    }
    else {
        fundir(idx);
        filhos[idx]->remover(k);
    }
}

int NoB::obterPredecessor(int idx) {
    NoB* atual = filhos[idx];
    while (!atual->eh_folha)
        atual = atual->filhos[atual->filhos.size() - 1];
    return atual->chaves.back();
}

int NoB::obterSucessor(int idx) {
    NoB* atual = filhos[idx + 1];
    while (!atual->eh_folha)
        atual = atual->filhos[0];
    return atual->chaves[0];
}

void NoB::preencher(int idx) {
    if (idx != 0 && filhos[idx - 1]->chaves.size() >= t)
        pegarEmprestadoAnterior(idx);
    else if (idx != chaves.size() && filhos[idx + 1]->chaves.size() >= t)
        pegarEmprestadoProximo(idx);
    else {
        if (idx != chaves.size())
            fundir(idx);
        else
            fundir(idx - 1);
    }
}

void NoB::pegarEmprestadoAnterior(int idx) {
    NoB* filho = filhos[idx];
    NoB* irmao = filhos[idx - 1];

    filho->chaves.insert(filho->chaves.begin(), chaves[idx - 1]);
    if (!filho->eh_folha)
        filho->filhos.insert(filho->filhos.begin(), irmao->filhos.back());

    chaves[idx - 1] = irmao->chaves.back();
    irmao->chaves.pop_back();
    if (!irmao->eh_folha)
        irmao->filhos.pop_back();
}

void NoB::pegarEmprestadoProximo(int idx) {
    NoB* filho = filhos[idx];
    NoB* irmao = filhos[idx + 1];

    filho->chaves.push_back(chaves[idx]);
    if (!filho->eh_folha)
        filho->filhos.push_back(irmao->filhos[0]);

    chaves[idx] = irmao->chaves[0];
    irmao->chaves.erase(irmao->chaves.begin());
    if (!irmao->eh_folha)
        irmao->filhos.erase(irmao->filhos.begin());
}

void NoB::fundir(int idx) {
    NoB* filho = filhos[idx];
    NoB* irmao = filhos[idx + 1];

    filho->chaves.push_back(chaves[idx]);

    for (int i = 0; i < irmao->chaves.size(); ++i)
        filho->chaves.push_back(irmao->chaves[i]);
    
    if (!filho->eh_folha) {
        for (int i = 0; i < irmao->filhos.size(); ++i)
            filho->filhos.push_back(irmao->filhos[i]);
    }

    chaves.erase(chaves.begin() + idx);
    filhos.erase(filhos.begin() + idx + 1);

    delete irmao;
}

// --- Implementação da Árvore ---
ArvoreB::ArvoreB(int _t) {
    raiz = nullptr;
    t = _t;
}

NoB* ArvoreB::buscar(int k) {
    return (raiz == nullptr) ? nullptr : buscarRecursivo(raiz, k);
}

NoB* ArvoreB::buscarRecursivo(NoB* no, int k) {
    int i = 0;
    while (i < no->chaves.size() && k > no->chaves[i]) {
        i++;
    }
    if (i < no->chaves.size() && k == no->chaves[i]) {
        return no;
    }
    if (no->eh_folha) {
        return nullptr;
    }
    return buscarRecursivo(no->filhos[i], k);
}

void ArvoreB::inserir(int k) {
    if (raiz == nullptr) {
        raiz = new NoB(t, true);
        raiz->chaves.push_back(k);
    } else {
        if (raiz->chaves.size() == 2 * t - 1) {
            NoB* s = new NoB(t, false);
            s->filhos.push_back(raiz);
            dividirFilho(s, 0, raiz);
            int i = 0;
            if (s->chaves[0] < k) i++;
            inserirNaoCheio(s->filhos[i], k);
            raiz = s;
        } else {
            inserirNaoCheio(raiz, k);
        }
    }
}

void ArvoreB::inserirNaoCheio(NoB* x, int k) {
    int i = x->chaves.size() - 1;
    if (x->eh_folha) {
        x->chaves.push_back(0);
        while (i >= 0 && x->chaves[i] > k) {
            x->chaves[i + 1] = x->chaves[i];
            i--;
        }
        x->chaves[i + 1] = k;
    } else {
        while (i >= 0 && x->chaves[i] > k) i--;
        i++;
        if (x->filhos[i]->chaves.size() == 2 * t - 1) {
            dividirFilho(x, i, x->filhos[i]);
            if (x->chaves[i] < k) i++;
        }
        inserirNaoCheio(x->filhos[i], k);
    }
}

void ArvoreB::dividirFilho(NoB* x, int i, NoB* y) {
    NoB* z = new NoB(y->t, y->eh_folha);
    
    for (int j = 0; j < t - 1; j++)
        z->chaves.push_back(y->chaves[j + t]);

    if (!y->eh_folha) {
        for (int j = 0; j < t; j++)
            z->filhos.push_back(y->filhos[j + t]);
    }

    y->chaves.resize(t - 1);
    if (!y->eh_folha) y->filhos.resize(t);

    x->filhos.insert(x->filhos.begin() + i + 1, z);
    x->chaves.insert(x->chaves.begin() + i, y->chaves[t - 1]);
}

void ArvoreB::remover(int k) {
    if (!raiz) {
        cout << "A árvore está vazia.\n";
        return;
    }
    raiz->remover(k);

    if (raiz->chaves.size() == 0) {
        NoB* tmp = raiz;
        if (raiz->eh_folha)
            raiz = nullptr;
        else
            raiz = raiz->filhos[0];
        delete tmp;
    }
}

void ArvoreB::exibirBFS() {
    if (!raiz) {
        cout << "Arvore Vazia" << endl;
        return;
    }

    queue<NoB*> fila;
    fila.push(raiz);
    
    int nivel = 0;
    while (!fila.empty()) {
        int contagemNivel = fila.size();
        cout << "Nivel " << nivel << ": ";
        
        while (contagemNivel > 0) {
            NoB* no = fila.front();
            fila.pop();
            
            cout << "[ ";
            for (int chave : no->chaves) cout << chave << " ";
            cout << "] ";

            if (!no->eh_folha) {
                for (NoB* filho : no->filhos) {
                    fila.push(filho);
                }
            }
            contagemNivel--;
        }
        cout << endl;
        nivel++;
    }
}

void ArvoreB::salvarArvore(string nomeArquivo) {
    ofstream arq(nomeArquivo);
    if (!arq.is_open()) {
        cout << "Erro ao abrir arquivo para salvar.\n";
        return;
    }
    arq << t << endl;
    salvarNo(raiz, arq);
    arq.close();
    cout << "Arvore salva em " << nomeArquivo << endl;
}

void ArvoreB::salvarNo(NoB* no, ofstream& arq) {
    if (!no) {
        arq << "#" << endl;
        return;
    }
    arq << no->eh_folha << " " << no->chaves.size();
    for (int k : no->chaves) arq << " " << k;
    arq << endl;

    if (!no->eh_folha) {
        for (NoB* filho : no->filhos) {
            salvarNo(filho, arq);
        }
    }
}

void ArvoreB::carregarArvore(string nomeArquivo) {
    ifstream arq(nomeArquivo);
    if (!arq.is_open()) {
        cout << "Arquivo nao encontrado.\n";
        return;
    }
    raiz = nullptr; 
    
    int t_lido;
    arq >> t_lido;
    this->t = t_lido;
    
    raiz = carregarNo(arq);
    arq.close();
    cout << "Arvore carregada com sucesso." << endl;
}

NoB* ArvoreB::carregarNo(ifstream& arq) {
    bool eh_folha;
    int num_chaves;
    if (!(arq >> eh_folha >> num_chaves)) return nullptr;

    NoB* no = new NoB(t, eh_folha);
    for (int i = 0; i < num_chaves; i++) {
        int k;
        arq >> k;
        no->chaves.push_back(k);
    }

    if (!eh_folha) {
        for (int i = 0; i <= num_chaves; i++) {
            NoB* filho = carregarNo(arq);
            no->filhos.push_back(filho);
        }
    }
    return no;
}