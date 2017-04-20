#include "No.h"

No::No(int id, int dado)
{
    this->id = id;
    this->dado = dado;
    prox = NULL;
    adjRaiz = NULL;
    ultimaAdj = NULL;
    grau = 0;
    grauEntrada = 0;
    //ctor
}

No::~No()
{
    //!implementar esse destrutor para apagar toda a lista de adjacencias
}
//! Adicionar adjacencia
//! A função recebe um nó de destino e um peso e adiciona a adjacencia na lista do nó que a chamou
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

//! Remover adjacencia
//! A função recebe um nó de destino e um peso e remove a aresta correspondente
void No::removerAdj(No* destino, int peso){
    Adjacencia* aux = adjRaiz;
    if(aux!=NULL){
        while(aux->getProx()!=NULL && aux->getProx()->getNoFim() != destino && aux->getProx()->getPeso() != peso)
            aux = aux->getProx();
        if(aux->getProx()!=NULL){
            Adjacencia* lixo = aux->getProx();
            aux->setProx(lixo->getProx());
            delete lixo;
            grau--;
        }
    }

}


//! Função para incrementar o grau de entrada do grafo (grafos direcionados) em i
void No::addGrauEntrada(int i){
    grauEntrada+=i;
}

//!Gets e seters


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

int No::getGrauEntrada(){
    return grauEntrada;
}
