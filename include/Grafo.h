#ifndef GRAFO_H
#define GRAFO_H
#include "No.h"
#include "Adjacencia.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <algorithm>
#define NUM_FREQ 14

struct dfs
{
    int label;
    int pai;
    int descoberto;
    int menor;
    bool articulacao;
};

struct bfs
{
    int label;
    int pai;
    int descoberto;
    int distancia;
};

typedef struct strNo{
    int id;
    int grau;
    int label;
    bool operator < (const strNo& s) const{ return grau<s.grau; } //define operador de comparacao
}structNo;

class Grafo
{
    public:
        float interferencias[NUM_FREQ][NUM_FREQ];
        Grafo(bool direcionado, bool ponderado);
        ~Grafo();
        //a
        bool lerArquivo(const char *caminho);
        void salvarArquivo(const char *caminho);
        //b
        void criarNo(int label, int dado);
        void removerNo(No *no);
        void removerNoPorLabel(int label);
        bool criarAdj(No *noInicio, No *noFim, int peso);
        void removerAdj(No *noInicio, No *noFim, int peso);
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
        bool ehNulo();
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
            std::vector< std::vector<int> > > geraMatrizesFloyd(bool ponderado);
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
        //w
        void arestaPonte();
        //x
        void imprimeRaioDiaCentPerif();
        //y
        Grafo* AGM();
        //z
        dfs* buscaProfundidade();
        void buscaProfundidade(int id, bool *visitados, dfs *nos, int *tempo);
        bfs* buscaLargura();
        //!Guloso final
        void gulosoFrequencias();
        //float calculaInterferenciaTotal()B uscar cada aresta e aplicar uma função de interferencia recebendo a frequencia das duas pontas. Mas qual é essa função de interferencia?
        void atualizaLC(std::vector<structNo> &LC, int i);
        void defineFrequencia(int label, Grafo* subjacente);
        std::vector<structNo> retornaNos();

        float calcularInterferencia(int freq, int frequencias[14]);

        //Auxiliares
        void limparNos();
        void ordenacaoTopologica(int v, bool visitados[], std::vector<int>& pilha);
        void buscaProfundidadeImprimindo(int v, bool visitados[]);
        void reordenaIds();
        Grafo* obterSubjacente();
        Grafo* grafoReverso();
        int numComponentesConexas();
        void buscaProfundidade(int id, bool* visitados);
        int getMaiorId();
        void removerTodasAdj(No *no);
        void imprimeGrafo();
        void ordenaVetor(int *vet, int n);
        bool verificarSimples();
        bool verificarSelfLoop();
        No* getNoPorId(int id);
        No* getNoPorLabel(int label);
        int getOrdem();

    private:
        bool direcionado;
        bool ponderado;
        No* noRaiz;
        No* ultimo;
        //descritores
        int ordem;
};

#endif // GRAFO_H
