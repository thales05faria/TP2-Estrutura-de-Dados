#include "ListaEncadeada.hpp"
#include <iostream>

ListaEncadeada::ListaEncadeada(){

    tamanho = 0;
    first = nullptr;
    last = nullptr;
}

ListaEncadeada::~ListaEncadeada(){
    Limpa();
}

int* ListaEncadeada::GetFirst(){
    if (first == nullptr) return nullptr;
    return &(first->item);
}

int ListaEncadeada::GetTamanho() const{
    return tamanho;
}

void ListaEncadeada::InsereFinal(int item){
    CelulaLista *nova = new CelulaLista();
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

void ListaEncadeada::RemoveInicio(){

    if(first==nullptr) return;
    CelulaLista *antigoFirst = first;
    first = first->next;
    delete antigoFirst;
    tamanho--;

    if (first == nullptr){
        last = nullptr;
    }
}

void ListaEncadeada::Limpa(){
    while(tamanho != 0) RemoveInicio();
}