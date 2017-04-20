#include <iostream>
#include<fstream>
#include "Grafo.h"
#include "No.h"
#include "Adjacencia.h"


int main(int argc, const char* argv[])
{
    Grafo* grafo = new Grafo(true);

    bool arquivoExiste;
    if (argc > 1) {
        arquivoExiste = grafo->lerArquivo(argv[1]);
    } else {
        arquivoExiste = grafo->lerArquivo("grafo.txt");
    }

    if (!arquivoExiste) {
        std::cout << "Arquivo nao encontrado!";
        return 0;
    }

    //!Manipulações no grafo
    grafo->removerNo(1);

    //!Escrita
    //grafo->imprimir(argv[2]);
    grafo->imprimir("saida.txt");

    //!Informações
    grafo->informaOrdem();
    grafo->informaGrau();
    grafo->informaTrivial();
    grafo->informaNulo();
    grafo->apresentaSequenciaGraus();
    grafo->informaGrauNo(2);
    std::cout<<grafo->verificarMultigrafo();
    return 0;
}
