#ifndef LISTAENCADEADA_HPP
#define LISTAENCADEADA_HPP

class ListaEncadeada {

    private:

        struct CelulaLista{
            int item; //Armazena o ID do armazém
            CelulaLista *next;
        };

        CelulaLista *first;
        CelulaLista *last;
        int tamanho;

    public:


        ListaEncadeada();
        ~ListaEncadeada();
        ListaEncadeada(const ListaEncadeada& outra); // Construtor de Cópia
        ListaEncadeada& operator=(const ListaEncadeada& outra); // Operador de Atribuição
        int* GetFirst();
        int GetTamanho() const;
        void InsereFinal(int item);
        void InsereInicio(int item);
        void RemoveInicio();
        void Limpa();

};


#endif