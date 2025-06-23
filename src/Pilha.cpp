#include "Pilha.hpp"
#include <iostream>

Pilha::Pilha(){
    topo = nullptr;
    tamanho = 0;
}

Pilha::~Pilha(){
    Limpa();
}

int Pilha::getTamanho() const{
    return tamanho;
}

Pacote* Pilha::getTopo() const{
    if (topo == nullptr) return nullptr;
    return topo->item;
}

void Pilha::Limpa(){
    while(topo != nullptr) Desempilha();
}

void Pilha::Empilha(Pacote* item){

    CelulaPilha *nova = new CelulaPilha();
    nova->item = item;
    nova->next = topo;
    topo = nova;
    tamanho++;

}

void Pilha::Desempilha(){
    if (topo == nullptr) return;

    CelulaPilha *antigoTopo = topo;
    topo = topo->next;
    delete antigoTopo;
    tamanho--;

}