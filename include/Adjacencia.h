#ifndef ADJACENCIA_H
#define ADJACENCIA_H

#include<stdlib.h>
#include<iostream>

class No;

class Adjacencia
{
    public:
        Adjacencia(No* inicio, No* fim, int peso);
        ~Adjacencia();
        void setProx(Adjacencia* adj);
        Adjacencia* getProx();

    protected:

    private:
        No* noInicio;
        No* noFim;
        int peso;
        Adjacencia* prox;
};

#endif // ADJACENCIA_H
