#include <iostream>
#include <fstream>
#include <string>

// Seus includes de TADs
#include "Armazem.hpp"
#include "MinHeap.hpp"
#include "Pacote.hpp"
#include "RotaBFS.hpp"
#include "Evento.hpp" // Incluído para usar a classe Evento

int main(int argc, char* argv[]) {

    // --- Verificação do Arquivo de Entrada ---
    if (argc != 2) {
        std::cerr << "Erro: Uso incorreto." << std::endl;
        std::cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>" << std::endl;
        return 1;
    }
    std::ifstream arquivo_entrada(argv[1]);
    if (!arquivo_entrada.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo " << argv[1] << std::endl;
        return 1;
    }

    // --- Leitura dos Parâmetros da Simulação ---
    int capacidadeTransporte, latenciaTransporte, intervaloTransportes, custoRemocao;
    arquivo_entrada >> capacidadeTransporte;
    arquivo_entrada >> latenciaTransporte;
    arquivo_entrada >> intervaloTransportes;
    arquivo_entrada >> custoRemocao;

    // --- Leitura da Topologia do Grafo ---
    int numArmazens;
    arquivo_entrada >> numArmazens;
    int** grafo = new int*[numArmazens];
    for (int i = 0; i < numArmazens; ++i) {
        grafo[i] = new int[numArmazens];
        for (int j = 0; j < numArmazens; ++j) {
            arquivo_entrada >> grafo[i][j];
        }
    }

    // --- Inicialização dos Componentes Principais ---
    MinHeap escalonador(1000); // Capacidade para 1000 eventos pendentes
    
    Armazem* armazens = new Armazem[numArmazens];
    for(int i = 0; i < numArmazens; ++i) {
        armazens[i].inicializar(i, numArmazens);
    }

    // --- Leitura dos Pacotes e Agendamento Inicial ---
    int numPacotes;
    arquivo_entrada >> numPacotes;
    Pacote** todosOsPacotes = new Pacote*[numPacotes]; // Array para guardar os ponteiros

    for (int i = 0; i < numPacotes; ++i) {
        //Setar TempoChegada = tempo do primeiro transporte
        int tempoPostagem, id, origem, destino;
        std::string pac, org, dst; 
        arquivo_entrada >> tempoPostagem >> pac >> id >> org >> origem >> dst >> destino;
        
        todosOsPacotes[i] = new Pacote(id, origem, destino, tempoPostagem);
        
        ListaEncadeada rota = calculaRota(grafo, numArmazens, origem, destino);
        todosOsPacotes[i]->setRota(rota);

        Evento eventoChegada(tempoPostagem, todosOsPacotes[i], origem);
        escalonador.insere(eventoChegada);
    }

    // --- Agendamento dos Primeiros Eventos de Transporte ---
    for (int i = 0; i < numArmazens; ++i) {
        for (int j = i; j < numArmazens; ++j) {
            if (grafo[i][j] == 1) {
                Evento eventoTransporte(intervaloTransportes, i, j);
                escalonador.insere(eventoTransporte);
                Evento eventoTransporteVolta(intervaloTransportes, j, i);
                escalonador.insere(eventoTransporteVolta);
            }
        }
    }
    
    // ==========================================================
    // LOOP DE SIMULAÇÃO PRINCIPAL
    // ==========================================================
    int tempoSimulacao = 0;

    while (!escalonador.Vazio()) {
        Evento eventoAtual = escalonador.remove();

        std::cout << "[DEBUG] Processando evento -> Tipo: " << eventoAtual.tipo << ", Tempo: " << eventoAtual.tempo << std::endl;

        tempoSimulacao = eventoAtual.tempo;

        if (eventoAtual.tipo == CHEGADA_PACOTE) {
            Pacote* pacote = eventoAtual.pacote; // 'pacote' agora é um ponteiro
            int armazemChegada = eventoAtual.armazemOrigem;

            if (armazemChegada == pacote->getDestino()) {
                pacote->setEstado(ENTREGUE, tempoSimulacao);
                std::cout << tempoSimulacao << " pacote " << pacote->getID() << " entregue em " << armazemChegada << std::endl;
            } else {
                pacote->setLocalizacao(armazemChegada);
                pacote->setEstado(ARMAZENADO, tempoSimulacao);
                
                int* proximoDestinoPtr = pacote->getProximoArmazem();
                if (proximoDestinoPtr != nullptr) {
                    int proximoDestino = *proximoDestinoPtr;
                    armazens[armazemChegada].getSecao(proximoDestino).Empilha(pacote);
                    pacote->deslocamentoRota();
                    std::cout << tempoSimulacao << " pacote " << pacote->getID() << " armazenado em " << armazemChegada << " na secao " << proximoDestino << std::endl;
                }
            }
        } else if (eventoAtual.tipo == TRANSPORTE_PACOTE) {
            int origem = eventoAtual.armazemOrigem;
            int destino = eventoAtual.armazemDestino;

            Pilha& secao = armazens[origem].getSecao(destino);

            for (int i = 0; i < capacidadeTransporte; ++i) {
                if (secao.getTamanho() == 0) break;

                Pacote* pacoteParaTransporte = secao.getTopo();
                secao.Desempilha();

                pacoteParaTransporte->setEstado(REMOVIDO_PARA_TRANSPORTE, tempoSimulacao);
                int tempoChegada = tempoSimulacao + latenciaTransporte;
                
                Evento proximoEvento(tempoChegada, pacoteParaTransporte, destino);
                escalonador.insere(proximoEvento);

                std::cout << tempoSimulacao << " pacote " << pacoteParaTransporte->getID() << " em transito de " << origem << " para " << destino << std::endl;
            }
            
            int proximoTransporteTempo = tempoSimulacao + intervaloTransportes;
            Evento proximoTransporte(proximoTransporteTempo, origem, destino);
            escalonador.insere(proximoTransporte);
        }
    }
    
    // --- Limpeza Final da Memória Alocada ---
    delete[] armazens;
    for (int i = 0; i < numArmazens; ++i) { delete[] grafo[i]; }
    delete[] grafo;
    for (int i = 0; i < numPacotes; ++i) { delete todosOsPacotes[i]; }
    delete[] todosOsPacotes;

    // std::cout << "Simulacao finalizada." << std::endl;
    return 0;
}