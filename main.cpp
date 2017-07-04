#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include "Grafo.h"
#include "No.h"
#include "Adjacencia.h"
#include "Test.h"

#define NUM_ITERACOES 100

int main(int argc, const char *argv[])
{
    srand(time(NULL));
    Grafo *grafo = new Grafo(false, false);

    // const char *arquivoEntrada = "grafoT.txt";
    const char *arquivoEntrada = "instancias\\instance_30.txt";

    if (!grafo->lerArquivo(arquivoEntrada)) {
        std::cout << "Arquivo n" << char(198) << "o encontrado!";
        return 0;
    }

    grafo->imprimeInterferencias();
    int melhor;

    grafo->gulosoFrequencias();
    // grafo->imprimeGrafo();
    std::cout << "Interferencia total: " << grafo->calculaInterferenciaTotal() << std::endl;

    melhor = grafo->gulosoRandomizadoFrequencias(NUM_ITERACOES);
    // grafo->imprimeGrafo();
    std::cout << "Interferencia total: " << melhor << std::endl;

    melhor = grafo->gulosoRandomizadoReativoFrequencias(NUM_ITERACOES, 5, 10);
    // grafo->imprimeGrafo();
    std::cout << "Interferencia total: " << melhor << std::endl;

    return 0;
}
