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

// Construtor de Cópia: cria uma lista nova a partir de outra
ListaEncadeada::ListaEncadeada(const ListaEncadeada& outra) {
    // Inicializa a nova lista como vazia
    this->first = nullptr;
    this->last = nullptr;
    this->tamanho = 0;

    // Itera pela 'outra' lista e insere cada item na nova lista
    for (CelulaLista* no = outra.first; no != nullptr; no = no->next) {
        this->InsereFinal(no->item);
    }
}

// Operador de Atribuição: para quando fazemos 'listaA = listaB'
ListaEncadeada& ListaEncadeada::operator=(const ListaEncadeada& outra) {
    // 1. Verifica se não estamos atribuindo um objeto a ele mesmo (ex: a = a)
    if (this == &outra) {
        return *this;
    }

    // 2. Limpa a lista atual para não vazar memória
    this->Limpa();

    // 3. Copia os itens da 'outra' lista para a lista atual
    for (CelulaLista* no = outra.first; no != nullptr; no = no->next) {
        this->InsereFinal(no->item);
    }

    // 4. Retorna a lista atual para permitir encadeamento (ex: a = b = c)
    return *this;
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

void ListaEncadeada::InsereInicio(int item){
    CelulaLista *nova = new CelulaLista();
    nova->item = item;
    nova->next = first;
    first = nova;


    if (last == nullptr){
        last = nova;
    }

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