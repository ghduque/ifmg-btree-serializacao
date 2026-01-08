# Implementação de Árvore B (Cormen)

![C++](https://img.shields.io/badge/Linguagem-C%2B%2B-blue?style=for-the-badge&logo=c%2B%2B)
![IFMG](https://img.shields.io/badge/Instituição-IFMG-green?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Concluído-success?style=for-the-badge)

Repositório destinado ao trabalho prático de **Árvores Balanceadas** da disciplina de **Técnicas de Programação** do Instituto Federal de Minas Gerais (IFMG).

Este projeto consiste na implementação completa e orientada a objetos de uma **Árvore B** com grau mínimo **t=5**, seguindo rigorosamente os algoritmos descritos no livro *"Introduction to Algorithms"* (Cormen, Leiserson, Rivest, Stein). O software inclui funcionalidades de manipulação de dados, persistência em arquivo e testes automatizados de carga.

---

## 📋 Tabela de Conteúdos

- [🚀 Funcionalidades do Projeto](#-funcionalidades-do-projeto)
  - [Operações Básicas](#operações-básicas)
  - [Algoritmos Complexos](#algoritmos-complexos)
  - [Persistência e Testes](#persistência-e-testes)
- [📂 Estrutura de Arquivos](#-estrutura-de-arquivos)
- [🛠️ Tecnologias Utilizadas](#️-tecnologias-utilizadas)
- [▶️ Como Executar](#️-como-executar)
- [👤 Autores](#-autores)

---

## 🚀 Funcionalidades do Projeto

### Operações Básicas
- **Inserção (`B-Tree-Insert`):** Adição de chaves inteiras mantendo as propriedades da árvore.
- **Busca (`B-Tree-Search`):** Localização eficiente de chaves na estrutura.
- **Exibição em BFS:** Visualização da árvore nível por nível (Breadth-First Search), permitindo validar a estrutura hierárquica.

### Algoritmos Complexos
- **Divisão de Nós (`Split`):** Tratamento proativo de nós cheios durante a descida (inserção *top-down*).
- **Remoção (`B-Tree-Delete`):** Implementação completa de todos os casos:
  - Remoção em folhas.
  - Remoção em nós internos (uso de predecessor/sucessor).
  - **Redistribuição:** Empréstimo de chaves de irmãos adjacentes (rotação).
  - **Fusão (Merge):** União de nós quando há *underflow*.

### Persistência e Testes
- **Serialização:** Salvamento da estrutura completa da árvore em arquivo de texto.
- **Desserialização:** Reconstrução da árvore a partir do arquivo gerado.
- **Teste Automatizado:** Script integrado que realiza:
  1. Geração e inserção de **500 chaves aleatórias** (Mersenne Twister).
  2. Busca de chaves aleatórias para validação.
  3. Remoção de um subconjunto de chaves.
  4. Validação de integridade após recarregamento do disco.

---

## 📂 Estrutura de Arquivos

O código foi organizado seguindo boas práticas de separação de interface e implementação:

- `main.cpp`: Menu interativo e lógica do teste automatizado com gerador aleatório.
- `ArvoreB.h`: Definição das classes `NoB` e `ArvoreB`.
- `ArvoreB.cpp`: Implementação lógica dos algoritmos do Cormen.
- `arvoreB.txt` / `teste_auto.txt`: Arquivos gerados pela serialização.

---

## 🛠️ Tecnologias Utilizadas

A implementação utiliza recursos modernos da linguagem e ferramentas de desenvolvimento:

- **C++ (Standard Library)** — STL (Vector, Queue, String) e I/O Streams.
- **Library `<random>`** — Geração estatística de números aleatórios de alta qualidade.
- **VS Code** — Ambiente de desenvolvimento.
- **Compilador G++** — Compilação e linkedição do projeto.

---

## ▶️ Como Executar

Para compilar e rodar o projeto em seu ambiente local, utilize os comandos abaixo no terminal:

```bash
# Compilar os arquivos fontes
g++ main.cpp ArvoreB.cpp -o trabalho_arvore

# Executar (Windows)
trabalho_arvore.exe

# Executar (Linux/Mac)
./trabalho_arvore
```

---

## 👤 Autores
Gabriel Henrique Silva Duque

Rafael Gonçalves Oliveira
