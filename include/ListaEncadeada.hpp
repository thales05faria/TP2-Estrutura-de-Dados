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
        int* GetFirst();
        int GetTamanho() const;
        void InsereFinal(int item);
        void InsereInicio(int item);
        void RemoveInicio();
        void Limpa();

};


#endif LISTAENCADEADA_HPP