#include <iostream>
#include "Grafo.h"
#include "No.h"
#include "Adjacencia.h"

using namespace std;

int main()
{

    Grafo* grafo = new Grafo(false);
    grafo->criarNo(1,5);
    grafo->criarNo(2,3);
    grafo->criarAdj(1,2,5);
    grafo->imprimeNos();
    cout << "Hello world!" << grafo->getOrdem()<<"  "<< grafo->getNo(2)->getGrau() << endl;
    return 0;
}
