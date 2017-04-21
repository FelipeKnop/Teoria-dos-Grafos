#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"
#include "No.h"
#include "Adjacencia.h"


int main(int argc, const char *argv[])
{
    Grafo *grafo = new Grafo(true);

    const char *arquivoEntrada = "grafo.txt";
    const char *arquivoSaida = "saida.txt";

    if (argc > 1) {
        arquivoEntrada = argv[1];
    }
    if (argc > 2) {
        arquivoSaida = argv[2];
    }

    if (!grafo->lerArquivo(arquivoEntrada)) {
        std::cout << "Arquivo nao encontrado!";
        return 0;
    }
    for (;;) {
        char operacao, subOperacao;
        std::cout << "@ - Operacoes extras" << std::endl;
        std::cout << "A - Leitura e escrita" << std::endl;
        std::cout << "B - Criar e remover nos e adjacencias" << std::endl;
        std::cout << "C - Imprimir grau de um no" << std::endl;
        std::cout << "D - Verificar se o grafo e k-regular" << std::endl;
        std::cout << "E - Imprimir ordem do grafo" << std::endl;
        std::cout << "F - Verificar se o grafo e trivial" << std::endl;
        std::cout << "G - Verificar se o grafo e nulo" << std::endl;
        std::cout << "J - Verificar se o grafo e multigrafo" << std::endl;
        std::cout << "L - Verificar se o grafo e bipartido" << std::endl;
        std::cout << "N - Imprimir o grau do grafo" << std::endl;
        std::cout << "Q - Imprimir sequencia de graus" << std::endl;
        std::cout << "R - Obter subgrafo induzido" << std::endl;
        std::cout << "S - Obter complementar do grafo" << std::endl;
        std::cout << "Escolha uma operacao ('!' para sair): ";
        std::cin >> operacao;

        if (operacao == '!')
            break;

        switch (operacao) {
            case '@': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "1 - Remover todas as adjacencias" << std::endl;
                std::cout << "2 - Imprimir grafo" << std::endl;
                std::cout << "Escolha uma sub operacao: ";
                std::cin >> subOperacao;

                switch (subOperacao) {
                    case '1': {
                        int id;
                        std::cout << "[id]: ";
                        std::cin >> id;
                        grafo->removerTodasAdj(id);
                        break;
                    }
                    case '2': {
                        grafo->imprimeGrafo();
                        break;
                    }
                }
                break;
            }
            case 'a':
            case 'A': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "1 - Ler arquivo" << std::endl;
                std::cout << "2 - Salvar arquivo" << std::endl;
                std::cout << "Escolha uma sub operacao: ";
                std::cin >> subOperacao;

                switch (subOperacao) {
                    case '1': {
                        grafo->lerArquivo(arquivoEntrada);
                        break;
                    }
                    case '2': {
                        grafo->salvarArquivo(arquivoSaida);
                        break;
                    }
                }

                break;
            }
            case 'b':
            case 'B': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "1 - Criar no" << std::endl;
                std::cout << "2 - Criar adjacencia" << std::endl;
                std::cout << "3 - Remover no" << std::endl;
                std::cout << "4 - Remover adjacencia" << std::endl;
                std::cout << "Escolha uma sub operacao: ";
                std::cin >> subOperacao;

                switch (subOperacao) {
                    case '1': {
                        int id, dado;
                        std::cout << "[id, dado]: ";
                        std::cin >> id >> dado;
                        grafo->criarNo(id, dado);
                        break;
                    }
                    case '2': {
                        int idNoInicio, idNoFim, peso;
                        std::cout << "[idNoInicio, idNoFim, peso]: ";
                        std::cin >> idNoInicio >> idNoFim >> peso;
                        grafo->criarAdj(idNoInicio, idNoFim, peso);
                        break;
                    }
                    case '3': {
                        int id;
                        std::cout << "[id]: ";
                        std::cin >> id;
                        grafo->removerNo(id);
                        break;
                    }
                    case '4': {
                        int idNoInicio, idNoFim, peso;
                        std::cout << "[idNoInicio, idNoFim, peso]: ";
                        std::cin >> idNoInicio >> idNoFim >> peso;
                        grafo->removerAdj(idNoInicio, idNoFim, peso);
                        break;
                    }
                }

                break;
            }
            case 'c':
            case 'C': {
                std::cout << "----------------------------" << std::endl;
                int id;
                std::cout << "[id]: ";
                std::cin >> id;
                grafo->informaGrauNo(id);
                break;
            }
            case 'd':
            case 'D': {
                std::cout << "----------------------------" << std::endl;
                int k;
                std::cout << "[k]: ";
                std::cin >> k;
                if (grafo->verificaRegularidade(k))
                    std::cout << "Esse grafo " << char(130) << " " << k << "-regular" << std::endl;
                else
                    std::cout <<"Esse grafo n" << char(198) << "o " << char(130) << " " << k << "-regular" << std::endl;
                break;
            }
            case 'e':
            case 'E': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Ordem do grafo: " << grafo->getOrdem() << std::endl;
                break;
            }
            case 'f':
            case 'F': {
                std::cout << "----------------------------" << std::endl;
                grafo->informaTrivial();
                break;
            }
            case 'g':
            case 'G': {
                std::cout << "----------------------------" << std::endl;
                grafo->informaNulo();
                break;
            }
            case 'h':
            case 'H': {
                std::cout << "----------------------------" << std::endl;
                int id;
                std::cout << "[id]: ";
                std::cin >> id;
                grafo->vizinhancaAberta(id);
                break;
            }
            case 'i':
            case 'I': {
                std::cout << "----------------------------" << std::endl;
                int id;
                std::cout << "[id]: ";
                std::cin >> id;
                grafo->vizinhancaFechada(id);
                break;
            }
            case 'j':
            case 'J': {
                std::cout << "----------------------------" << std::endl;
                std::cout << (grafo->verificarMultigrafo() ?
                    "O grafo e multigrafo":
                    "O grafo nao e multigrafo")
                    << std::endl;
                break;
            }
            case 'k':
            case 'K': {
                std::cout << "----------------------------" << std::endl;
                if (grafo->verificarCompleto())
                    std::cout <<"Esse grafo " << char(130) << " " << "completo" << std::endl;
                else
                    std::cout <<"Esse grafo n" << char(198) << "o " << char(130) << " " << "completo" << std::endl;
                break;
            }
            case 'l':
            case 'L': {
                std::cout << "----------------------------" << std::endl;
                if (grafo->verificarBipartido())
                    std::cout <<"Esse grafo " << char(130) << " " << "bipartido" << std::endl;
                else
                    std::cout <<"Esse grafo n" << char(198) << "o " << char(130) << " " << "bipartido" << std::endl;
                break;
            }
            case 'm':
            case 'M': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Funcao nao implementada!" << std::endl;
                break;
            }
            case 'n':
            case 'N': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Grau do grafo: " << grafo->calculaGrau() << std::endl;
                break;
            }
            case 'o':
            case 'O': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Funcao nao implementada!" << std::endl;
                break;
            }
            case 'p':
            case 'P': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Funcao nao implementada!" << std::endl;
                break;
            }
            case 'q':
            case 'Q': {
                std::cout << "----------------------------" << std::endl;
                grafo->apresentaSequenciaGraus();
                break;
            }
            case 'r':
            case 'R': {
                std::cout << "----------------------------" << std::endl;
                int numeroNos;
                std::cout << "Numero de nos: ";
                std::cin >> numeroNos;

                int nos[numeroNos];
                for (int i = 0; i < numeroNos; i++) {
                    std::cout << "[id(" << i << ")]: ";
                    std::cin >> nos[i];
                }

                std::vector<int> nosVector(nos, nos + numeroNos);
                grafo->imprimeSubInduzido(numeroNos, nosVector);
                break;
            }
            case 's':
            case 'S': {
                std::cout << "----------------------------" << std::endl;
                Grafo* comp = grafo->obterComplementar();
                comp->imprimeGrafo();
                break;
            }
            case 't':
            case 'T': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Funcao nao implementada!" << std::endl;
                break;
            }
            case 'u':
            case 'U': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Funcao nao implementada!" << std::endl;
                break;
            }
            case 'v':
            case 'V': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Funcao nao implementada!" << std::endl;
                break;
            }
            case 'w':
            case 'W': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Funcao nao implementada!" << std::endl;
                break;
            }
            case 'x':
            case 'X': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Funcao nao implementada!" << std::endl;
                break;
            }
            case 'y':
            case 'Y': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Funcao nao implementada!" << std::endl;
                break;
            }
            case 'z':
            case 'Z': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Funcao nao implementada!" << std::endl;
                break;
            }

            default:
                std::cout << "----------------------------" << std::endl;
                std::cout << "Opcao invalida!" << std::endl;
        }

        std::cout << "============================" << std::endl;
    }

    //!Manipulações no grafo
    //grafo->removerNo(1);

    //!Escrita
    grafo->salvarArquivo(arquivoSaida);

    //!Informações
    grafo->informaOrdem();
    grafo->informaGrau();
    grafo->informaTrivial();
    grafo->informaNulo();
    grafo->apresentaSequenciaGraus();

    grafo->informaGrauNo(2);

    std::cout << grafo->verificarMultigrafo();

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
