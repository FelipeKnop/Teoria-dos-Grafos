#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include "Grafo.h"
#include "No.h"
#include "Adjacencia.h"
#include "Test.h"

int main(int argc, const char *argv[])
{
    // GrafosGrupo2.exe instancias/instance_30.txt 20 100 0.2 10 5

    if (argc <= 6) {
        std::cout << "Uso: nome_do_programa <arquivo_de_entrada> <numero_execucoes> <numero_iteracoes> <alpha_randomizado> <bloco_iteracoes> <numero_alphas>";
        return 1;
    }

    const char *arquivoEntrada = argv[1];
    int numExecucoes = strtol(argv[2], NULL, 10);
    int numIteracoes = strtol(argv[3], NULL, 10);
    float alpha = strtof(argv[4], NULL);
    int blocoIteracoes = strtol(argv[5], NULL, 10);
    int numAlphas = strtol(argv[6], NULL, 10);

    srand(time(NULL));
    Grafo *grafo = new Grafo(false, false);

    if (!grafo->lerArquivo(arquivoEntrada)) {
        std::cout << "Arquivo n" << char(198) << "o encontrado!";
        return 1;
    }

    grafo->imprimeInterferencias();
    int melhor;

    std::cout << "Guloso:" << std::endl;
    grafo->gulosoFrequencias();
    // grafo->imprimeGrafo();
    std::cout << "Interferencia total: " << grafo->calculaInterferenciaTotal() << std::endl;


    std::cout << std::endl << "Guloso randomizado:" << std::endl;
    for (int i = 0; i < numExecucoes; ++i) {
        melhor = grafo->gulosoRandomizadoFrequencias(numIteracoes, alpha);
        // grafo->imprimeGrafo();
        std::cout << "Interferencia total: " << melhor << std::endl;

    }

    std::cout << std::endl << "Guloso randomizado reativo:" << std::endl;
    for (int i = 0; i < numExecucoes; ++i) {
        melhor = grafo->gulosoRandomizadoReativoFrequencias(numIteracoes, blocoIteracoes, numAlphas);
        // grafo->imprimeGrafo();
        std::cout << "Interferencia total: " << melhor << std::endl;
    }

    return 0;
}
