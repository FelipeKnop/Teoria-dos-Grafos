#include <iostream>
#include<fstream>
#include<vector>
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

    grafo->informaGrauNo(2);
    std::cout<<grafo->verificarMultigrafo();
        
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
