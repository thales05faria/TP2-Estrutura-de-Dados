#ifndef FILA_HPP
#define FILA_HPP

class Fila {

    private:

        struct CelulaFila{
            int item;
            CelulaFila *next;
        };

        CelulaFila *first;
        CelulaFila *last;
        int tamanho;

    public:


        Fila();
        ~Fila();
        int* GetFirst();
        int GetTamanho() const;
        void Enfileirar(int item);
        void Desenfileirar();
        void Limpa();

};


#endif 