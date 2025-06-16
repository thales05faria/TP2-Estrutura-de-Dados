#include "RotaBFS.hpp"
#include "Fila.hpp"

ListaEncadeada calculaRota(int** grafo, int numArmazens, int origem, int destino){

    int* distancia = new int[numArmazens]; //Vetor para guardar a distancia de cada armazém até a origem
    int* antecessor = new int[numArmazens]; //Vetor que guarda, para cada armazém visitado, o armazém visitado anteriormente 

    //Incializa todos os elementos do vetor com -1 (não há informações sobre o armazém)
    for (int i = 0; i < numArmazens; i++){
        distancia[i] = -1;
        antecessor[i] = -1;
    }

    Fila caminhoVisitas; //Fila de armazéns a serem visitados em ordem
    distancia[origem] = 0; //Distancia da origem até a origem é 0
    caminhoVisitas.Enfileirar(origem); //Primeiro armazém a ser visitado é a origem

    //Enquanto a fila não estiver vazia
    while(caminhoVisitas.GetTamanho() > 0){
        int atual = *caminhoVisitas.GetFirst(); //Seleciona o armazém para testar 
        caminhoVisitas.Desenfileirar(); //Remove da fila

        //Se o armazém for o destino, encerra busca.
        if(atual == destino){
            break;
        }

        //Olha na matriz todos os vizinhos desse armazém
        for (int vizinho = 0; vizinho < numArmazens; vizinho++){
            //Verifica se o vizinho ainda não foi visitado
            if (grafo[atual][vizinho] == 1 && distancia[vizinho] == -1){

                distancia[vizinho] = distancia[atual] + 1; //Anota a distância do vizinho até a origem
                antecessor[vizinho] = atual; //Anota o armazém antecessor desse vizinho

                caminhoVisitas.Enfileirar(vizinho); //Entra na fila para ser testado
            }
        }
    }

    ListaEncadeada rota; //Cria uma lista para armazenar o menor caminho

    //Testa se o caminho chegou ao destino
    if(distancia[destino] != -1){
        int armazemRota = destino;

        //Enquanto não chegamos ao início do caminho (antecessor[origem] == -1)
        while(armazemRota != -1){
            rota.InsereInicio(armazemRota); //Adiciona o armazém a rota
            armazemRota = antecessor[armazemRota]; //Passa para o armazém antecessor
        }
        
        rota.RemoveInicio(); //Remove a origem
    }

    //Libera a memória alocada para os vetores
    delete[] distancia;
    delete[] antecessor;

    return rota;
}