#include "Grafo.h"


Grafo::Grafo()
{
    //ctor
    noRaiz = NULL;
    ordem = 0;
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
    ordem++;
}

//Função auxiliar para imprimir No
void imprimeNo(No* no){
    std::cout<<no->getId()<<" "<<no->getDado()<<std::endl;
    if(no->getProx()!=NULL){
        imprimeNo(no->getProx());
    }
}
//

void Grafo::imprimeNos(){
    imprimeNo(noRaiz);
}




void Grafo::criarAdj(int idNo1, int idNo2,int peso){
    No *no1 = getNo(idNo1),*no2 = getNo(idNo2);
    if(no1!=NULL && no2!=NULL){
        no1->adicionarAdj(no2,peso);
        //Se o grafo não for direcionado:
        no2->adicionarAdj(no1,peso);
    }else{
        std::cout<<"Adjacencia "<<idNo1<<","<<idNo2<<" nao pode ser criada!"<<std::endl;
    }
}


//auxiliar para buscar No
No* auxGetNo(No* no, int id){
    if(no == NULL) return NULL;

    if(no->getId() == id) return no;
    else return auxGetNo(no->getProx(),id);
}

//
No* Grafo::getNo(int id){
    return auxGetNo(noRaiz,id);
}

int Grafo::getOrdem(){
    return ordem;
}
