#include <iostream>
#include <random>    // Biblioteca moderna para random
#include <vector>
#include <set>
#include <algorithm> // Para shuffle
#include "ArvoreB.h" // Inclui nossa árvore

using namespace std;

// --- Função do Teste Automatizado (Requisito da Imagem) ---
void realizarTesteAutomatizado() {
    cout << "\n======================================================\n";
    cout << "      INICIANDO TESTE AUTOMATIZADO (500 CHAVES)       ";
    cout << "\n======================================================\n";

    ArvoreB arvore(5); // Árvore com grau t=5
    vector<int> chavesGeradas;
    
    // --- 1. Configuração do Gerador Aleatório (Mersenne Twister) ---
    // Muito melhor estatisticamente que o rand() antigo
    random_device rd;  
    mt19937 gen(rd()); 
    uniform_int_distribution<> distrib(1, 20000); // Gera números entre 1 e 20000

    // --- Passo 1: Inserção de 500 chaves ---
    cout << "\n[PASSO 1] Gerando e Inserindo 500 chaves unicas...\n";
    
    set<int> unicos; // Set garante unicidade
    while (unicos.size() < 500) {
        unicos.insert(distrib(gen));
    }
    
    for (int chave : unicos) {
        chavesGeradas.push_back(chave);
        arvore.inserir(chave);
    }
    cout << "-> Sucesso: 500 chaves inseridas.\n";

    // --- Passo 2: Busca de chaves aleatórias ---
    cout << "\n[PASSO 2] Testando busca em 20 chaves aleatorias...\n";
    // Embaralha o vetor para pegar chaves aleatórias que sabemos que existem
    shuffle(chavesGeradas.begin(), chavesGeradas.end(), gen);
    
    bool buscaOk = true;
    for (int i = 0; i < 20; i++) {
        int alvo = chavesGeradas[i];
        if (arvore.buscar(alvo) == nullptr) {
            cout << "ERRO: Chave " << alvo << " deveria existir mas nao foi encontrada!\n";
            buscaOk = false;
        }
    }
    if (buscaOk) cout << "-> Sucesso: Todas as 20 chaves foram encontradas.\n";

    // --- Passo 3: Exclusão de parte das chaves (50 chaves) ---
    cout << "\n[PASSO 3] Removendo 50 chaves aleatorias...\n";
    int qtdRemover = 50;
    for (int i = 0; i < qtdRemover; i++) {
        int alvo = chavesGeradas[i]; // Como embaralhamos antes, pegar os primeiros 50 é aleatório
        arvore.remover(alvo);
    }
    // Removemos essas chaves do nosso vetor de controle também para não buscar depois
    chavesGeradas.erase(chavesGeradas.begin(), chavesGeradas.begin() + qtdRemover);
    cout << "-> Sucesso: 50 chaves removidas.\n";

    // --- Passo 4: Impressão BFS ---
    cout << "\n[PASSO 4] Exibindo Arvore em BFS (Parcial)...\n";
    // Nota: Vai imprimir 450 chaves, prepare o terminal
    arvore.exibirBFS(); 

    // --- Passo 5: Serialização ---
    cout << "\n[PASSO 5] Salvando arvore em 'teste_auto.txt'...\n";
    arvore.salvarArvore("teste_auto.txt");
    
    // --- Passo 6: Desserialização e Verificação ---
    cout << "\n[PASSO 6] Recarregando em uma NOVA instancia de arvore...\n";
    ArvoreB arvoreRecarregada(5); 
    arvoreRecarregada.carregarArvore("teste_auto.txt");
    
    cout << "-> Verificando integridade (buscando 10 chaves restantes)...\n";
    bool consistenciaOk = true;
    for (int i = 0; i < 10; i++) {
        // chavesGeradas[i] contém apenas chaves que NÃO foram removidas
        if (arvoreRecarregada.buscar(chavesGeradas[i]) == nullptr) {
            cout << "ERRO FATAL: Chave " << chavesGeradas[i] << " sumiu apos carregar do arquivo.\n";
            consistenciaOk = false;
        }
    }
    
    if (consistenciaOk) {
        cout << "-> SUCESSO TOTAL: A arvore recarregada esta consistente.\n";
    }
    
    cout << "\n======================================================\n";
    cout << "              FIM DO TESTE AUTOMATIZADO               \n";
    cout << "======================================================\n";
}

int main() {
    int opcao;
    
    cout << "Selecione o modo de operacao:\n";
    cout << "1. Menu Interativo (Inserir manual, Remover manual, etc)\n";
    cout << "2. TESTE AUTOMATIZADO (Requisito do Trabalho: 500 chaves)\n";
    cout << "Escolha: ";
    cin >> opcao;

    if (opcao == 2) {
        realizarTesteAutomatizado();
    } else {
        // Menu Manual Original
        ArvoreB arvore(5);
        int op, valor;
        do {
             cout << "\n--- MENU MANUAL ---\n";
             cout << "1. Inserir\n2. Remover\n3. Buscar\n4. BFS\n5. Salvar\n6. Carregar\n0. Sair\nOpcao: ";
             cin >> op;
             if(op==1) { cout<<"Valor: "; cin >> valor; arvore.inserir(valor); }
             else if(op==2) { cout<<"Valor: "; cin >> valor; arvore.remover(valor); }
             else if(op==3) { cout<<"Valor: "; cin >> valor; if(arvore.buscar(valor)) cout << "Encontrado!\n"; else cout << "Nao encontrado!\n"; }
             else if(op==4) { arvore.exibirBFS(); }
             else if(op==5) { arvore.salvarArvore("manual.txt"); }
             else if(op==6) { arvore.carregarArvore("manual.txt"); }
        } while(op != 0);
    }
    
    return 0;
}