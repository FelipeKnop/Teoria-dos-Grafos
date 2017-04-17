#include "Grafo.h"


Grafo::Grafo()
{
    //ctor
    noRaiz = NULL;
}

Grafo::~Grafo()
{
    //dtor
}

void Grafo::criarNo(int id, int dado){
    No* no = new No(id,dado);
    if(noRaiz == NULL){
        noRaiz = no;
        ultimo = no;
    }else{
        ultimo->setProx(no);
        ultimo = no;
    }
}

//Função auxiliar para imprimir No
void imprimeNo(No* no){
    std::cout<<no->getId()<<" "<<no->getDado()<<std::endl;
    if(no->getProx()!=NULL){
        imprime(no->getProx());
    }
}
//

void Grafo::imprimeNos(){
    imprimeNo(noRaiz);
}




void Grafo::criarAdj(int idNo1, int idNo2){
}

bool Grafo::buscaProfundidade(int dado){
}
