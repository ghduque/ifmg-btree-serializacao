#ifndef ARVOREB_H
#define ARVOREB_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

// --- Estrutura do Nó ---
class NoB {
public:
    vector<int> chaves;
    vector<NoB*> filhos;
    bool eh_folha;
    int t; // Grau mínimo

    NoB(int _t, bool _eh_folha);

    // Função auxiliar para encontrar índice
    int encontrarChave(int k);

    // Métodos de Remoção
    void remover(int k);
    void removerDaFolha(int idx);
    void removerDeNaoFolha(int idx);
    int obterPredecessor(int idx);
    int obterSucessor(int idx);
    void preencher(int idx);
    void pegarEmprestadoAnterior(int idx);
    void pegarEmprestadoProximo(int idx);
    void fundir(int idx);

    friend class ArvoreB;
};

// --- Classe da Árvore B ---
class ArvoreB {
    NoB* raiz;
    int t; // Grau mínimo

public:
    ArvoreB(int _t);

    // Métodos Principais
    NoB* buscar(int k);
    void inserir(int k);
    void remover(int k);
    void exibirBFS();
    
    // Serialização
    void salvarArvore(string nomeArquivo);
    void carregarArvore(string nomeArquivo);

private:
    // Métodos Auxiliares Privados
    NoB* buscarRecursivo(NoB* no, int k);
    void inserirNaoCheio(NoB* x, int k);
    void dividirFilho(NoB* x, int i, NoB* y);
    void salvarNo(NoB* no, ofstream& arq);
    NoB* carregarNo(ifstream& arq);
};

#endif