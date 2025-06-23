#include "Pacote.hpp"
        
Pacote::Pacote(){
    this->id = -1;
    this->origem = -1;
    this->destino = -1;
    this->tempoPostagem = -1;
    this->estadoPacote = NAO_POSTADO;
    this->localizacao = -1;
    this->tempoArmazenado = 0;
    this->tempoEmTransporte = 0;
    this->ultimoTempo = 0;
}

Pacote::Pacote(int id, int origem, int destino, int tempoPostagem){
    this->id = id;
    this->origem = origem;
    this->destino = destino;
    this->tempoPostagem = tempoPostagem;

    this->estadoPacote = NAO_POSTADO;
    this->localizacao = origem;
    this->tempoArmazenado = 0;
    this->tempoEmTransporte = 0;
    this->ultimoTempo = tempoPostagem;
}

int Pacote::getID() const{
    return id;
}

int Pacote::getOrigem() const{
    return origem;
}
int Pacote::getDestino() const{
    return destino;
}
EstadoPacote Pacote::getEstado() const{
    return estadoPacote;
}

void Pacote::setRota(const ListaEncadeada& novaRota){
    rota = novaRota;
}

void Pacote::setEstado(EstadoPacote novoEstado, int tempoAtual){
    int duracaoEstado = tempoAtual - ultimoTempo;

    if(estadoPacote == ARMAZENADO){
        tempoArmazenado += duracaoEstado;
    }

    if(estadoPacote == REMOVIDO_PARA_TRANSPORTE){
        tempoEmTransporte += duracaoEstado;
    }

    estadoPacote = novoEstado;
    ultimoTempo = tempoAtual;
}

void Pacote::setLocalizacao(int novaLocalizacao){
    localizacao = novaLocalizacao;
}

int* Pacote::getProximoArmazem(){
    return rota.GetFirst();
}

void Pacote::deslocamentoRota(){
    rota.RemoveInicio();
}

int Pacote::getTempoArmazenado() const{
    return tempoArmazenado;
}
int Pacote::getTempoEmTransporte() const{
    return tempoEmTransporte;
}