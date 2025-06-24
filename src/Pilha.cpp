#include "Pilha.hpp"
#include <iostream>

//Construtor
Pilha::Pilha(){
    topo = nullptr;
    tamanho = 0;
}


//Destrutor
Pilha::~Pilha(){
    Limpa();
}

//Retorna o tamanho
int Pilha::getTamanho() const{
    return tamanho;
}

//Retorna o item do topo a pilha
Pacote* Pilha::getTopo() const{
    if (topo == nullptr) return nullptr;
    return topo->item;
}

//Remove todos os itens da pilha
void Pilha::Limpa(){
    while(topo != nullptr) Desempilha();
}

//Adiciona um item ao topo da pilha
void Pilha::Empilha(Pacote* item){

    CelulaPilha *nova = new CelulaPilha();
    nova->item = item;
    nova->next = topo;
    topo = nova;
    tamanho++;

}

//Remove um item do topo da pilha
void Pilha::Desempilha(){
    if (topo == nullptr) return;

    CelulaPilha *antigoTopo = topo;
    topo = topo->next;
    delete antigoTopo;
    tamanho--;

}