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
     
        std::string Evento::gerarChavePrioridade() const {
            std::stringstream chave;
            
            // Formata com 0 à esquerda e largura fixa para cada campo
            chave << std::setw(6) << std::setfill('0') << this->tempo;

            if (this->tipo == CHEGADA_PACOTE) {
                // Formato para evento de Pacote, conforme Tabela 1
                chave << std::setw(6) << std::setfill('0') << this->pacote->getID();
                chave << std::setw(1) << std::setfill('0') << this->tipo;
            } else { 
                // Formato para evento de Transporte, conforme Tabela 1
                chave << std::setw(3) << std::setfill('0') << this->armazemOrigem;
                chave << std::setw(3) << std::setfill('0') << this->armazemDestino;
                chave << std::setw(1) << std::setfill('0') << this->tipo;
            }
            
            return chave.str();
        }

        bool Evento::operator>(const Evento& outro) const {
            // Gera as chaves para ambos os eventos
            std::string chaveThis = this->gerarChavePrioridade();
            std::string chaveOutro = outro.gerarChavePrioridade();

            // Compara as strings
            return chaveThis > chaveOutro;
        }