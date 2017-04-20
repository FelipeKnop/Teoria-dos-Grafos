#include "Adjacencia.h"

Adjacencia::Adjacencia(No* inicio, No* fim, int peso)
{
    noInicio = inicio;
    noFim = fim;
    this->peso = peso;
    prox = NULL;
}

Adjacencia::~Adjacencia()
{
    //dtor
}


//!Gets e Seters

No* Adjacencia::getNoFim(){
    return noFim;
}

int Adjacencia::getPeso(){
    return peso;
}


void Adjacencia::setProx(Adjacencia* adj){
    prox = adj;
}

Adjacencia* Adjacencia::getProx(){
    return prox;
}
