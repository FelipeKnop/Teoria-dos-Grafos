#ifndef NO_H
#define NO_H
#include "Adjacencia.h"

class No
{
    public:
        No(int id,int  dado);
        ~No();

        void adicionarAdj(No* destino, int peso);
        void removerAdj(No* destino, int peso);

        int getId();
        int getDado();
        No* getProx();
        void setProx(No* no);
        int getGrau();
        int getGrauEntrada();
        void addGrauEntrada(int i);


    protected:

    private:
        Adjacencia* adjRaiz;
        Adjacencia* ultimaAdj;
        int id;
        int dado;
        No* prox;

        //descritores:
        int grau; //Será considerado como grau de saída em grafos direcionados
        int grauEntrada; //para grafos direcionados
};

#endif // NO_H
