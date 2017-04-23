#ifndef GRAFO_H
#define GRAFO_H
#include "No.h"
#include "Adjacencia.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include <utility>

struct dfs
{
    int pai;
    int descoberto;
    int menor;
    bool articulacao;
};

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
        bool criarAdj(int idNo1, int idNo2, int peso);
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
        Grafo* vizinhancaAberta(int id);
        //i
        Grafo* vizinhancaFechada(int id);
        //j
        bool verificarMultigrafo();
        //k
        bool verificarCompleto();
        //l
        bool verificarBipartido();
        //m
        void imprimeResultadoDijkstra(int idOrigem, int idDestino);
        std::pair< std::vector<double>, std::vector<int> > menorCaminhoDijkstra(int idOrigem, int idDestino);
        void imprimeResultadoFloyd(int idOrigem, int idDestino);
        std::pair< std::vector< std::vector<double> >,
            std::vector< std::vector<int> > > geraMatrizesFloyd();
        //n
        int calculaGrau();
        //o
        std::vector<int> fechoTransitivoDireto(int idNo);
        //p
        std::vector<int> fechoTransitivoIndireto(int idNo);
        //q
        void apresentaSequenciaGraus();
        //r
        Grafo* subInduzido(int total, std::vector<int> &n);
        //s
        Grafo* obterComplementar();
        //t
        int componentesFortementeConexas(bool imprime); //retorna o numero de componentes fortemente conexas
        //u
        bool verificarEuleriano();
        //v
        std::vector<int> nosArticulacao();
        //x
        void imprimeRaioDiaCentPerif();
        //z
        dfs* buscaProfundidade();
        void buscaProfundidade(int id, bool *visitados, dfs *nos, int *tempo);

        //Auxiliares
        void ordenacaoTopologica(int v, bool visitados[], std::vector<int>& pilha);
        void buscaProfundidadeImprimindo(int v, bool visitados[]);
        void reordenaIds();
        Grafo* obterSubjacente();
        Grafo* grafoReverso();
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
