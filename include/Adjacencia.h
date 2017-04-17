#ifndef ADJACENCIA_H
#define ADJACENCIA_H

#include<stdlib.h>
#include<iostream>

class No;

class Adjacencia
{
    public:
        Adjacencia();
        ~Adjacencia();

    protected:

    private:
        No* noInicio;
        No* noFim;
        int peso;
        Adjacencia* prox;
};

#endif // ADJACENCIA_H
