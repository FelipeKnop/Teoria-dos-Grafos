#ifndef GRAFO_H
#define GRAFO_H
#include "No.h"
#include<stdlib.h>
#include<fstream>
#include<iostream>

class Grafo
{
    public:
        Grafo(bool direcionado);
        ~Grafo();
        //a
        void imprimir(char* caminho);
        //b
        void criarNo(int id, int dado);
        void criarAdj(int idNo1, int idNo2, int peso);
        void removerNo(int id);
        void removerAdj(int idNo1,int idNo2,int peso);
        //c

        //d

        //Auxiliares
        void removerTodasAdj(int id);
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
