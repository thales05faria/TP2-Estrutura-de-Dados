#include "MinHeap.hpp"
#include <stdexcept> // Para std::out_of_range e std::overflow_error

// Construtor
MinHeap::MinHeap(int capacidade) {
    this->capacidade = capacidade;
    this->tamanho = 0;
    this->heap = new Evento[capacidade];
}

// Destrutor
MinHeap::~MinHeap() {
    delete[] heap;
}

// --- Métodos Auxiliares Privados ---

void MinHeap::troca(Evento* a, Evento* b) {
    Evento temp = *a;
    *a = *b;
    *b = temp;
}

int MinHeap::pai(int i) { return (i - 1) / 2; }
int MinHeap::filhoEsquerdo(int i) { return (2 * i) + 1; }
int MinHeap::filhoDireito(int i) { return (2 * i) + 2; }

void MinHeap::sobe(int i) {
    while (i != 0 && heap[pai(i)] > heap[i]) {
        troca(&heap[i], &heap[pai(i)]);
        i = pai(i);
    }
}

// Implementação ITERATIVA e robusta do 'desce'
void MinHeap::desce(int i) {
    int indiceDoMenor;
    while (true) {
        int esq = filhoEsquerdo(i);
        int dir = filhoDireito(i);
        indiceDoMenor = i;

        // Acha o menor entre o nó atual (i) e seu filho esquerdo
        if (esq < tamanho && (heap[indiceDoMenor] > heap[esq])) {
            indiceDoMenor = esq;
        }

        // Compara o menor encontrado até agora com o filho direito
        if (dir < tamanho && (heap[indiceDoMenor] > heap[dir])) {
            indiceDoMenor = dir;
        }

        // Se o nó 'i' já é o menor, a propriedade do heap está satisfeita.
        if (indiceDoMenor == i) {
            break;
        }

        // Caso contrário, troca com o menor filho e continua o processo
        troca(&heap[i], &heap[indiceDoMenor]);
        i = indiceDoMenor;
    }
}


// --- Métodos Públicos ---

void MinHeap::insere(const Evento& evento) {
    if (tamanho == capacidade) {
        throw std::overflow_error("Erro: Heap cheio!");
    }
    tamanho++;
    heap[tamanho - 1] = evento;
    sobe(tamanho - 1);
}

Evento MinHeap::remove() {
    if (tamanho <= 0) {
        throw std::out_of_range("Erro: Heap vazio.");
    }
    if (tamanho == 1) {
        tamanho--;
        return heap[0];
    }
    Evento raiz = heap[0];
    heap[0] = heap[tamanho - 1];
    tamanho--;
    desce(0);
    return raiz;
}

bool MinHeap::Vazio() const {
    return tamanho == 0;
}

int MinHeap::getTamanho() const {
    return tamanho;
}