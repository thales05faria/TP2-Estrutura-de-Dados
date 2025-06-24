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

    // Itera pela outra lista e insere cada item na nova lista
    for (CelulaLista* no = outra.first; no != nullptr; no = no->next) {
        this->InsereFinal(no->item);
    }
}

// Operador de Atribuição
ListaEncadeada& ListaEncadeada::operator=(const ListaEncadeada& outra) {
    // Verifica se não estamos atribuindo um objeto a ele mesmo
    if (this == &outra) {
        return *this;
    }

    // Limpa a lista atual
    this->Limpa();

    // Copia os itens da outra lista para a atual
    for (CelulaLista* no = outra.first; no != nullptr; no = no->next) {
        this->InsereFinal(no->item);
    }

    // Retorna a lista atual 
    return *this;
}

//Retorna o primeiro elemento da lista
int* ListaEncadeada::GetFirst(){
    if (first == nullptr) return nullptr;
    return &(first->item);
}

//Retorna o tamanho da lista
int ListaEncadeada::GetTamanho() const{
    return tamanho;
}

//Insere um item no final da lista
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

//Insere um item no inicio da lista
void ListaEncadeada::InsereInicio(int item){
    CelulaLista *nova = new CelulaLista();
    nova->item = item;
    nova->next = first;
    first = nova;

//Faz verificações para atualizar os ponteiros corretamente
    if (last == nullptr){
        last = nova;
    }

    tamanho++;
}

//Remove um item no início da lista
void ListaEncadeada::RemoveInicio(){

    if(first==nullptr) return;
    CelulaLista *antigoFirst = first;
    first = first->next;
    delete antigoFirst;
    tamanho--;

//Faz verificações para atualizar os ponteiros corretamente
    if (first == nullptr){
        last = nullptr;
    }
}

//Limpa todos os elementos da lista
void ListaEncadeada::Limpa(){
    while(tamanho != 0) RemoveInicio();
}