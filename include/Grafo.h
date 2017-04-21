#ifndef GRAFO_H
#define GRAFO_H
#include "No.h"
#include "Adjacencia.h"
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<vector>
class Grafo
{
    public:
        Grafo(bool direcionado);
        ~Grafo();
        //a
        bool lerArquivo(const char *caminho);
        void salvarArquivo(const char *caminho);
        //b
        void criarNo(int id, int dado);
        void criarAdj(int idNo1, int idNo2, int peso);
        void removerNo(int id);
        void removerAdj(int idNo1,int idNo2,int peso);
        //c
        void informaGrauNo(int idNo);
        //d
        bool verificaRegularidade(int k);
        //e
        void informaOrdem();
        //f
        void informaTrivial();
        //g
        void informaNulo();
        //h
        void vizinhancaAberta(int id);
        //i
        void vizinhancaFechada(int id);
        //j
        bool verificarMultigrafo();
        //k
        bool verificarCompleto();
        //l
        bool verificarBipartido();
        //n
        int calculaGrau();
        //q
        void apresentaSequenciaGraus();
        void ordenaSequencia(int *sequencia, int n);
        //r
        void imprimeSubInduzido(int total, std::vector<int> &n);
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
