#include "Adjacencia.h"

Adjacencia::Adjacencia(No* inicio, No* fim, int peso)
{
    noInicio = inicio;
    noFim = fim;
    peso = peso;
    prox = NULL;
}

Adjacencia::~Adjacencia()
{
    //dtor
}


void Adjacencia::setProx(Adjacencia* adj){
    prox = adj;
}

Adjacencia* Adjacencia::getProx(){
    return prox;
}
