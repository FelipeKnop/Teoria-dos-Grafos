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
        std::cout << "Arquivo n" << char(198) << "o encontrado!";
        return 0;
    }
    for (;;) {
        char operacao, subOperacao;
        std::cout << "@ - Opera" << char(135) << char(228) << "es extras" << std::endl;
        std::cout << "A - Leitura e escrita" << std::endl;
        std::cout << "B - Criar e remover n" << char(162) << "s e adjac" << char(136) << "ncias" << std::endl;
        std::cout << "C - Imprimir grau de um n" << char(162) << std::endl;
        std::cout << "D - Verificar se o grafo " << char(130) << " k-regular" << std::endl;
        std::cout << "E - Imprimir ordem do grafo" << std::endl;
        std::cout << "F - Verificar se o grafo " << char(130) << " trivial" << std::endl;
        std::cout << "G - Verificar se o grafo " << char(130) << " nulo" << std::endl;
        std::cout << "H - Mostrar a vizinhan" << char(135) << "a aberta de um dado n" << char(162) << std::endl;
        std::cout << "I - Mostrar a vizinhan" << char(135) << "a fechada de um dado n" << char(162) << std::endl;
        std::cout << "J - Verificar se o grafo " << char(130) << " multigrafo" << std::endl;
        std::cout << "K - Verificar se o grafo " << char(130) << " um grafo completo" << std::endl;
        std::cout << "L - Verificar se o grafo " << char(130) << " bipartido" << std::endl;
        std::cout << "N - Imprimir o grau do grafo" << std::endl;
        std::cout << "Q - Imprimir sequ" << char(136) << "ncia de graus" << std::endl;
        std::cout << "R - Obter subgrafo induzido" << std::endl;
        std::cout << "S - Obter complementar do grafo" << std::endl;
        std::cout << "Escolha uma operac" << char(198) << "o ('!' para sair): ";
        std::cin >> operacao;

        if (operacao == '!')
            break;

        switch (operacao) {
            case '@': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "1 - Remover todas as adjac" << char(136) << "ncias" << std::endl;
                std::cout << "2 - Imprimir grafo" << std::endl;
                std::cout << "Escolha uma sub opera" << char(135) << char(198) << "o: ";
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
                std::cout << "Escolha uma sub opera" << char(135) << char(198) << "o: ";
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
                std::cout << "1 - Criar n" << char(162) << std::endl;
                std::cout << "2 - Criar adjac" << char(136) << "ncia" << std::endl;
                std::cout << "3 - Remover n" << char(162) << std::endl;
                std::cout << "4 - Remover adjac" << char(136) << "ncia" << std::endl;
                std::cout << "Escolha uma sub opera" << char(135) << char(198) << "o: ";
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
                if (grafo->verificarMultigrafo())
                    std::cout << "O grafo " << char(130) << " multigrafo" << std::endl;
                else
                    std::cout << "O grafo n" << char(198) << "o " << char(130) << " multigrafo" << std::endl;
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
                std::cout << "Fun" << char(135) << char(198) << "o n" << char(198) << "o implementada!" << std::endl;
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
                std::cout << "Fun" << char(135) << char(198) << "o n" << char(198) << "o implementada!" << std::endl;
                break;
            }
            case 'p':
            case 'P': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Fun" << char(135) << char(198) << "o n" << char(198) << "o implementada!" << std::endl;
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
                std::cout << "N" << char(163) << "mero de n" << char(162) << "s: ";
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
                std::cout << "Fun" << char(135) << char(198) << "o n" << char(198) << "o implementada!" << std::endl;
                break;
            }
            case 'u':
            case 'U': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Fun" << char(135) << char(198) << "o n" << char(198) << "o implementada!" << std::endl;
                break;
            }
            case 'v':
            case 'V': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Fun" << char(135) << char(198) << "o n" << char(198) << "o implementada!" << std::endl;
                break;
            }
            case 'w':
            case 'W': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Fun" << char(135) << char(198) << "o n" << char(198) << "o implementada!" << std::endl;
                break;
            }
            case 'x':
            case 'X': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Fun" << char(135) << char(198) << "o n" << char(198) << "o implementada!" << std::endl;
                break;
            }
            case 'y':
            case 'Y': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Fun" << char(135) << char(198) << "o n" << char(198) << "o implementada!" << std::endl;
                break;
            }
            case 'z':
            case 'Z': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "Fun" << char(135) << char(198) << "o n" << char(198) << "o implementada!" << std::endl;
                break;
            }

            default:
                std::cout << "----------------------------" << std::endl;
                std::cout << "Op" << char(135) << char(198) << "o inv" << char(160) << "lida!" << std::endl;
        }

        std::cout << "============================" << std::endl;
    }

    //!Manipulações no grafo
    //grafo->removerNo(1);

    //!Escrita
    grafo->salvarArquivo(arquivoSaida);

    //!Informações
    grafo->informaOrdem();
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
