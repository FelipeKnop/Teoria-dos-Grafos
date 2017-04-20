#include <iostream>
#include<fstream>
#include<vector>
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
    //grafo->removerNo(1);

    //!Escrita
    //grafo->imprimir(argv[2]);
    grafo->imprimir("saida.txt");

    //!Informações
    grafo->informaOrdem();
    grafo->informaGrau();
    grafo->informaTrivial();
    grafo->informaNulo();
    grafo->apresentaSequenciaGraus();
    std::vector<int> nos;
    nos.reserve(3);
    nos.push_back(3);
    nos.push_back(2);
    nos.push_back(1);

    grafo->imprimeSubInduzido(3, nos);
    grafo->vizinhancaAberta(1);
    grafo->vizinhancaFechada(1);

    return 0;
}
