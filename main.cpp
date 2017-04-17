#include <iostream>
#include "Grafo.h"
#include "No.h"
#include "Adjacencia.h"

using namespace std;

int main()
{
    Grafo* grafo = new Grafo;
    grafo->criarNo(1,5);
    grafo->criarNo(2,3);
    grafo->imprimeNos();
    cout << "Hello world!" << endl;
    return 0;
}
