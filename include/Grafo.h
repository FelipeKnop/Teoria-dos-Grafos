#ifndef GRAFO_H
#define GRAFO_H
#include "No.h"
#include "Adjacencia.h"
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<vector>
#include <limits>
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
        void removerNo(int id);
        void criarAdj(int idNo1, int idNo2, int peso);
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
        //m
        void menorCaminhoDijkstra(int idOrigem, int idDestino);
        void menorCaminhoFloyd(int idOrigem, int idDestino);
        //n
        int calculaGrau();
        //o
        std::vector<int> fechoTransitivoDireto(int idNo);
        //p
        std::vector<int> fechoTransitivoIndireto(int idNo);
        //q
        void apresentaSequenciaGraus();
        //r
        void imprimeSubInduzido(int total, std::vector<int> &n);
        //s
        Grafo* obterComplementar();

        //Auxiliares
        void reordenaIds();
        Grafo* obterSubjacente();
        int numComponentesConexas();
        void buscaProfundidade(int id, bool* visitados);
        int getMaiorId();
        void removerTodasAdj(int id);
        void imprimeGrafo();
        void ordenaVetor(int *vet, int n);
        bool verificarSimples();
        bool verificarSelfLoop();
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
