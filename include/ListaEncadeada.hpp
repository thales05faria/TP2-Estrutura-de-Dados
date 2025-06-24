#ifndef LISTAENCADEADA_HPP
#define LISTAENCADEADA_HPP

class ListaEncadeada {

    private:

        struct CelulaLista{
            int item; 
            CelulaLista *next;
        };

        CelulaLista *first;
        CelulaLista *last;
        int tamanho;

    public:


        ListaEncadeada();
        ~ListaEncadeada();
        ListaEncadeada(const ListaEncadeada& outra); 
        ListaEncadeada& operator=(const ListaEncadeada& outra);
        int* GetFirst();
        int GetTamanho() const;
        void InsereFinal(int item);
        void InsereInicio(int item);
        void RemoveInicio();
        void Limpa();

};


#endif