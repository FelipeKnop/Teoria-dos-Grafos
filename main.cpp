#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"
#include "No.h"
#include "Adjacencia.h"
#include "Test.h"


int main(int argc, const char *argv[])
{
    Grafo *grafo = new Grafo(false, false);

    const char *arquivoEntrada = "grafoT.txt";

    if (!grafo->lerArquivo(arquivoEntrada)) {
        std::cout << "Arquivo n" << char(198) << "o encontrado!";
        return 0;
    }

    grafo->imprimeInterferencias();

    grafo->gulosoFrequencias();
    grafo->imprimeGrafo();
    std::cout << "Interferencia total: " << grafo->calculaInterferenciaTotal() << std::endl;

    grafo->gulosoRandomizadoFrequencias();
    grafo->imprimeGrafo();
    std::cout << "Interferencia total: " << grafo->calculaInterferenciaTotal() << std::endl;

    return 0;
}
