#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include "Evento.hpp" // O Heap precisa saber o que é um Evento para poder armazená-lo.
#include <iostream>  // Para mensagens de erro

class MinHeap{
    
private:
    Evento* heap;     // Ponteiro para o array que armazenará os eventos.
    int capacidade;   // A capacidade máxima do heap.
    int tamanho;      // O número atual de eventos no heap.


    // Retorna o índice do pai de um nó.
    int pai(int i);
    // Retorna o índice do filho esquerdo.
    int filhoEsquerdo(int i);
    // Retorna o índice do filho direito.
    int filhoDireito(int i);

    // Sobe um elemento no heap
    // Usado após a inserção.
    void sobe(int i);

    // Desce um elemento no heap
    void desce(int i);

    //Troca dois eventos de lugar no array
    void troca(Evento* a, Evento* b);

public:

    // Construtor: cria um heap com uma capacidade definida
    MinHeap(int capacidade);

    // Destrutor: libera a memória alocada para o array do heap
    ~MinHeap();

    // Insere um novo evento
    void insere(const Evento& evento);

    // Remove e retorna o evento de maior prioridade (o menor evento)
    Evento remove();

    // Retorna true se o heap estiver vazio
    bool Vazio() const;

    // Retorna o número de eventos atualmente no heap
    int getTamanho() const;
};

#endif