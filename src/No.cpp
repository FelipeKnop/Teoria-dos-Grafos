#include "No.h"

No::No(int id, int label, int dado)
{
    this->id = id;
    this->dado = dado;
    this->label = label;
    prox = NULL;
    adjRaiz = NULL;
    ultimaAdj = NULL;
    grau = 0;
    grauEntrada = 0;
    frequencia = -1;
    //ctor
}

No::~No()
{
    do {
        Adjacencia* adj = adjRaiz;
        if (adj != NULL) {
            adjRaiz = adj->getProx();
            delete adj;
        }
    } while (adjRaiz != NULL);
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
    if(aux == NULL) return;

    if(aux->getNoFim() == destino && aux->getPeso() == peso){
        if(aux==ultimaAdj) ultimaAdj = aux->getProx();
        adjRaiz = aux->getProx();
        delete aux;
        grau--;
    }else{
        while(aux->getProx()!=NULL && aux->getProx()->getNoFim() != destino && aux->getProx()->getPeso() != peso)
            aux = aux->getProx();
        if(aux->getProx()!=NULL){
            if(aux->getProx() == ultimaAdj) ultimaAdj = aux;
            Adjacencia* lixo = aux->getProx();
            aux->setProx(lixo->getProx());
            delete lixo;
            grau--;
        }
    }

}

//! Remover adjacencias
//! Esta função remove todas as adjacências do nó que tiverem o nó "destino" como a extremidade final.
void No::removerAdjs(No* destino){
    Adjacencia* aux = adjRaiz;
    if(aux == NULL) return;
    if(aux->getNoFim() == destino){
        if(aux==ultimaAdj) ultimaAdj = aux->getProx();
        adjRaiz = aux->getProx();
        delete aux;
        grau--;
    }else{
        while(aux->getProx()!=NULL && aux->getProx()->getNoFim() != destino)
            aux = aux->getProx();
        if(aux->getProx()!=NULL){
            if(aux->getProx() == ultimaAdj) ultimaAdj = aux;
            Adjacencia* lixo = aux->getProx();
            aux->setProx(lixo->getProx());
            delete lixo;
            grau--;
        }else{
            return;
        }
    }
    removerAdjs(destino);

}

//! Verificar se faz parte de multigrafo (busca multiaresta)
//! Função serve para auxiliar a verificação de multigrafo da classe Grafo. Quando encontra duas adjacências com o mesmo destino conclui que existe uma multiaresta
bool No::verificarMultiaresta(int ordem){
    bool* visitados = new bool[ordem];
    for(int i = 0;i<ordem;i++) visitados[i] = false;

    Adjacencia* aux = adjRaiz;
    while(aux!=NULL){
        No* dest = aux->getNoFim();
        int id = dest->getId();
        if(visitados[id-1] == false){
            visitados[id-1] = true;
        }else{
            return true; //é multigrafo
        }
        aux = aux->getProx();
    }
    return false;
}

//! Verificar se contém selfloop
//! Função serve para auxiliar a verificação de grafo simples da classe Grafo.
//! Quando encontra uma adjacência com o próprio nó como destino,
//! conclui que existe um selfloop
bool No::verificarSelfLoop(){
    Adjacencia* aux = adjRaiz;
    while(aux!=NULL){
        No* dest = aux->getNoFim();
        if (dest->getId() == getId())
            return true;
        aux = aux->getProx();
    }
    return false;
}

//!Função que confere se existe uma adjacência no nó com destino de determinado id
bool No::existeAdj(int destino){
    Adjacencia* aux = adjRaiz;
    while(aux!=NULL){
        No* dest = aux->getNoFim();
        if (dest->getId() == destino)
            return true;
        aux = aux->getProx();
    }
    return false;
}


//! Função para incrementar o grau de entrada do grafo (grafos direcionados) em i
void No::addGrauEntrada(int i){
    grauEntrada+=i;
}

//!Gets e seters


int No::getId(){
    return id;
}

void No::setId(int id) {
    this->id = id;
}

int No::getFrequencia()
{
    return frequencia;
}

void No::setFrequencia(int freq){
    frequencia = freq;
}

int No::getDado(){
    return dado;
}

int No::getLabel(){
    return label;
}

No* No::getProx(){
    return prox;
}

void No::setProx(No* no){
    prox = no;
}

int No::getGrau(){
    return getGrauEntrada() + getGrauSaida(); //Observe que grafos no direcionados retornam apenas o grau de saída, por grauEntrada = 0;
}

int No::getGrauEntrada(){
    return grauEntrada;
}

int No::getGrauSaida(){
    return grau;
}

Adjacencia* No::getAdjRaiz(){
    return adjRaiz;
}
