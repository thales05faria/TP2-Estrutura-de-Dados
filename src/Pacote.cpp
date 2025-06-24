#include "Pacote.hpp"

//Construtor padrão
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

//Construtor
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

//Retorna id do pacote
int Pacote::getID() const{
    return id;
}

//Retorna origem do pacote
int Pacote::getOrigem() const{
    return origem;
}

//Retorna destino do pacote
int Pacote::getDestino() const{
    return destino;
}

//Retorna estado do pacote
EstadoPacote Pacote::getEstado() const{
    return estadoPacote;
}


//Guarda a rota do pacote
void Pacote::setRota(const ListaEncadeada& novaRota){
    rota = novaRota;
}

//Muda o estado do pacote e atualiza os atributos de tempo
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

//Atualiza a localização do pacote
void Pacote::setLocalizacao(int novaLocalizacao){
    localizacao = novaLocalizacao;
}

//Retorna o próximo armazém da rota
int* Pacote::getProximoArmazem(){
    return rota.GetFirst();
}

//Remove o armazém que o pacote já alcançou na rota
void Pacote::deslocamentoRota(){
    rota.RemoveInicio();
}

//Retorna há quanto tempo o pacote está armazenado
int Pacote::getTempoArmazenado() const{
    return tempoArmazenado;
}

//Retorna há quanto tempo o pacote está em transporte
int Pacote::getTempoEmTransporte() const{
    return tempoEmTransporte;
}

//Retorna o tempo de postagem do pacote
int Pacote::getTempoPostagem() const{
    return tempoPostagem;
}
