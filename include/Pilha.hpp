#ifndef PILHA_HPP
#define PILHA_HPP
#include "Pacote.hpp"

class Pilha{

    private: 

        struct CelulaPilha{
            Pacote* item; //Armazena um pacote
            CelulaPilha *next;
        };

        CelulaPilha *topo;
        int tamanho;

    public:

        Pilha();
        ~Pilha();

        void Empilha(Pacote* item);
        void Desempilha();
        Pacote* getTopo() const;
        int getTamanho() const;
        void Limpa();

};

#endif 