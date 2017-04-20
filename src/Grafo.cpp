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

//! Imprimir grafo
//! Fun��o que imprime o grafo em um arquivo
void Grafo::imprimir(char* caminho){
    std::ofstream saida(caminho);
    saida<<ordem<<std::endl;
    No* aux = noRaiz;
    while(aux!=NULL){
        Adjacencia* aux2 = aux->getAdjRaiz();
        while(aux2!=NULL){
            saida<<aux->getId()<<" "<< aux2->getNoFim()->getId() <<" "<< aux2->getPeso()<<std::endl;
            aux2 = aux2->getProx();
        }
        aux = aux->getProx();
    }
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
    if(aux == NULL) return;
    removerTodasAdj(id);
    if(aux->getId() == id){
        noRaiz = aux->getProx();
        delete aux;
        ordem--;
    }else{
        while(aux->getProx()!= NULL && aux->getProx()->getId()!=id)
            aux = aux->getProx();
        if(aux->getProx() != NULL){
            No* lixo= aux->getProx();
            aux->setProx(lixo->getProx());
            delete lixo;
            ordem--;
        }
    }
}


//! Fun��o que remove todas as adjac�ncias com um determinado id. Complementa a remo��o do n�.
void Grafo::removerTodasAdj(int id){
    No* remover = getNo(id);
    if(remover==NULL) return;

    No* aux = noRaiz;
    while(aux!=NULL){
        aux->removerAdjs(remover);
        aux = aux->getProx();
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


//! Informa a ordem do grafo
//! Chama a pr�pria fun��o getOrdem para obter essa informa��o e a imprime na tela
void Grafo::informaOrdem() {
    int ordemGrafo = getOrdem();
    std::cout << "Ordem do grafo: " << ordemGrafo << std::endl;
}

//! Informa se o grafo � trivial
//! Chama a pr�pria fun��o getOrdem para obter a ordem do grafo e, se ela for igual a 1,
//! imprime na tela que � um grafo trivial
void Grafo::informaTrivial() {
    int ordemGrafo = getOrdem();
    if (ordemGrafo <= 1) {
        std::cout << "O grafo " << char(130) << " trivial" << std::endl;
    } else {
        std::cout << "O grafo n" << char(198) << "o " << char(130) << " trivial" << std::endl;
    }
}

//! Informa se o grafo � nulo
//! Chama a pr�pria fun��o getOrdem para obter a ordem do grafo e, se ela for igual a 0,
//! imprime na tela que � um grafo nulo
void Grafo::informaNulo() {
    int ordemGrafo = getOrdem();
    if (ordemGrafo == 0) {
        std::cout << "O grafo " << char(130) << " nulo" << std::endl;
    } else {
        std::cout << "O grafo n" << char(198) << "o " << char(130) << " nulo" << std::endl;
    }
}

//! Gets e seters

int Grafo::getOrdem(){
    return ordem;
}
