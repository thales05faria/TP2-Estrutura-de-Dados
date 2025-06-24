#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "Armazem.hpp"
#include "MinHeap.hpp"
#include "Pacote.hpp"
#include "RotaBFS.hpp"
#include "Evento.hpp" 

int main(int argc, char* argv[]) {

    //Verificação do Arquivo de Entrada
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

    // Leitura dos parâmetros 
    int capacidadeTransporte, latenciaTransporte, intervaloTransportes, custoRemocao;
    arquivo_entrada >> capacidadeTransporte;
    arquivo_entrada >> latenciaTransporte;
    arquivo_entrada >> intervaloTransportes;
    arquivo_entrada >> custoRemocao;

    //Leitura do grafo 
    int numArmazens;
    arquivo_entrada >> numArmazens;
    int** grafo = new int*[numArmazens];
    for (int i = 0; i < numArmazens; ++i) {
        grafo[i] = new int[numArmazens];
        for (int j = 0; j < numArmazens; ++j) {
            arquivo_entrada >> grafo[i][j];
        }
    }

    //Inicialização dos componentes principais ---
    MinHeap escalonador(1000); //Capacidade para 1000 eventos 
    
    Armazem* armazens = new Armazem[numArmazens];
    for(int i = 0; i < numArmazens; ++i) {
        armazens[i].inicializar(i, numArmazens);
    }

    //Leitura dos pacotes
    int numPacotes;
    arquivo_entrada >> numPacotes;
    Pacote** todosOsPacotes = new Pacote*[numPacotes]; //Array para guardar os ponteiros

    //Loop para criar os pacotes, calcular a melhor rota e agendar os eventos
    for (int i = 0; i < numPacotes; ++i) {
        int tempoPostagem, id, origem, destino;
        std::string pac, org, dst; 
        arquivo_entrada >> tempoPostagem >> pac >> id >> org >> origem >> dst >> destino;
        
        todosOsPacotes[i] = new Pacote(i, origem, destino, tempoPostagem);
        
        // Calcula o menor caminho usando busca em largura
        ListaEncadeada rota = calculaRota(grafo, numArmazens, origem, destino);
        todosOsPacotes[i]->setRota(rota);

        //Insere o evento de chegada do pacote ao armazém de origem
        Evento eventoChegada(tempoPostagem, todosOsPacotes[i], origem);
        escalonador.insere(eventoChegada);
    }

    int primeiroTempoPostagem = -1;

    //Define o primeiro tempo de postagem
    if (numPacotes > 0) {
        primeiroTempoPostagem = todosOsPacotes[0]->getTempoPostagem();
        for (int i = 1; i < numPacotes; ++i) {
            if (todosOsPacotes[i]->getTempoPostagem() < primeiroTempoPostagem) {
                primeiroTempoPostagem = todosOsPacotes[i]->getTempoPostagem();
            }
        }
    } else {
        primeiroTempoPostagem = 0; 
    }
    
    // Calcula o tempo do primeiro transporte com base na primeira postagem
    int tempoPrimeiroTransporte = primeiroTempoPostagem + intervaloTransportes;


    //Agendamento dos primeiros eventos de transporte 
    for (int i = 0; i < numArmazens; ++i) {
        for (int j = i; j < numArmazens; ++j) {
            if (grafo[i][j] == 1) {
                Evento eventoTransporte(tempoPrimeiroTransporte, i, j);
                escalonador.insere(eventoTransporte);
                Evento eventoTransporteVolta(tempoPrimeiroTransporte, j, i);
                escalonador.insere(eventoTransporteVolta);
            }
        }
    }
    
    
    // Loop de Simulação principal
    int tempoSimulacao = 0;
    int pacotesEntregues = 0;

    //Para após entregar todos os pacotes
    while (!escalonador.Vazio() && pacotesEntregues < numPacotes) {

        //Retira o primeiro evento da fila e soma o tempo ao relógio
        Evento eventoAtual = escalonador.remove();
        tempoSimulacao = eventoAtual.tempo;

        //Se for a chegada de um pacote
        if (eventoAtual.tipo == CHEGADA_PACOTE) {
            Pacote* pacote = eventoAtual.pacote;
            int armazemChegada = eventoAtual.armazemOrigem;

            //Se chegou ao destino final, registra a entrega
            if (armazemChegada == pacote->getDestino()) {
                pacote->setEstado(ENTREGUE, tempoSimulacao);
                pacotesEntregues++;

                std::cout << std::setw(7) << std::setfill('0') << tempoSimulacao << " pacote " 
                        << std::setw(3) << std::setfill('0') << pacote->getID() 
                        << " entregue em " << std::setw(3) << std::setfill('0') << armazemChegada << std::endl;

            //Se ainda não chegou, armazena na seção correta
            } else {
                pacote->setLocalizacao(armazemChegada);
                pacote->setEstado(ARMAZENADO, tempoSimulacao);
                
                int* proximoDestinoPtr = pacote->getProximoArmazem();
                if (proximoDestinoPtr != nullptr) {
                    int proximoDestino = *proximoDestinoPtr;
                    armazens[armazemChegada].getSecao(proximoDestino).Empilha(pacote);
                    pacote->deslocamentoRota();

                    // Saída formatada
                    std::cout << std::setw(7) << std::setfill('0') << tempoSimulacao << " pacote " 
                            << std::setw(3) << std::setfill('0') << pacote->getID() 
                            << " armazenado em " << std::setw(3) << std::setfill('0') << armazemChegada 
                            << " na secao " << std::setw(3) << std::setfill('0') << proximoDestino << std::endl;
                }
            }
        // Se o evento for do tipo transporte
        } else if (eventoAtual.tipo == TRANSPORTE_PACOTE) {
            int origem = eventoAtual.armazemOrigem;
            int destino = eventoAtual.armazemDestino;
            Pilha& secao = armazens[origem].getSecao(destino);

            int tempoOperacao = tempoSimulacao;
            Pilha pilhaAuxiliar;

            //Esvazia a seção, registrando o tempo de cada remoção.
            while (secao.getTamanho() > 0) {
                Pacote* pacoteRemovido = secao.getTopo();
                secao.Desempilha();
                
                tempoOperacao += custoRemocao;
                std::cout << std::setw(7) << std::setfill('0') << tempoOperacao << " pacote " 
                        << std::setw(3) << std::setfill('0') << pacoteRemovido->getID() 
                        << " removido de " << std::setw(3) << std::setfill('0') << origem 
                        << " na secao " << std::setw(3) << std::setfill('0') << destino << std::endl;
                
                pilhaAuxiliar.Empilha(pacoteRemovido);
            }

            //Decide quem transportar e quem rearmazenar
            int transportados = 0;
            while (pilhaAuxiliar.getTamanho() > 0) {
                Pacote* pacoteAtual = pilhaAuxiliar.getTopo();
                pilhaAuxiliar.Desempilha();

                if (transportados < capacidadeTransporte) {
                    // TRANSPORTAR
                    pacoteAtual->setEstado(REMOVIDO_PARA_TRANSPORTE, tempoOperacao);
                    int tempoChegada = tempoOperacao + latenciaTransporte;
                    Evento proximoEvento(tempoChegada, pacoteAtual, destino);
                    escalonador.insere(proximoEvento);

                    std::cout << std::setw(7) << std::setfill('0') << tempoOperacao << " pacote " 
                            << std::setw(3) << std::setfill('0') << pacoteAtual->getID() 
                            << " em transito de " << std::setw(3) << std::setfill('0') << origem 
                            << " para " << std::setw(3) << std::setfill('0') << destino << std::endl;
                    transportados++;
                } else {
                    // Rearmazenamento
                    secao.Empilha(pacoteAtual); //Empilha de volta na seção original
                    pacoteAtual->setEstado(ARMAZENADO, tempoOperacao);

                    std::cout << std::setw(7) << std::setfill('0') << tempoOperacao << " pacote " 
                            << std::setw(3) << std::setfill('0') << pacoteAtual->getID() 
                            << " rearmazenado em " << std::setw(3) << std::setfill('0') << origem 
                            << " na secao " << std::setw(3) << std::setfill('0') << destino << std::endl;
                }
            }
            
            //Reagenda o próximo transporte.
            int proximoTransporteTempo = tempoSimulacao + intervaloTransportes;
            Evento proximoTransporte(proximoTransporteTempo, origem, destino);
            escalonador.insere(proximoTransporte);
        }
    }
   //Limpeza da memória alocada
    delete[] armazens;
    for (int i = 0; i < numArmazens; ++i) { delete[] grafo[i]; }
    delete[] grafo;
    for (int i = 0; i < numPacotes; ++i) { delete todosOsPacotes[i]; }
    delete[] todosOsPacotes;

    return 0;
}