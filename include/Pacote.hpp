#ifndef PACOTE_HPP
#define PACOTE_HPP
#include "ListaEncadeada.hpp"


enum EstadoPacote {
    NAO_POSTADO,
    CHEGADA_ESCALONADA,
    ARMAZENADO,
    REMOVIDO_PARA_TRANSPORTE,
    ENTREGUE
};

class Pacote{

    public: 
        Pacote();
        Pacote(int id, int origem, int destino, int tempoPostagem);

        int getID() const;
        int getOrigem() const;
        int getDestino() const;
        EstadoPacote getEstado() const;

        void setRota(const ListaEncadeada& novaRota);
        void setEstado(EstadoPacote novoEstado, int tempoAtual);
        void setLocalizacao(int novaLocalizacao);

        int* getProximoArmazem();
        void deslocamentoRota();

        int getTempoArmazenado() const;
        int getTempoEmTransporte() const;
        int getTempoPostagem() const;

    private:
        int id;
        int origem;
        int destino;
        int tempoPostagem;

        EstadoPacote estadoPacote;
        ListaEncadeada rota;
        int localizacao;

        int tempoArmazenado;
        int tempoEmTransporte;
        int ultimoTempo;

};

#endif 