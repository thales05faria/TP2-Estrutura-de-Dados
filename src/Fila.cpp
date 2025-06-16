#include "Fila.hpp"
#include <iostream>

Fila::Fila(){

    tamanho = 0;
    first = nullptr;
    last = nullptr;
}

Fila::~Fila(){
    Limpa();
}

int* Fila::GetFirst(){
    if (first == nullptr) return nullptr;
    return &(first->item);
}

int Fila::GetTamanho() const{
    return tamanho;
}

void Fila::Enfileirar(int item){
    CelulaFila *nova = new CelulaFila();
    nova->item = item;
    nova->next = nullptr;

    if(first == nullptr){
        first = nova;
    } else {
        last->next = nova;
    }

    last = nova;
    tamanho++;
}

void Fila::Desenfileirar(){

    if(first==nullptr) return;
    CelulaFila *antigoFirst = first;
    first = first->next;
    delete antigoFirst;
    tamanho--;

    if (first == nullptr){
        last = nullptr;
    }
}

void Fila::Limpa(){
    while(tamanho != 0) Desenfileirar();
}