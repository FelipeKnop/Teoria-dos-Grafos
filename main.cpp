#include <iostream>
#include<fstream>
#include "Grafo.h"
#include "No.h"
#include "Adjacencia.h"


int main(int argc, const char* argv[])
{
    //!Leitura
    std::ifstream file;

    //file.open(argv[1]);
    file.open("grafo.txt");

    if(!file){
        std::cout<<"Arquivo nao encontrado!";
        return 0;
    }

    Grafo* grafo = new Grafo(true);
    int n,i,d,p;
    file>>n;

    for(int i =1;i<=n;i++)
        grafo->criarNo(i,1);

    while(file>>i>>d>>p)
        grafo->criarAdj(i,d,p);


    //!Manipulações no grafo
    grafo->removerNo(1);

    //!Escrita
    //grafo->imprimir(argv[2]);
    grafo->imprimir("saida.txt");

    grafo->informaOrdem();
    grafo->informaTrivial();
    grafo->informaNulo();

    return 0;
}
