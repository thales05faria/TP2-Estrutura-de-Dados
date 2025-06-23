#include "Evento.hpp"

        Evento::Evento(){
            this->tempo = -1;
        }

        //Construtor tipo CHEGADA_PACOTE
        Evento::Evento(int tempo, Pacote* pacote, int armazemChegada){
            this->tempo = tempo;
            this->tipo = CHEGADA_PACOTE;
            this->pacote  = pacote;
            this->armazemOrigem = armazemChegada;
            this->armazemDestino = -1;
        }

        //Construtor tipo TRANSPORTE_PACOTE
        Evento::Evento(int tempo, int origem, int destino){
            this->tempo = tempo;
            this->tipo = TRANSPORTE_PACOTE;
            this->armazemOrigem = origem;
            this->armazemDestino = destino;
            this->pacote = nullptr;
        } 

        bool Evento::operator>(const Evento& outro) const{

            //PRIORIDADE 1: TEMPO
            if(this->tempo > outro.tempo) {
                return true;
            }

            if(this->tempo < outro.tempo){
                return false;
            }

            //PRIORIDADE 2: ID do Pacote ou Origem-Destino do Transporte
            if (this->tipo == CHEGADA_PACOTE && outro.tipo == CHEGADA_PACOTE) {

                if (this->pacote->getID() > outro.pacote->getID()) return true;
                if (this->pacote->getID() < outro.pacote->getID()) return false;

            } else if (this->tipo == TRANSPORTE_PACOTE && outro.tipo == TRANSPORTE_PACOTE) {

                if (this->armazemOrigem > outro.armazemOrigem) return true;
                if (this->armazemOrigem < outro.armazemOrigem) return false;
                
                if (this->armazemDestino > outro.armazemDestino) return true;
                if (this->armazemDestino < outro.armazemDestino) return false;

            }

            //PRIORIDADE 3: TIPO DO EVENTO
            if (this->tipo > outro.tipo) {
                return true;
            }

            if (this->tipo < outro.tipo) {
                return false;
            }

            return false;

        }