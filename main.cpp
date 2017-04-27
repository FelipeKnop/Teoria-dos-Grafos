#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"
#include "No.h"
#include "Adjacencia.h"
#include "Test.h"


int main(int argc, const char *argv[])
{
    int tipo;
    std::cout<<"Favor escolher o tipo do grafo:"<<std::endl;
    std::cout<< "1 - Grafo n"<<char(198)<<"o direcionado"<<std::endl;
    std::cout<< "2 - Grafo direcionado"<<std::endl;
    std::cin>>tipo;

    Grafo *grafo = new Grafo((tipo==1)?false:true);

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
        std::cout<<"ATEN" << char(128) << char(199) << "O: Os ids de um n" << char(162) << " s" << char(198) << "o incrementados e regulados automaticamente (estando sempre entre 1 e a ordem do grafo)."<<std::endl;
        std::cout<<"Para descobrir em qual n" << char(162) << " o seu dado est" << char(160) <<" armazenado, use a fun" << char(135) << char(198) << "o de imprimir grafo em @->2"<<std::endl;
        std::cout<<"Todos os n" << char(162) << "s s" << char(198) << "o aqui referenciados pelos seus ids"<<std::endl;

        std::cout << "# - Testes" << std::endl;
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
        std::cout << "M - Informar o menor caminho entre dois n" << char(162) << "s e seu custo" << std::endl;
        std::cout << "N - Imprimir o grau do grafo" << std::endl;
        std::cout << "O - Obter fecho transitivo direto" << std::endl;
        std::cout << "P - Obter fecho transitivo indireto" << std::endl;
        std::cout << "Q - Imprimir sequ" << char(136) << "ncia de graus" << std::endl;
        std::cout << "R - Obter subgrafo induzido" << std::endl;
        std::cout << "S - Obter complementar do grafo" << std::endl;
        std::cout << "T - Obter componentes fortemente conexos" << std::endl;
        std::cout << "U - Verificar se grafo " << char(130) << " euleriano" << std::endl;
        std::cout << "V - Obter n" << char(162) << "s de articula" << char(135) << char(198) << "o" << std::endl;
        std::cout << "W - Apresentar arestas pontes" << std::endl;
        std::cout << "X - Apresentar raio, di" << char(131) << "metro, centro e periferia do grafo" << std::endl;
        std::cout << "Y - Apresentar a AGM(" << char(181) <<"rvore Geradora M" << char(161) << "nima)" << std::endl;
        std::cout << "Z - Obter " << char(181) <<"rvores de busca em profundidade e largura" << std::endl;
        std::cout << "Escolha uma operac" << char(198) << "o ('!' para sair): ";
        std::cin >> operacao;

        if (operacao == '!')
            break;

        switch (operacao) {
            case '#': {
                std::cout << "1 - Gerar arquivo de resultados deste grafo" << std::endl;
                std::cout << "2 - Comparar arquivos de resultados" << std::endl;
                std::cout << "Escolha uma sub opera" << char(135) << char(198) << "o: ";
                std::cin >> subOperacao;

                switch (subOperacao) {
                    case '1': {
                        std::string nome;
                        std::cout << "Nome do arquivo: ";
                        std::cin >> nome;
                        geraResultado(nome.c_str(), grafo);
                        break;
                    }
                    case '2': {
                        std::string nome1, nome2;
                        std::cout << "Nome do arquivo 1: ";
                        std::cin >> nome1;
                        std::cout << "Nome do arquivo 2: ";
                        std::cin >> nome2;
                        if (!comparaResultado(nome1.c_str(), nome2.c_str()))
                            std::cout << "Resultados diferentes entre os arquivos!" << std::endl;
                        else
                            std::cout << "Resultados iguais entre os arquivos!" << std::endl;
                        break;
                    }
                }
                break;
            }
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
                std::cout << "1 - Reler arquivo de entrada" << std::endl;
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
                        int dado;
                        std::cout << "[dado numerico a ser armazenado]: ";
                        std::cin >> dado;
                        grafo->criarNo(dado);
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
                Grafo *vizinhancaAberta = grafo->vizinhancaAberta(id);
                vizinhancaAberta->imprimeGrafo();
                break;
            }
            case 'i':
            case 'I': {
                std::cout << "----------------------------" << std::endl;
                int id;
                std::cout << "[id]: ";
                std::cin >> id;
                Grafo* vizinhancaFechada = grafo->vizinhancaFechada(id);
                vizinhancaFechada->imprimeGrafo();
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
                int idOrigem, idDestino;
                std::cout << "[idOrigem]: ";
                std::cin >> idOrigem;
                std::cout << "[idDestino]: ";
                std::cin >> idDestino;

                if (idOrigem == idDestino) {
                    std::cout << "Digite ids diferentes" << std::endl;
                    break;
                }

                if (grafo->getNo(idOrigem) == NULL || grafo->getNo(idDestino) == NULL) {
                    std::cout << "Digite somente o id de n" << char(162) << "s que existem" << std::endl;
                    break;
                }

                std::cout << "1 - Dijkstra" << std::endl;
                std::cout << "2 - Floyd" << std::endl;
                std::cout << "Escolha uma sub opera" << char(135) << char(198) << "o: ";
                std::cin >> subOperacao;

                switch (subOperacao) {
                    case '1': {
                        grafo->imprimeResultadoDijkstra(idOrigem, idDestino);
                        break;
                    }
                    case '2': {
                        grafo->imprimeResultadoFloyd(idOrigem, idDestino);
                        break;
                    }
                }
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
                int id;
                std::cout << "[id]: ";
                std::cin >> id;
                std::cout<<std::endl;
                std::vector<int> ftd = grafo->fechoTransitivoDireto(id);
                for(int i = 0; i < static_cast<int>(ftd.size()); i++){
                    std::cout<<ftd.at(i)<<" ";
                }
                std::cout<<std::endl;
                break;
            }
            case 'p':
            case 'P': {
                std::cout << "----------------------------" << std::endl;
                int id;
                std::cout << "[id]: ";
                std::cin >> id;
                std::cout<<std::endl;
                std::vector<int> fti = grafo->fechoTransitivoIndireto(id);
                for(int i = 0; i < static_cast<int>(fti.size()); i++){
                    std::cout<<fti.at(i)<<" ";
                }
                std::cout<<std::endl;
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
                Grafo* subInduzido = grafo->subInduzido(numeroNos, nosVector);
                subInduzido->imprimeGrafo();
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
                grafo->componentesFortementeConexas(true);
                break;
            }
            case 'u':
            case 'U': {
                std::cout << "----------------------------" << std::endl;
                if (grafo->verificarEuleriano())
                    std::cout <<"Esse grafo " << char(130) << " " << "euleriano" << std::endl;
                else
                    std::cout <<"Esse grafo n" << char(198) << "o " << char(130) << " " << "euleriano" << std::endl;
                break;
            }
            case 'v':
            case 'V': {
                std::cout << "----------------------------" << std::endl;
                std::vector<int> articulacao = grafo->nosArticulacao();

                std::cout << "N" << char(162) << "s de articula" << char(135) << char(198) << "o: ";
                for (std::vector<int>::iterator it = articulacao.begin(); it < articulacao.end(); it++)
                    std::cout << *it << " ";
                std::cout << std::endl;
                break;
            }
            case 'w':
            case 'W': {
                std::cout << "----------------------------" << std::endl;
                grafo->arestaPonte();
                break;
            }
            case 'x':
            case 'X': {
                std::cout << "----------------------------" << std::endl;
                grafo->imprimeRaioDiaCentPerif();
                break;
            }
            case 'y':
            case 'Y': {
                std::cout << "----------------------------" << std::endl;
                Grafo* AGM = grafo->AGM();
                AGM->imprimeGrafo();
                break;
            }
            case 'z':
            case 'Z': {
                std::cout << "----------------------------" << std::endl;
                std::cout << "1 - " << char(181) <<"rvore de busca em profundidade" << std::endl;
                std::cout << "2 - " << char(181) <<"rvore de busca em largura" << std::endl;
                std::cout << "Escolha uma sub opera" << char(135) << char(198) << "o: ";
                std::cin >> subOperacao;

                int ordem = grafo->getOrdem();

                switch (subOperacao) {
                    case '1': {
                        dfs *nos = grafo->buscaProfundidade();

                        Grafo *arvore = new Grafo(true);
                        for (int i = 0; i < ordem; ++i)
                            arvore->criarNo(i+1, nos[i].menor);
                        for (int i = 0; i < ordem; ++i)
                        {
                            if (nos[i].pai != 0)
                                arvore->criarAdj(nos[i].pai, i+1, 1);
                        }
                        arvore->imprimeGrafo();
                        break;
                    }
                    case '2': {
                        bfs *nos = grafo->buscaLargura();

                        Grafo *arvore = new Grafo(true);
                        for (int i = 0; i < ordem; ++i)
                            arvore->criarNo(i+1, nos[i].distancia);
                        for (int i = 0; i < ordem; ++i)
                        {
                            if (nos[i].pai != 0)
                                arvore->criarAdj(nos[i].pai, i+1, 1);
                        }
                        arvore->imprimeGrafo();
                        break;
                    }
                }

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

    return 0;
}
