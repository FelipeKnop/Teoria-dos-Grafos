#ifndef GRAFO_H
#define GRAFO_H
#include "No.h"
#include<stdlib.h>
#include<iostream>

class Grafo
{
    public:
        Grafo(bool direcionado);
        ~Grafo();
        //b
        void criarNo(int id, int dado);
        void criarAdj(int idNo1, int idNo2, int peso);
        void removerNo(int id);
        void removerAdj(int idNo1,int idNo2,int peso);
        //c

        //d

        //Auxiliares
        void imprimeNos();
        No* getNo(int id);
        int getOrdem();

    private:
        bool direcionado;
        No* noRaiz;
        No* ultimo;
        //descritores
        int grau;
        int ordem;
};

#endif // GRAFO_H
