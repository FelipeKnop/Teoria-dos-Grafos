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
        void criarAdj(int idNo1, int idNo2, int peso);
        bool buscaProfundidade(int dado);
        void imprimeNos();

        No* getNo(int id);
        int getOrdem();

    private:
        No* noRaiz;
        No* ultimo;
        //descritores
        int grau;
        int ordem;
};

#endif // GRAFO_H
