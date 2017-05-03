#include "Test.h"


bool comparaResultado(const char *caminho1, const char *caminho2) {
    std::ifstream file1(caminho1, std::ios::binary | std::ios::ate);
    std::ifstream file2(caminho2, std::ios::binary | std::ios::ate);

    if (!file1 || !file2) {
        std::cout << "Problema na leitura de um dos arquivos" << std::endl;
        return false;
    }

    if (file1.tellg() != file2.tellg()) {
        std::cout << "Tamanhos dos arquivos diferentes" << std::endl;
        return false;
    }

    std::vector<std::string> lines1, lines2;
    std::string aux;

    while (std::getline(file1, aux))
        lines1.push_back(aux);

    while (std::getline(file2, aux))
        lines2.push_back(aux);

    if (lines1.size() != lines2.size()) {
        std::cout << "Quantidades de linhas diferente entre os arquivos" << std::endl;
        return false;
    }

    std::vector<std::string>::iterator it1;
    std::vector<std::string>::iterator it2;

    for (it1 = lines1.begin(), it2 = lines2.begin(); it1 != lines1.end() && it2 != lines2.end(); it1++, it2++)
        if (*it1 != *it2) {
            std::cout << "Alguma linha dos arquivos é diferente" << std::endl;
            return false;
        }

    return true;
}

void geraResultado(const char *nome, Grafo* grafo) {
    freopen(nome, "w", stdout);

    int i, j, ordem = grafo->getOrdem();

    //e
    std::cout << "Ordem do grafo: " << grafo->getOrdem() << std::endl;

    //f
    grafo->informaTrivial();

    //g
    grafo->informaNulo();

    //j
    if (grafo->verificarMultigrafo())
        std::cout << "O grafo " << char(130) << " multigrafo" << std::endl;
    else
        std::cout << "O grafo n" << char(198) << "o " << char(130) << " multigrafo" << std::endl;

    //k
    if (grafo->verificarCompleto())
        std::cout <<"Esse grafo " << char(130) << " " << "completo" << std::endl;
    else
        std::cout <<"Esse grafo n" << char(198) << "o " << char(130) << " " << "completo" << std::endl;

    //l
    if (grafo->verificarBipartido())
        std::cout <<"Esse grafo " << char(130) << " " << "bipartido" << std::endl;
    else
        std::cout <<"Esse grafo n" << char(198) << "o " << char(130) << " " << "bipartido" << std::endl;

    //n
    std::cout << "Grau do grafo: " << grafo->calculaGrau() << std::endl;

    //q
    grafo->apresentaSequenciaGraus();

    //s
    Grafo* comp = grafo->obterComplementar();
    comp->imprimeGrafo();

    //t
    grafo->componentesFortementeConexas(true);

    //u
    if (grafo->verificarEuleriano())
        std::cout <<"Esse grafo " << char(130) << " " << "euleriano" << std::endl;
    else
        std::cout <<"Esse grafo n" << char(198) << "o " << char(130) << " " << "euleriano" << std::endl;

    //v
    std::vector<int> articulacao = grafo->nosArticulacao();

    std::cout << "N" << char(162) << "s de articula" << char(135) << char(198) << "o: ";
    for (std::vector<int>::iterator it = articulacao.begin(); it < articulacao.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    //w
    grafo->arestaPonte();

    //x
    grafo->imprimeRaioDiaCentPerif();

    //y
    Grafo* AGM = grafo->AGM();
    AGM->imprimeGrafo();

    //z
    dfs *nos = grafo->buscaProfundidade();

    Grafo *arvore = new Grafo(true);
    for (i = 0; i < ordem; ++i)
        arvore->criarNo(i+1, nos[i].menor);
    for (i = 0; i < ordem; ++i) {
        if (nos[i].pai != 0)
            arvore->criarAdj(nos[i].pai, i+1, 1);
    }
    arvore->imprimeGrafo();

    bfs *nos2 = grafo->buscaLargura();

    Grafo *arvore2 = new Grafo(true);
    for (i = 0; i < ordem; ++i)
        arvore2->criarNo(i+1, nos2[i].distancia);
    for (i = 0; i < ordem; ++i) {
        if (nos2[i].pai != 0)
            arvore2->criarAdj(nos2[i].pai, i+1, 1);
    }
    arvore2->imprimeGrafo();

    for (i = 1; i <= ordem; i++) {
        //c
        grafo->informaGrauNo(i);

        //d
        if (grafo->verificaRegularidade(i))
            std::cout << "Esse grafo " << char(130) << " " << i << "-regular" << std::endl;
        else
            std::cout <<"Esse grafo n" << char(198) << "o " << char(130) << " " << i << "-regular" << std::endl;

        //h
        Grafo *vizinhancaAberta = grafo->vizinhancaAberta(i);
        vizinhancaAberta->imprimeGrafo();

        //i
        Grafo* vizinhancaFechada = grafo->vizinhancaFechada(i);
        vizinhancaFechada->imprimeGrafo();

        //o
        std::vector<int> ftd = grafo->fechoTransitivoDireto(i);
        for(j = 0; j < static_cast<int>(ftd.size()); j++){
            std::cout<<ftd.at(j)<<" ";
        }
        std::cout<<std::endl;

        //p
        std::vector<int> fti = grafo->fechoTransitivoIndireto(i);
        for(j = 0; j < static_cast<int>(fti.size()); j++){
            std::cout<<fti.at(j)<<" ";
        }
        std::cout<<std::endl;

        //m
        for (j = 1; j <= ordem; j++) {
            grafo->imprimeResultadoDijkstra(i, j);
            grafo->imprimeResultadoFloyd(i, j);
        }

        //TODO: letra R
    }

    freopen("CON", "w", stdout);
}
