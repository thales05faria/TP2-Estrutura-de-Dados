#include "Fila.hpp"
#include <iostream>

// Construtor padrão de Fila
Fila::Fila(){
    tamanho = 0;
    first = nullptr;
    last = nullptr;
}

//Destrutor
Fila::~Fila(){
    Limpa();
}

//Retorna o primeiro elemento da fila
int* Fila::GetFirst(){
    if (first == nullptr) return nullptr;
    return &(first->item);
}

//Retorna o tamanho da fila
int Fila::GetTamanho() const{
    return tamanho;
}

//Adiciona um novo item no final da fila
void Fila::Enfileirar(int item){
    CelulaFila *nova = new CelulaFila();
    nova->item = item;
    nova->next = nullptr;

//Faz as verificações para atualizar os ponteiros corretamente
    if(first == nullptr){
        first = nova;
    } else {
        last->next = nova;
    }

    last = nova;
    tamanho++;
}


//Remove o primeiro item da fila
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

//Remove todos os elementos da fila
void Fila::Limpa(){
    while(tamanho != 0) Desenfileirar();
}