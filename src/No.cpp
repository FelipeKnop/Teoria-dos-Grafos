#include "No.h"

No::No(int id, int dado)
{
    this->id = id;
    this->dado = dado;
    prox = NULL;
    adjRaiz = NULL;
    ultimaAdj = NULL;
    grau = 0;

    //ctor
}

No::~No()
{
    //dtor
}

void No::adicionarAdj(No* destino, int peso){
    Adjacencia* adj = new Adjacencia(this,destino,peso);
    if(adjRaiz == NULL){
        adjRaiz = adj;
        ultimaAdj = adj;
    }else{
        ultimaAdj->setProx(adj);
        ultimaAdj = adj;
    }
    grau++;
}


int No::getDado(){
    return dado;
}

int No::getId(){
    return id;
}

No* No::getProx(){
    return prox;
}
void No::setProx(No* no){
    prox = no;
}

int No::getGrau(){
    return grau;
}
