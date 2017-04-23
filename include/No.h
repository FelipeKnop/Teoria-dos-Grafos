#ifndef NO_H
#define NO_H
#include "Adjacencia.h"

class No
{
    public:
        No(int id, int dado);
        ~No();

        void adicionarAdj(No* destino, int peso);
        void removerAdj(No* destino, int peso);
        void removerAdjs(No* destino);
        bool verificarMultiaresta(int ordem);
        bool verificarSelfLoop();
        bool existeAdj(int destino);

        int getId();
        void setId(int id);
        int getDado();
        No* getProx();
        void setProx(No* no);
        int getGrau();
        int getGrauEntrada();
        int getGrauSaida();
        void addGrauEntrada(int i);
        Adjacencia* getAdjRaiz();


    protected:

    private:
        Adjacencia* adjRaiz;
        Adjacencia* ultimaAdj;
        int id;
        int dado;
        No* prox;

        //descritores:
        int grau; //Será considerado como grau de saída em grafos direcionados
        int grauEntrada; //para grafos direcionados
};

#endif // NO_H
