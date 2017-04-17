#ifndef GRAFO_H
#define GRAFO_H
#include "No.h"
#include<stdlib.h>
#include<iostream>

class Grafo
{
    public:
        Grafo();
        ~Grafo();
        void criarNo(int id, int dado);
        void criarAdj(int idNo1, int idNo2);
        bool buscaProfundidade(int dado);
        void imprimeNos();

    private:
        No* noRaiz;
        No* ultimo;
};

#endif // GRAFO_H
