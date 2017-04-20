#include "Grafo.h"


Grafo::Grafo(bool direcionado)
{
    //ctor
    noRaiz = NULL;
    ordem = 0;
    this->direcionado = direcionado;
}

Grafo::~Grafo()
{
    //dtor
}

//! Cria��o de n�s
//! Fun�ao recebe um id e um dado e adiciona o n� na lista encadeada
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

//! Remo��o de n�
//! Funcao que recebe um id e remove o n� correpondente
void Grafo::removerNo(int id){
    No* aux = noRaiz;
    while(noRaiz->getProx()!= NULL && noRaiz->getProx()->getId()!=id)
        aux = aux->getProx();
    if(aux->getProx() != NULL){
        No* lixo= aux->getProx();
        aux->setProx(lixo->getProx());
        delete lixo;
        ordem--;
    }
}


//! Cria��o de adjac�ncia
//! A fun��o recebe dois ids e um peso para a aresta, e adiciona a adjac�ncia em ambos os n�s para o grafo n�o direcionado, ou apenas no primeiro para o direcionado
void Grafo::criarAdj(int idNo1, int idNo2,int peso){
    No *no1 = getNo(idNo1),*no2 = getNo(idNo2);
    if(no1!=NULL && no2!=NULL){
        no1->adicionarAdj(no2,peso);
        if(!direcionado)
            no2->adicionarAdj(no1,peso);
        else
            no2->addGrauEntrada(1);
    }else{
        std::cout<<"Adjacencia "<<idNo1<<","<<idNo2<<" nao pode ser criada!"<<std::endl;
    }
}

//! Remo�ao de adjacencia
//! A fun��o recebe dois n�s e o peso da aresta, e a remove devidamente do grafo, seja direcionado ou n�o
void Grafo::removerAdj(int idNo1,int idNo2,int peso){
    No *no1 = getNo(idNo1),*no2 = getNo(idNo2);
    if(no1!=NULL && no2!=NULL){
        no1->removerAdj(no2,peso);
        if(!direcionado)
            no2->removerAdj(no1,peso);
        else
            no2->addGrauEntrada(-1);
    }
}

//! Impress�o de n�s
//! Com a ajuda de uma fun��o auxiliar, imprimeNos imprime os ids e os dados de cada n�
void imprimeNo(No* no){
    std::cout<<no->getId()<<" "<<no->getDado()<<std::endl;
    if(no->getProx()!=NULL){
        imprimeNo(no->getProx());
    }
}

void Grafo::imprimeNos(){
    imprimeNo(noRaiz);
}



//! Obter N�
//! A fun�ao recebe um id e retorna um ponteiro para o n� correspondente.
No* auxGetNo(No* no, int id){
    if(no == NULL) return NULL;

    if(no->getId() == id) return no;
    else return auxGetNo(no->getProx(),id);
}

No* Grafo::getNo(int id){
    return auxGetNo(noRaiz,id);
}


//! Gets e seters

int Grafo::getOrdem(){
    return ordem;
}
