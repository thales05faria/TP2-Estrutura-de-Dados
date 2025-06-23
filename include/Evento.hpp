#ifndef EVENTO_HPP
#define EVENTO_HPP
#include "Pacote.hpp"

enum TipoEvento{
    CHEGADA_PACOTE,
    TRANSPORTE_PACOTE
};

class Evento{

    public:

        Evento();
        Evento(int tempo, Pacote* pacote, int armazemChegada); //Construtor tipo CHEGADA_PACOTE
        Evento(int tempo, int origem, int destino); //Construtor tipo TRANSPORTE_PACOTE

        int tempo;
        TipoEvento tipo;

        Pacote *pacote; //para CHEGADA
        int armazemOrigem; 
        int armazemDestino; 

        bool operator>(const Evento& outro) const;
};


#endif 