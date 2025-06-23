#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include "Pilha.hpp" // O Armazém é composto por Pilhas

class Armazem {
private:
    int id;                // O ID deste armazém
    int numTotalArmazens;  // O número total de armazéns na rede
    Pilha* secoes;         // Ponteiro para um array dinâmico de Pilhas

public:
    // Construtor: cria um armazém e inicializa suas seções
    Armazem();
    Armazem(int id, int numTotalArmazens);

    // Destrutor: libera a memória alocada para as seções
    ~Armazem();

    // Método para inicializar o armazém (se não usar o construtor parametrizado)
    void inicializar(int id, int numTotalArmazens);

    // Retorna a seção (Pilha) correta para um determinado destino
    Pilha& getSecao(int idArmazemDestino);
};

#endif