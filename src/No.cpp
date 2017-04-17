#include "No.h"

No::No(int id, int dado)
{
    this->id = id;
    this->dado = dado;
    prox = NULL;
    adjRaiz = NULL;

    //ctor
}

No::~No()
{
    //dtor
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
