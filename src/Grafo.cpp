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
//! Função que imprime o grafo em um arquivo
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


//! Criação de nós
//! Funçao recebe um id e um dado e adiciona o nó na lista encadeada
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

//! Remoção de nó
//! Funcao que recebe um id e remove o nó correpondente
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


//! Função que remove todas as adjacências com um determinado id. Complementa a remoção do nó.
void Grafo::removerTodasAdj(int id){
    No* remover = getNo(id);
    if(remover==NULL) return;

    No* aux = noRaiz;
    while(aux!=NULL){
        aux->removerAdjs(remover);
        aux = aux->getProx();
    }
}


//! Criação de adjacência
//! A função recebe dois ids e um peso para a aresta, e adiciona a adjacência em ambos os nós para o grafo não direcionado, ou apenas no primeiro para o direcionado
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

//! Remoçao de adjacencia
//! A função recebe dois nós e o peso da aresta, e a remove devidamente do grafo, seja direcionado ou não
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

//! Impressão de nós
//! Com a ajuda de uma função auxiliar, imprimeNos imprime os ids e os dados de cada nó
void imprimeNo(No* no){
    std::cout<<no->getId()<<" "<<no->getDado()<<std::endl;
    if(no->getProx()!=NULL){
        imprimeNo(no->getProx());
    }
}

void Grafo::imprimeNos(){
    imprimeNo(noRaiz);
}



//! Obter Nó
//! A funçao recebe um id e retorna um ponteiro para o nó correspondente.
No* auxGetNo(No* no, int id){
    if(no == NULL) return NULL;

    if(no->getId() == id) return no;
    else return auxGetNo(no->getProx(),id);
}

No* Grafo::getNo(int id){
    return auxGetNo(noRaiz,id);
}


//! Informa a ordem do grafo
//! Chama a própria função getOrdem para obter essa informação e a imprime na tela
void Grafo::informaOrdem() {
    int ordemGrafo = getOrdem();
    std::cout << "Ordem do grafo: " << ordemGrafo << std::endl;
}

//! Informa se o grafo é trivial
//! Chama as funções do grafo para obter a ordem e o grau,
//! se o grau for igual a 0 e a ordem igual a 1, imprime na tela que é um grafo trivial,
//! imprime que não é caso contrário
void Grafo::informaTrivial() {
    if (getOrdem() == 1 && calculaGrau() == 0) {
        std::cout << "O grafo " << char(130) << " trivial" << std::endl;
    } else {
        std::cout << "O grafo n" << char(198) << "o " << char(130) << " trivial" << std::endl;
    }
}

//! Informa se o grafo é nulo
//! Chama as funções do grafo para obter a ordem e o grau,
//! se o grau e a ordem forem iguais a 0, imprime na tela que é um grafo nulo,
//! imprime que não é caso contrário
void Grafo::informaNulo() {
    if (getOrdem() == 0 && calculaGrau() == 0) {
        std::cout << "O grafo " << char(130) << " nulo" << std::endl;
    } else {
        std::cout << "O grafo n" << char(198) << "o " << char(130) << " nulo" << std::endl;
    }
}

//! Imprime na tela a sequência de graus do grafo
//! Percorre a lista encadeada de nós obtendo esses graus e imprimindo
void Grafo::apresentaSequenciaGraus() {
    int n = getOrdem();
    int i = 0;
    int* sequencia = new int[n];
    No* aux = noRaiz;
    while (aux != NULL) {
        sequencia[i] = aux->getGrau();
        aux = aux->getProx();
        i++;
    }
    ordenaSequencia(sequencia, n);
    std::cout << "Sequ" << char(136) << "ncia de graus: ";
    for (i = 0; i < n; i++)
        std::cout << sequencia[i] << " ";
    std::cout << std::endl;
}
//!Verifica se o grafo é k-regular
//!Percorre a lista encadeada buscando nós com grau diferente de k
void Grafo::verificaRegularidade(int k) {
    No* aux = noRaiz;
    while (aux != NULL) {
        if (aux->getGrau()!=k){
            std::cout <<"Esse grafo n"<<char(198) <<"o "<<char(130) <<" "<< k << "-regular" << std::endl;
            return;
        }
    }
    std::cout <<"Esse grafo "<<char(130) <<" "<< k << "-regular" << std::endl;
}

//! Calcula o grau do grafo
//! Percorre todos os nós obtendo o grau de cada um e mantendo registro do maior
int Grafo::calculaGrau() {
    No* aux = noRaiz;
    int maior = 0;
    while(aux != NULL) {
        if (aux->getGrau() > maior)
            maior = aux->getGrau();
        aux = aux->getProx();
    }
    return maior;
}

void Grafo::informaGrau() {
    std::cout << "Grau do grafo: " << calculaGrau() << std::endl;
}

void Grafo::ordenaSequencia(int* sequencia, int n) {
    int i, j, aux;

    for (i = 1; i < n; i++) {
        aux = sequencia[i];
        for (j = i - 1; j >= 0 && sequencia[j] > aux; j--)
            sequencia[j+1] = sequencia[j];
        sequencia[j+1] = aux;
    }
}

//!Imprime o subgrafo induzido por um conjunto de nós informados pelos seus ids
void Grafo::imprimeSubInduzido(int total, std::vector<int> &n){
    No* aux;
    Adjacencia *adj;
    int noId;
    for(int i=0;i<total;i++){
        aux = getNo(n.at(i));
        if(aux!=NULL)
        {
            std::cout<< "No " << n.at(i) << ":" << std::endl;
            adj = aux->getAdjRaiz();
            while(adj!=NULL){
                noId = adj->getNoFim()->getId();
                for(int k=0;k<total;k++){
                    if (noId == n.at(k)){
                        std::cout << "\t" << n.at(i) <<"\t" << n.at(k) <<"\t" << adj->getPeso() << std::endl;
                        break;
                    }
                }
                adj = adj->getProx();
            }
        }

    }
}

//!imprime a vizinhanca aberta de um no
void Grafo::vizinhancaAberta(int id){
    No* aux = getNo(id);
    Adjacencia* adj = aux->getAdjRaiz();
    std::vector<int> nos;
    int i=0;
    while(adj!=NULL){
        i++;
        nos.resize(i);
        nos.push_back(adj->getNoFim()->getId());
        adj = adj->getProx();
    }
    imprimeSubInduzido(nos.size(), nos);
}
//!imprime a vizinhanca fechada de um no
void Grafo::vizinhancaFechada(int id){
    No* aux = getNo(id);
    Adjacencia* adj = aux->getAdjRaiz();
    std::vector<int> nos;
    int i=1;
    nos.reserve(i);
    nos.push_back(id);
    while(adj!=NULL){
        i++;
        nos.resize(i);
        nos.push_back(adj->getNoFim()->getId());
        adj = adj->getProx();
    }imprimeSubInduzido(nos.size(), nos);
}
//! Gets e seters

int Grafo::getOrdem(){
    return ordem;
}
