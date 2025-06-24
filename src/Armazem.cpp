#include "Armazem.hpp"

// Construtor padrão
Armazem::Armazem() {
    this->id = -1;
    this->numTotalArmazens = 0;
    this->secoes = nullptr;
}

// Construtor principal
Armazem::Armazem(int id, int numTotalArmazens) {
    this->id = id;
    this->numTotalArmazens = numTotalArmazens;
    // Aloca um array com N posições, onde N é o número total de armazéns
    this->secoes = new Pilha[numTotalArmazens];
}

// Destrutor
Armazem::~Armazem() {
    // Libera a memória do array de Pilhas
    delete[] secoes;
}

// Método de inicialização
void Armazem::inicializar(int id, int numTotalArmazens) {
    this->id = id;
    this->numTotalArmazens = numTotalArmazens;
    if (this->secoes != nullptr) {
        delete[] secoes; 
    }
    this->secoes = new Pilha[numTotalArmazens];
}

// Retorna uma referência para a Pilha correta
Pilha& Armazem::getSecao(int idArmazemDestino) {
    // O array secoes tem uma pilha para cada possível destino
    // A pilha na posição 'idArmazemDestino' guarda os pacotes que vão para lá
    return secoes[idArmazemDestino];
}