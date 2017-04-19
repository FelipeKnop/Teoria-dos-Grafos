#ifndef NO_H
#define NO_H
#include "Adjacencia.h"

class No
{
    public:
        No(int id,int  dado);
        ~No();

        void adicionarAdj(No* destino, int peso);

        int getId();
        int getDado();
        No* getProx();
        void setProx(No* no);
        int getGrau();


    protected:

    private:
        Adjacencia* adjRaiz;
        Adjacencia* ultimaAdj;
        int id;
        int dado;
        No* prox;

        //descritores:
        int grau;
};

#endif // NO_H
