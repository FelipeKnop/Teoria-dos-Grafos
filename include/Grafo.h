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
        void informaGrauNo(int idNo);
        //d
        void verificaRegularidade(int k);
        //e
        void informaOrdem();
        //f
        void informaTrivial();
        //g
        void informaNulo();
        //j
        bool verificarMultigrafo();
        //n
        int calculaGrau();

        //q
        void apresentaSequenciaGraus();
        void ordenaSequencia(int* sequencia, int n);

        //Auxiliares
        void removerTodasAdj(int id);
        void imprimeNos();
        void informaGrau();
        No* getNo(int id);
        int getOrdem();

    private:
        bool direcionado;
        No* noRaiz;
        No* ultimo;
        //descritores
        int ordem;
};

#endif // GRAFO_H
