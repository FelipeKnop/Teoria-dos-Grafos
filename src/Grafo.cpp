#include "Grafo.h"
#include <vector>
#include <time.h>
#include <math.h>


Grafo::Grafo(bool direcionado, bool ponderado)
{
    noRaiz = NULL;
    ultimo = NULL;
    ordem = 0;
    this->direcionado = direcionado;
    this->ponderado = ponderado;
    std::ifstream matrixInterf("interferencias.txt");
     for(int i = 0;i<NUM_FREQ;i++){
        for(int j = 0;j<NUM_FREQ;j++){
//            if(i==j) interferencias[i][j] = 100;
//            else if(abs(i-j)>4) interferencias[i][j] = 0;
//            else interferencias[i][j] = floor(exp(-abs(i-j))*100);
            matrixInterf>>interferencias[i][j];
        }
    }
}

Grafo::~Grafo()
{
}

//!a

//! Ler um arquivo
//! Função que lê o grafo de um arquivo. Recebe o caminho do arquivo a ser lido
//! e se o grafo é ponderado ou não.
bool Grafo::lerArquivo(const char *caminho)
{
    std::ifstream file(caminho);

    if (!file) {
        return false;
    }

    if(noRaiz!=NULL){
        limparNos();
    }
    int ordem, labelNoInicio, labelNoFim, peso;
    file >> ordem;

    for (int i = 1; i <= ordem; i++)
        criarNo(i, i);

    if (ponderado == 1) {
        while (file >> labelNoInicio >> labelNoFim >> peso) {
            No *noInicio = getNoPorLabel(labelNoInicio);
            No *noFim = getNoPorLabel(labelNoFim);
            criarAdj(noInicio, noFim, peso);
        }
    } else {
        while (file >> labelNoInicio >> labelNoFim) {
            No *noInicio = getNoPorLabel(labelNoInicio);
            No *noFim = getNoPorLabel(labelNoFim);
            criarAdj(noInicio, noFim, 1);
        }
    }

    return true;
}


//! Salvar um arquivo
//! Função que imprime o grafo em um arquivo. Recebe o caminho do arquivo que
//! será salvo e se o grafo é ponderado ou não.
void Grafo::salvarArquivo(const char *caminho)
{
    std::ofstream saida(caminho);
    saida << ordem << std::endl;
    No *aux = noRaiz;
    Grafo* grafAux;
    if(!direcionado){
        grafAux = this->grafoReverso(); //Não vai fazer diferença, só quero uma cópia do grafo
        aux = grafAux->getNoPorId(1);
    }
    if(ponderado==1){
        while (aux != NULL) {
            Adjacencia *aux2 = aux->getAdjRaiz();
            while (aux2 != NULL) {
                saida << aux->getLabel() << " " << aux2->getNoFim()->getLabel() << " " << aux2->getPeso() << std::endl;
                aux2 = aux2->getProx();
            }
            if(!direcionado){
                int labelLixo = aux->getLabel();
                aux = aux->getProx();
                grafAux->removerNoPorLabel(labelLixo);
            }else
                aux = aux->getProx();
        }
    }else{
        while (aux != NULL) {
            Adjacencia *aux2 = aux->getAdjRaiz();
            while (aux2 != NULL) {
                saida << aux->getLabel() << " " << aux2->getNoFim()->getLabel() << std::endl;
                aux2 = aux2->getProx();
            }
            if(!direcionado){
                int labelLixo = aux->getLabel();
                aux = aux->getProx();
                grafAux->removerNoPorLabel(labelLixo);
            }else
                aux = aux->getProx();
        }
    }
}


//!b

//! Criação de nós
//! Função recebe um id e um dado e adiciona o nó na lista encadeada
// void Grafo::criarNo(int id, int dado)
// {
//     No *no = new No(id, dado);
//     if (noRaiz == NULL) {
//         noRaiz = no;
//         ultimo = no;
//     } else {
//         ultimo->setProx(no);
//         ultimo = no;
//     }
//     ordem++;
// }

//! Função recebe um dado e adiciona o nó na lista encadeada, incrementando o id de acordo com a ordem
void Grafo::criarNo(int label, int dado)
{
    No *no = new No(ordem+1, label, dado);
    if (noRaiz == NULL) {
        noRaiz = no;
        ultimo = no;
    } else {
        ultimo->setProx(no);
        ultimo = no;
    }
    ordem++;
}

//! Remoção de nó
//! Função que recebe uma label e remove o nó correpondente
void Grafo::removerNoPorLabel(int label)
{
    No *aux = noRaiz;
    if(aux == NULL) return;

    No *no = getNoPorLabel(label);
    removerTodasAdj(no);

    if (aux->getLabel() == label) {
        if(aux == ultimo) ultimo = aux->getProx();
        noRaiz = aux->getProx();
        delete aux;
        ordem--;
    } else {
        while (aux->getProx() != NULL && aux->getProx()->getLabel() != label)
            aux = aux->getProx();

        if (aux->getProx() != NULL) {
            if(aux->getProx() == ultimo) ultimo = aux;
            No* lixo = aux->getProx();
            aux->setProx(lixo->getProx());
            delete lixo;
            ordem--;
        }
    }

    reordenaIds();
}


//! Criação de adjacência
//! A função recebe dois ids e um peso para a aresta, e adiciona a adjacência em ambos os nós para o grafo não direcionado, ou apenas no primeiro para o direcionado
bool Grafo::criarAdj(No *noInicio, No *noFim, int peso)
{
    if (noInicio == NULL || noFim == NULL)
        return false;

    noInicio->adicionarAdj(noFim, peso);
    if (!direcionado)
        noFim->adicionarAdj(noInicio, peso);
    else
        noFim->addGrauEntrada(1);

    // std::cout << "Adjac" << char(136) << "ncia " << labelNoInicio << "," << labelNoFim << " n" << char(198) << "o p" << char(147) << "de ser criada!" << std::endl;
    return true;
}


//! Remoção de adjacencia
//! A função recebe dois nós e o peso da aresta, e a remove devidamente do grafo, seja direcionado ou não
void Grafo::removerAdj(No *noInicio, No *noFim, int peso)
{
    if (noInicio != NULL && noFim != NULL)
    {
        noInicio->removerAdj(noFim, peso);
        if (!direcionado)
            noFim->removerAdj(noInicio, peso);
        else
            noFim->addGrauEntrada(-1);
    }
}


//!c

//! Informar grau de nó
//! Função informa o grau de um nó em um grafo não direcionado, ou o grau de saída e entrada de um nó em um digrafo
void Grafo::informaGrauNo(int labelNo)
{
    No *no = getNoPorLabel(labelNo);
    if (no != NULL) {
        if (!direcionado)
            std::cout << "Grau do n" << char(162) << " " << labelNo << ": " << no->getGrau() << std::endl;
        else
            std::cout << "Grau de entrada do n" << char(162) << " " << labelNo << ": " << no->getGrauEntrada() << ", grau de sa" << char(161) << "da: " << no->getGrau() << std::endl;
    } else {
        std::cout << "N" << char(162) << " n" << char(198) << "o encontrado!" << std::endl;
    }
}


//!d

//! Verifica se o grafo é k-regular
//! Percorre a lista encadeada buscando nós com grau diferente de k. Retorna
//! true caso o grafo seja k-regular ou false caso contrário.
bool Grafo::verificaRegularidade(int k)
{
    No *aux = noRaiz;
    while (aux != NULL) {
        if (aux->getGrau() != k)
            return false;
        aux = aux->getProx();
    }
    return true;
}


//!e

//! Informa a ordem do grafo
//! Chama a própria função getOrdem para obter essa informação e a imprime na tela
void Grafo::informaOrdem()
{
    int ordemGrafo = getOrdem();
    std::cout << "Ordem do grafo: " << ordemGrafo << std::endl;
}


//!f

//! Informa se o grafo é trivial
//! Chama as funções do grafo para obter a ordem e o grau,
//! se o grau for igual a 0 e a ordem igual a 1, imprime na tela que é um grafo trivial,
//! imprime que não é caso contrário
void Grafo::informaTrivial()
{
    if (getOrdem() == 1 && calculaGrau() == 0) {
        std::cout << "O grafo " << char(130) << " trivial" << std::endl;
    } else {
        std::cout << "O grafo n" << char(198) << "o " << char(130) << " trivial" << std::endl;
    }
}


//!g

//! Informa se o grafo é nulo
//! Chama as funções do grafo para obter a ordem e o grau,
//! se o grau e a ordem forem iguais a 0, imprime na tela que é um grafo nulo,
//! imprime que não é caso contrário
void Grafo::informaNulo()
{
    if (getOrdem() == 0 && calculaGrau() == 0) {
        std::cout << "O grafo " << char(130) << " nulo" << std::endl;
    } else {
        std::cout << "O grafo n" << char(198) << "o " << char(130) << " nulo" << std::endl;
    }
}
//!Parecido mas com retorno bool
bool Grafo::ehNulo()
{
    if (getOrdem() == 0 && calculaGrau() == 0) {
        return true;
    } else {
        return false;
    }
}


//!h

//! Gera a vizinhanca aberta de um nó
//! Recebe como parametro
Grafo* Grafo::vizinhancaAberta(int label)
{
    No *aux = getNoPorId(label);
    Adjacencia *adj = aux->getAdjRaiz();
    std::vector<int> nos;
    int i = 0;
    while(adj != NULL) {
        i++;
        nos.resize(i);
        nos.push_back(adj->getNoFim()->getId());
        adj = adj->getProx();
    }
    return subInduzido(nos.size(), nos);
}

//!i


//! Gera a vizinhanca fechada de um nó
Grafo* Grafo::vizinhancaFechada(int label)
{
    No *aux = getNoPorId(label);
    Adjacencia *adj = aux->getAdjRaiz();
    std::vector<int> nos;
    int i = 1;
    nos.reserve(i);
    nos.push_back(aux->getId());
    while(adj != NULL) {
        i++;
        nos.resize(i);
        nos.push_back(adj->getNoFim()->getId());
        adj = adj->getProx();
    }
    return subInduzido(nos.size(), nos);
}


//!j

//! Verificar se é multigrafo
//! A função verifica se um grafo é ou não multigrafo.
//! Para fazer isso, passa por todas as arestas de cada nó e confere se elas têm adjacências com o mesmo destino
bool Grafo::verificarMultigrafo()
{
    No *aux = noRaiz;
    while (aux != NULL) {
        if(aux->verificarMultiaresta(getMaiorId()))
            return true;
        aux = aux->getProx();
    }
    return false;
}


//!k

//! Verifica se o grafo é completo
//! Obtém o grau do grafo e usa a função de verificar regularidade
//! para saber se ele é k-1-regular, depois verifica se é simples
bool Grafo::verificarCompleto() {
    int n = getOrdem();
    return verificaRegularidade(n-1) && verificarSimples();
}


//!l

//! Verifica se o grafo é bipartido
//! Função auxiliar realiza busca em profundidade para definir as partições
bool profBipartido(No* no, int* particoes,int parte){
    int id = no->getId();

    if(particoes[id-1]==0) particoes[id-1] = parte;
    else if(particoes[id-1]!=parte) {
        return false;
    }else{
        return true;
    }
    parte = (parte==1)?2:1;

    Adjacencia* aux = no->getAdjRaiz();
    while(aux!=NULL){
        if (profBipartido(aux->getNoFim(),particoes,parte) == false) return false;
        aux = aux->getProx();
    }
    return true;
}

//! Função principal da verificação de existência de bipartição
bool Grafo::verificarBipartido(){
    int * particao = new int[getMaiorId()];
    for(int i = 0;i<getOrdem();i++){
        particao[i] = 0;
    }
    No* aux = noRaiz;
    while(aux!=NULL){
        if(particao[aux->getId() - 1]==0){
            //Em grafos direcionados, um nó começar estar com o valor 0 não significa que ele não é adjacência de nenhum anterior
            //Por isso, preciso testar colocar nele tanto a partição 1 quanto a 2
            int * particao2 = new int[getMaiorId()]; //Preciso de uma cópia para o caso de 1 falhar na partição
            for(int i = 0;i<getMaiorId();i++) particao2[i] = particao[i];

            if(!profBipartido(aux,particao,1)){ //Testo se posso iniciar esse nó na partição 1
                if(!profBipartido(aux,particao2,2)){ //Testo se posso iniciar esse nó na partição 2
                    return false;
                }else{
                    particao = particao2; //se a partição 2 for a correto para o nó, seguimos com este vetor
                }
            }
        }
        aux = aux->getProx();
    }
    return true;
}


//!m

//!Imprime o caminho de dijkstra
void imprimeCaminhoDijkstra(std::vector<int> anterior, int posOrigem,int posDestino)
{
    if (posOrigem == posDestino)

        return;

    imprimeCaminhoDijkstra(anterior,posOrigem, anterior[posDestino]);

    std::cout<<posDestino+1<<" -> ";

}

//! Chama a função menorCaminhoDijkstra e utiliza o resultado para imprimir o menor caminho
//! entre os dois nós e seu custo
void Grafo::imprimeResultadoDijkstra(int idOrigem, int idDestino) {
    std::pair< std::vector<double>, std::vector<int> > vetores = menorCaminhoDijkstra(idOrigem, idDestino);

    std::vector<double> distancias = vetores.first;
    std::vector<int> anterior = vetores.second;

    double distancia = distancias[idDestino - 1];

    if (distancia == std::numeric_limits<double>::infinity()) {
        std::cout << "N" << char(198) << "o existe caminho entre os n" << char(162) << "s de id " << idOrigem << " e " << idDestino << std::endl;
    } else {

        std::cout << "O menor caminho entre os n" << char(162) << "s de id " << idOrigem << " e " << idDestino << " " << char(130) << ": " << idOrigem<<" -> ";
        imprimeCaminhoDijkstra(anterior,idOrigem-1,anterior[idDestino-1]);
        std::cout <<idDestino<< std::endl;
        std::cout << "E o custo desse caminho " << char(130) << ": ";
        std::cout << distancia << std::endl;
    }
}

//!Encontra a menor distancia em "pi" dentre aqueles pertencentes a sBarra
int noMenorDistancia (std::vector<double> *distancias, int n,std::vector<bool> *sBarra) {
    int i, menor = 0;
    for(i=0;i<n;i++){
        if(sBarra->at(i)==true){
            menor = i;
            break;
        }
    }

    for (i = 0; i < n; i++){
        if (distancias->at(i) <= distancias->at(menor) && sBarra->at(i) == true){
            menor = i;
        }
    }
    sBarra->at(menor) = false;

    return menor + 1;
}

//!Confere se sBarra é vazio
bool vazio(std::vector<bool> vetor) {
    for (std::vector<bool>::iterator it = vetor.begin(); it < vetor.end(); it++)
        if(*it==true) return false;
    return true;
}

//! Informa o menor caminho entre dois nós usando o algoritmo de Dijkstra
std::pair< std::vector<double>, std::vector<int> > Grafo::menorCaminhoDijkstra(int idOrigem, int idDestino) {
    int n = getOrdem();

    std::vector<double> distancias (n, std::numeric_limits<double>::infinity());
    std::vector<bool> sBarra(n,true);
    distancias[idOrigem - 1] = 0;
    sBarra[idOrigem - 1] = false;
    No* aux = getNoPorId(idOrigem);

    std::vector< int > anterior(n,0);
    for (int i = 0; i<n;i++)
        anterior[i] = i;

    while(!vazio(sBarra)){

        Adjacencia* adj = aux->getAdjRaiz();
        while (adj != NULL) {
            int posAux = aux->getId() - 1;
            double dist = distancias[posAux];
            double peso = adj->getPeso();
            int posDestino = adj->getNoFim()->getId() - 1;
            if (dist + peso < distancias[posDestino]){
                distancias[posDestino] = dist + peso;
                anterior[posDestino] = posAux;
            }
            adj = adj->getProx();
        }

        int idMenor = noMenorDistancia(&distancias, n,&sBarra);
        aux = getNoPorId(idMenor);

    }

    return std::make_pair(distancias, anterior);
}


//! Retorna o menor caminho entre dois nós a partir da matriz gerada pela função geraMatrizesFloyd
std::vector<int> obtemCaminhoFloyd(int idOrigem, int idDestino, std::vector< std::vector<int> > next) {
    std::vector<int> caminho;
    int u = idOrigem;
    caminho.push_back(u);

    do {
        u = next[u - 1][idDestino - 1];
        caminho.push_back(u);
    } while (u != idDestino);

    return caminho;
}

//! Chama a função geraMatrizesFloyd e utiliza o resultado para imprimir o menor caminho
//! entre os dois nós e seu custo
void Grafo::imprimeResultadoFloyd(int idOrigem, int idDestino) {
    std::pair<std::vector< std::vector<double> >,
    std::vector< std::vector<int> > > matrizes = geraMatrizesFloyd(false);

    std::vector< std::vector<double> > distancias = matrizes.first;
    std::vector< std::vector<int> > next = matrizes.second;

    double distancia = distancias[idOrigem - 1][idDestino - 1];

    if (distancia == std::numeric_limits<double>::infinity()) {
        std::cout << "N" << char(198) << "o existe caminho entre os n" << char(162) << "s de id " << idOrigem << " e " << idDestino << std::endl;
    } else {
        std::vector<int> caminho = obtemCaminhoFloyd(idOrigem, idDestino, next);

        std::cout << "O menor caminho entre os n" << char(162) << "s de id " << idOrigem << " e " << idDestino << " " << char(130) << ": " << caminho.front();

        for (std::vector<int>::iterator it = caminho.begin() + 1; it != caminho.end(); it++)
            std::cout << " -> " << *it;

        std::cout << std::endl;
        std::cout << "E o custo desse caminho " << char(130) << ": ";
        std::cout << distancia << std::endl;
    }
}

//! Utiliza o algoritmo de Floyd para gerar a matriz de distâncias e a que indica os caminhos
std::pair< std::vector< std::vector<double> >,
std::vector< std::vector<int> > > Grafo::geraMatrizesFloyd(bool ponderado) {
    int i, j, k, n = getOrdem();

    std::vector< std::vector<double> > distancias(n, std::vector<double>(n, std::numeric_limits<double>::infinity()));

    No* aux = noRaiz;
    while (aux != NULL) {
        Adjacencia* adj = aux->getAdjRaiz();
        while (adj != NULL) {
            int id1 = adj->getNoInicio()->getId();
            int id2 = adj->getNoFim()->getId();
            distancias[id1 - 1][id2 - 1] = ponderado ? 1 : adj->getPeso();
            adj = adj->getProx();
        }
        aux = aux->getProx();
    }

    std::vector< std::vector<int> > next(n, std::vector<int>(n));
    for (i = 0; i < static_cast<int>(next.size()); i++)
        for (j = 0; j < static_cast<int>(next.size()); j++)
            if (i != j)
                next[i][j] = j + 1;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            for (k = 0; k < n; k++)
                if (distancias[j][k] > distancias[j][i] + distancias[i][k]) {
                        distancias[j][k] = distancias[j][i] + distancias[i][k];
                        next[j][k] = next[j][i];
                }

    return std::make_pair(distancias, next);
}


//!n

//! Calcula o grau do grafo
//! Percorre todos os nós obtendo o grau de cada um e mantendo registro do maior
int Grafo::calculaGrau()
{
    No *aux = noRaiz;
    int maior = 0;
    while (aux != NULL) {
        if (aux->getGrau() > maior)
            maior = aux->getGrau();
        aux = aux->getProx();
    }
    return maior;
}

//!o

//! Encontrar fecho transitivo direto
//! Imprime na tela os ids dos nós pertencentes ao fecho transitivo direto de um nó
std::vector<int> Grafo::fechoTransitivoDireto(int idNo){
    std::vector<int> ftd;
    bool *visitados = new bool[getMaiorId()];
    for(int i=0; i<getMaiorId() ;i++)  visitados[i] = false;
    buscaProfundidade(idNo,visitados);
    for(int i=0;i<getMaiorId();i++){
        if(visitados[i] == true)
            ftd.push_back(i+1);
    }
    return ftd;
}


//!p

//! Encontrar fecho transitivo indireto
//! Imprime na tela os ids dos nós pertencentes ao fecho transitivo direto de um nó
std::vector<int> Grafo::fechoTransitivoIndireto(int idNo){
    std::vector<int> fti;
    No* aux = noRaiz;
    while(aux!=NULL){
        bool *visitados = new bool[getMaiorId()];
        for(int i=0; i<getMaiorId() ;i++)  visitados[i] = false;
        buscaProfundidade(aux->getId(),visitados);
        if(visitados[idNo-1]==true)
            fti.push_back(aux->getId());
        aux = aux->getProx();
    }
    return fti;
}

//!q

//! Imprime na tela a sequência de graus do grafo
//! Percorre a lista encadeada de nós obtendo esses graus e imprimindo
void Grafo::apresentaSequenciaGraus()
{
    int n = getOrdem();
    int i = 0;
    int *sequencia = new int[n];
    No *aux = noRaiz;
    while (aux != NULL) {
        sequencia[i] = aux->getGrau();
        aux = aux->getProx();
        i++;
    }
    ordenaVetor(sequencia, n);
    std::cout << "Sequ" << char(136) << "ncia de graus: ";
    for (i = 0; i < n; i++)
        std::cout << sequencia[i] << " ";
    std::cout << std::endl;
}


//!r
//! Gera o subgrafo Induzido pelos nós informados
Grafo* Grafo::subInduzido(int total, std::vector<int> &n){
    No *aux;
    Grafo *grafo = new Grafo(true, true);
    Adjacencia *adj;
    int noId;
    for (int i = 0; i < total; i++) {
        aux = getNoPorId(n.at(i));
        if (aux != NULL)
            grafo->criarNo(n.at(i), aux->getDado());
    }
    for (int i = 0; i < total; i++) {
        aux = getNoPorId(n.at(i));
        if (aux != NULL)
        {
            adj = aux->getAdjRaiz();
            while (adj != NULL) {
                noId = adj->getNoFim()->getId();
                for (int k = 0; k < total; k++) {
                    if (noId == n.at(k)) {
                        No *noInicio = grafo->getNoPorLabel(n.at(i));
                        No *noFim = grafo->getNoPorLabel(n.at(k));
                        grafo->criarAdj(noInicio, noFim, adj->getPeso());
                        break;
                    }
                }
                adj = adj->getProx();
            }
        }

    }
    return grafo;
}

//!s

//! Obter complementar
//! Função retorna o complementar de um grafo
Grafo* Grafo::obterComplementar(){
    Grafo* comp = new Grafo(direcionado, ponderado);
    int n = getMaiorId();
    for (int i = 1 ; i <= n; i++) {
        if(getNoPorId(i) != NULL)
            comp->criarNo(i, getNoPorId(i)->getDado());
    }
    No* aux = noRaiz;
    while(aux != NULL) {
        for(int i = 1; i <= n; i++) {
            if(!aux->existeAdj(i)) {
                No *noInicio = comp->getNoPorLabel(aux->getId());
                No *noFim = comp->getNoPorLabel(i);
                comp->criarAdj(noInicio, noFim, 0);
            }
        }
        aux = aux->getProx();
    }
    return comp;

}

//!t

//! Componentes Fortemente Conexas
//! Função retorna o numero de componentes, mas também possui a opção de imprimí-las na tela
int Grafo::componentesFortementeConexas(bool imprime){
    int k = 0,n = getOrdem();
    std::vector<int> pilhaNos;

    bool* visitados = new bool[n];
    for(int i = 0;i<n;i++) visitados[i]=false;

    for(int i = 1; i <= n; i++)
    {
        if(visitados[i-1] == false)
            ordenacaoTopologica(i, visitados, pilhaNos);
    }

    Grafo* reverso = grafoReverso();
    for(int i = 0;i<n;i++) visitados[i]=false;
    while(pilhaNos.size()!=0){
        int v = pilhaNos[pilhaNos.size()-1];
        pilhaNos.pop_back();
        if(visitados[v-1]==false){
            if(imprime){
                std::cout<<"Componente "<<k+1<<": ";
                reverso->buscaProfundidadeImprimindo(v,visitados);
                std::cout << std::endl;
            }else
                reverso->buscaProfundidade(v,visitados);
            k++;
        }
    }
    return k;
}

//!u

//! Verificar se é euleriano
//! Função verifica se um grafo ou um digrafo é euleriano. Baseado nos seguintes teoremas:
//! Um digrafo conexo G é euleriano se, se somente se, ele é balanceado, d+(v) = d-(v) para todo v em G
//! Um grafo conexo G é um grafo euleriano se e somente se todo vértice de G possui grau par.
bool Grafo::verificarEuleriano(){
    No * aux = noRaiz;
    if(direcionado){
        if(componentesFortementeConexas(false) == 1){
            while(aux!=NULL){
                if(aux->getGrauEntrada()!=aux->getGrauSaida())
                    return false;
                aux = aux->getProx();
            }
        }else{
            return false;
        }
    }else{
        if(numComponentesConexas() == 1){
            while(aux!=NULL){
                if(aux->getGrau()%2==1)
                    return false;
                aux = aux->getProx();
            }
        }else{
            return false;
        }
    }
    return true;
}


//!v

//! Apresentar os nos de articualção do grafo
std::vector<int> Grafo::nosArticulacao()
{
    int ordem = getOrdem();

    dfs *nos = buscaProfundidade();
    std::vector<int> articulacoes;

    for (int i = 0; i < ordem; ++i) {
        if (nos[i].articulacao)
            articulacoes.push_back(i+1);
    }

    return articulacoes;
}

//!w
//!Encontra as arestas ponte checando a remoção de quais arestas causaria um acréscimo no número de componentes conexas,
//!imprimindo os nós ligados pela aresta assim como seu peso
void Grafo::arestaPonte(){
    No* aux;
    No* fim;
    Adjacencia* adj;
    std::vector<Adjacencia*> adjs;
    int numComponentes = numComponentesConexas();
    aux = noRaiz;
    int peso;
    while(aux!=NULL){
        adj = aux->getAdjRaiz();
        while(adj!=NULL){
            adjs.push_back(adj);
            adj = adj->getProx();
        }
        for(int i=0;i<static_cast<int>(adjs.size());i++){
            fim = adjs.at(i)->getNoFim();
            peso = adjs.at(i)->getPeso();
            aux->removerAdj(fim, peso);
            if(numComponentesConexas()> numComponentes)
            {
                std::cout << "ID1: "<<aux->getId() << "\tID2: "<<fim->getId() << "\tPeso: " << peso << std::endl;
            }
            criarAdj(aux, fim, peso);
        }
        aux = aux->getProx();
        adjs.erase(adjs.begin(), adjs.end());
    }
}

//!x

//! Apresentar raio, diâmetro, centro e periferia do grafo
void Grafo::imprimeRaioDiaCentPerif() {
    int i, j, n = getOrdem();

    std::pair< std::vector< std::vector<double> >,
    std::vector< std::vector<int> > > matrizes = geraMatrizesFloyd(false);

    std::vector< std::vector<double> > distancias = matrizes.first;
    std::vector< std::vector<int> > next = matrizes.second;

    std::vector<int> tamanhosCaminhos;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (i != j) {
                int tamanho = 0;
                if (distancias[i - 1][j - 1] != std::numeric_limits<double>::infinity())
                    tamanho = static_cast<int>(obtemCaminhoFloyd(i, j, next).size()) - 1;
                tamanhosCaminhos.push_back(tamanho);
            }


    std::vector<int> excentricidades;

    for (i = 0; i < n; i++) {
        int excentricidade = 0;
        for (j = 0; j < n - 1; j++)
            if (tamanhosCaminhos[(n - 1) * i + j] > excentricidade)
                excentricidade = tamanhosCaminhos[(n - 1) * i + j];
        excentricidades.push_back(excentricidade);
    }

    int raio = n, diametro = 0;

    for (std::vector<int>::iterator it = excentricidades.begin(); it != excentricidades.end(); it++) {
        if (*it < raio && *it != 0)
            raio = *it;
        if (*it > diametro)
            diametro = *it;
    }

    std::vector<int> nosPerifericos;
    std::vector<int> nosCentrais;

    for (i = 0; i < n; i++) {
        if (excentricidades[i] == diametro)
            nosPerifericos.push_back(i + 1);
        if (excentricidades[i] == raio)
            nosCentrais.push_back(i + 1);
    }

    std::cout << "Raio: " << raio << std::endl;
    std::cout << "Di" << char(131) << "metro: " << diametro << std::endl;

    std::cout << "Centro: " << std::endl;
    std::cout << "Id: " << nosCentrais.front() << std::endl;
    for (std::vector<int>::iterator it = nosCentrais.begin() + 1; it != nosCentrais.end(); it++)
        std::cout << ", Id: " << *it << std::endl;

    std::cout << "Periferia: " << std::endl;
    std::cout << "Id: " << nosPerifericos.front() << std::endl;
    for (std::vector<int>::iterator it = nosPerifericos.begin() + 1; it != nosPerifericos.end(); it++)
        std::cout << ", Id: " << *it << std::endl;
}

//!y

//! Gera a Arvore Geradora Minima pelo algoritmo de Prim

Grafo* Grafo::AGM(){
    std::vector<No*> visitados, restantes;
    Grafo *subjacente = this->obterSubjacente();
    No *aux = subjacente->noRaiz;
    Adjacencia *adj;
    Grafo *arvore = new Grafo(true, true);
    int minimo, noIniLabel, noDestLabel, noDestDado, noDestIndex;
    while (aux != NULL) {
        restantes.push_back(aux);
        aux = aux->getProx();
    }
    aux = restantes.at(0);
    arvore->criarNo(aux->getId(), aux->getDado());
    visitados.push_back(restantes.at(0));
    restantes.erase(restantes.begin());
    while (restantes.size() > 0) {
        minimo = 9999;
        for (int i = 0; i < static_cast<int>(visitados.size()); i++) {
            aux = visitados.at(i);
            adj = aux->getAdjRaiz();
            while (adj != NULL) {
                for (int j = 0; j < static_cast<int>(restantes.size()); j++) {
                    if (adj->getNoFim() == restantes.at(j)) {
                        if (adj->getPeso() < minimo) {
                            minimo = adj->getPeso();
                            noIniLabel = visitados.at(i)->getLabel();
                            noDestLabel = restantes.at(j)->getLabel();
                            noDestDado = restantes.at(j)->getDado();
                            noDestIndex = j;
                        }
                    }
                }
                adj = adj->getProx();
            }
        }
        if(minimo != 9999) {
            arvore->criarNo(noDestLabel, noDestDado);

            No *noInicio = arvore->getNoPorLabel(noIniLabel);
            No *noFim = arvore->getNoPorLabel(noDestLabel);
            arvore->criarAdj(noInicio, noFim, minimo);

            visitados.push_back(restantes.at(noDestIndex));
            restantes.erase(restantes.begin()+noDestIndex);
        } else {
            arvore->criarNo(restantes.at(0)->getId(), restantes.at(0)->getDado());
            visitados.push_back(restantes.at(0));
            restantes.erase(restantes.begin());
        }
    }
    return arvore;
}

//!z

//! Realiza uma busca em profundidade e retorna uma lista contendo informações da arvore gerada pela busca
dfs* Grafo::buscaProfundidade()
{
    if(direcionado)
        return obterSubjacente()->buscaProfundidade();

    int ordem = getOrdem();
    int tempo = 0;

    bool *visitados = new bool[ordem];
    dfs *nos = new dfs[ordem];

    for (int i = 0; i < ordem; ++i) {
        visitados[i] = false;
        nos[i].label = 0;
        nos[i].pai = 0;
        nos[i].descoberto = 0;
        nos[i].menor = 0;
        nos[i].articulacao = false;
    }

    for (int i = 0; i < ordem; ++i) {
        if (!visitados[i])
            buscaProfundidade(i+1, visitados, nos, &tempo);
    }

    delete visitados;

    return nos;
}

//!Gulosos
//!Note que a struct está definida em Grafo.h

//!Algoritmo guloso para a resolução do problema de atribuição de frequências.
//!Prepara o grafo definindo frequência -1 para todos os nós, obtém o subjacente
//!para desconsiderar a direção dos arcos e transformá-los em arestas e executa
//!o fluxo básico de um algoritmo guloso (lista de candidatos, função critério
//!e atualização da lista de candidatos).
void Grafo::gulosoFrequencias(){
    resetaFrequencias();
    Grafo *subjacente = obterSubjacente(); //Para fazer o algoritmo sem considerar direções
    std::vector<structNo> LC = subjacente->retornaNos(); //Retorna um vector da estrutura definida em Grafo.h
    while(!LC.empty()){
        std::sort(LC.begin(),LC.end()); //Usa o operador definido (na struct) para ordenar na ordem crescente por grau
        std::reverse(LC.begin(), LC.end()); //Inverte a ordem

        defineFrequencia(LC.at(0).label,subjacente);
        subjacente->atualizaLC(LC,0); //remove o primeiro elemento e atualiza o grau dos adjacentes
    }
}

//!Algoritmo guloso randomizado para a resolução do problema de atribuição de frequências.
//!Obtém o subjacente do grafo para desconsiderar a direção dos arcos e transformá-los em
//!arestas, o prepara definindo frequência 1 para todos os nós e executa
//!o fluxo básico de um algoritmo guloso randomizado(lista de candidatos, função critério,
//!seleção aleatória baseada no alfa de um elemento da lista de candidatos
//!e atualização da lista de candidatos).
int Grafo::gulosoRandomizadoFrequencias(int numeroIteracoes, float alpha)
{
    Grafo *subjacente = obterSubjacente(); //Para fazer o algoritmo sem considerar direções
    int melhor = INFINITY;

    for (int i = 0; i < numeroIteracoes; ++i) {
        resetaFrequencias();
        std::vector<structNo> LC = subjacente->retornaNos(); //Retorna um vector da estrutura definida em Grafo.h
        while(!LC.empty()) {
            std::sort(LC.begin(),LC.end()); //Usa o operador definido (na struct) para ordenar na ordem crescente por grau
            std::reverse(LC.begin(), LC.end()); //Inverte a ordem

            int tamanho = round((LC.size() - 1) * alpha + 1);
            int indice = round(rand() % tamanho);

            defineFrequencia(LC.at(indice).label,subjacente);
            subjacente->atualizaLC(LC,indice); //remove o elemento da posicao indice e atualiza o grau dos adjacentes
        }

        int interferencia = calculaInterferenciaTotal();
        if (interferencia < melhor)
            melhor = interferencia;
    }

    return melhor;
}

//!Algoritmo guloso randomizado reativo para a resolução do problema de atribuição de frequências.
//!Obtém o subjacente do grafo para desconsiderar a direção dos arcos e transformá-los em
//!arestas, inicia o conjunto de probabilidades de acordo com o parâmetro numAlpha e distribui
//!igualmente valores de 0 a 1 para cada alpha, prepara o grafo definindo frequência 1 para
//!todos os nós e executa
//!o fluxo básico de um algoritmo guloso randomizado reativo(seleção de um alpha baseado na
//!probabilidade definida para cada um, lista de candidatos, função critério,
//!seleção aleatória baseada no alfa de um elemento da lista de candidatos
//!e atualização da lista de candidatos).
int Grafo::gulosoRandomizadoReativoFrequencias(int numeroIteracoes, int blocoInteracoes, int numAlpha)
{
    Grafo *subjacente = obterSubjacente(); //Para fazer o algoritmo sem considerar direções

    int melhor = INFINITY;

    float probAlpha[numAlpha];
    int usoAlpha[numAlpha];
    int resultadoAlpha[numAlpha];
    for (int i = 0; i < numAlpha; ++i) {
        probAlpha[i] = 1.0f / (float)numAlpha;
        usoAlpha[i] = 0;
        resultadoAlpha[i] = 0;
    }

    for (int i = 0; i < numeroIteracoes; ++i) {
        resetaFrequencias();
        // Sorteia alpha
        int alphaSelecionado = 0;
        float alphaAleatorio = (float)rand() / (float)RAND_MAX;
        for (int j = 0; j < numAlpha; ++j) {
            if (probAlpha[j] > alphaAleatorio) {
                alphaSelecionado = j;
                break;
            }
            alphaAleatorio -= probAlpha[j];
        }
        float alpha = (float)alphaSelecionado / (float)numAlpha;

        std::vector<structNo> LC = subjacente->retornaNos(); //Retorna um vector da estrutura definida em Grafo.h
        while(!LC.empty()) {
            std::sort(LC.begin(),LC.end()); //Usa o operador definido (na struct) para ordenar na ordem crescente por grau
            std::reverse(LC.begin(), LC.end()); //Inverte a ordem

            int tamanho = round((LC.size() - 1) * alpha + 1);
            int indice = round(rand() % tamanho);

            defineFrequencia(LC.at(indice).label,subjacente);
            subjacente->atualizaLC(LC,indice);
        }

        int interferencia = calculaInterferenciaTotal();
        usoAlpha[alphaSelecionado] += 1;
        resultadoAlpha[alphaSelecionado] += interferencia;

        if (interferencia < melhor)
            melhor = interferencia;

        if ((i + 1) % blocoInteracoes == 0) {
            // Atualiza alphas
            float q[numAlpha];
            float qTotal = 0;
            for (int j = 0; j < numAlpha; ++j) {
                if (usoAlpha[j] > 0)
                    q[j] = (float)melhor / ((float)resultadoAlpha[j] / (float)usoAlpha[j]);
                else
                    q[j] = 1.0f;

                qTotal += q[j];
            }
            for (int j = 0; j < numAlpha; ++j) {
                probAlpha[j] = q[j] / qTotal;
            }
        }
    }

    return melhor;
}

//Auxiliares para os gulosos:

//!Função que atualiza a lista de candidados removendo o nó recebido (atual),
//!percorrendo todos os nós adjacentes ao nó recebido e decrementando seus graus.
void Grafo::atualizaLC(std::vector<structNo> &LC,int i)
{
    No *no = getNoPorLabel(LC.at(i).label);
    LC.erase(LC.begin()+i);
    for(int j= 0;j<LC.size();j++){
        int label = LC.at(j).label;
        No* no2 = getNoPorLabel(label);
        if(no2->existeAdj(no->getId())){
            LC.at(j).grau--;
        }
    }
}

//!Função que calcula a interferência total entre a frequência recebida e a quantidade
//!de frequências de cada banda presente em nós adjacentes ao que está sendo analisado.
float Grafo::calcularInterferencia(int freq, int frequencias[14]){
    float soma = 0;
    for(int i = 0;i<NUM_FREQ;i++){
        soma += interferencias[freq-1][i] * frequencias[i];
    }
    return soma;
}

//!Função que busca a melhor frequência que pode ser atribuída ao nó recebido, ou seja, aquela que
//!minimiza a interferência total com seus adjacentes que já receberem uma frequência, ou seja, os
//!que tem frequência diferente de -1. Isso é feito calculando a interferência total com cada uma
//!das bandas de frequência e escolhendo a que gerou menor interferência.
void Grafo::defineFrequencia(int label, Grafo* subjacente){
    //Obtem No:
    No* noReal;
    if(direcionado) //subjacente != grafo
        noReal = getNoPorLabel(label);
    No* no = subjacente->getNoPorLabel(label);

    //Calcula frequencia:
    Adjacencia* aux = no->getAdjRaiz();
    int freq;

    int frequencias[NUM_FREQ];
    for(int i = 0;i<NUM_FREQ;i++) frequencias[i] = 0;

    while(aux!=NULL){
        int freqAdj = aux->getNoFim()->getFrequencia();
        if(freqAdj!=-1){
            frequencias[freqAdj-1]+=1;
        }
        aux= aux->getProx();
    }

    freq =-1;
    float menorFreq=INFINITY;
    for(int i = 0;i<NUM_FREQ;i++){
        float atual = calcularInterferencia(i+1,frequencias);
        if(atual == 0){
            freq = i+1;
            break;
        }
        if(atual<menorFreq){
            freq = i+1;
            menorFreq = atual;
        }
    }

    //Defina frequencia:
    no->setFrequencia(freq);
    if(direcionado)
        noReal->setFrequencia(freq);
}

//!Função que cria a lista de candidatos pegando os nós do grafo e colocando
//!duas informações em um structNo criado e inserido na lista de candidatos.
std::vector<structNo> Grafo::retornaNos()
{
    std::vector<structNo> LC;
    No* aux = noRaiz;
    while(aux!=NULL){
        structNo no;
        no.grau = aux->getGrau();
        no.id = aux->getId();
        no.label = aux->getLabel();
        LC.push_back(no);
        aux = aux->getProx();
    }
    return LC;

}

//!Função que calcula a interferência total do grafo baseado nas frequências
//!atribuídas pelos algoritmos.
int Grafo::calculaInterferenciaTotal()
{
    int interferencia = 0;

    No* no = noRaiz;
    while(no!=NULL){
        Adjacencia* adj = no->getAdjRaiz();
        while(adj!=NULL){
            interferencia += interferencias[adj->getNoInicio()->getFrequencia()-1]
                                           [adj->getNoFim()->getFrequencia()-1];

            adj = adj->getProx();
        }
        no = no->getProx();
    }

    // A adjacencia entre dois nó e contada duas vezes  (uma ida e uma volta) no
    // grafo. Por isso a interferencia total precisa ser dividida por dois
    return interferencia / 2;
}

//!Define a frequência de todos os nós do grafo como -1.
void Grafo::resetaFrequencias()
{
    No* no = noRaiz;
    while(no!=NULL){
        no->setFrequencia(-1);
        no = no->getProx();
    }
}





//! Metódo auxilar para a recursão da busca em profundidade
void Grafo::buscaProfundidade(int id, bool *visitados, dfs *nos, int *tempo)
{
    No *no = getNoPorId(id);

    nos[id-1].label = no->getLabel();
    nos[id-1].descoberto = nos[id-1].menor = ++(*tempo);
    visitados[id-1] = true;
    int numFilhos = 0;

    Adjacencia* aux = no->getAdjRaiz();
    while (aux != NULL) {
        int idAux = aux->getNoFim()->getId();

        if (!visitados[idAux-1]) {
            nos[idAux-1].pai = nos[id-1].label;
            buscaProfundidade(idAux, visitados, nos, tempo);

            numFilhos++;
            nos[id-1].menor = std::min(nos[id-1].menor, nos[idAux-1].menor);

            if (nos[id-1].pai == 0 && numFilhos > 1)
                nos[id-1].articulacao = true;

            if (nos[id-1].pai != 0 && nos[idAux-1].menor >= nos[id-1].descoberto)
                nos[id-1].articulacao = true;
        } else if (nos[idAux-1].label != nos[id-1].pai) {
            nos[id-1].menor = std::min(nos[id-1].menor, nos[idAux-1].descoberto);
        }

        aux = aux->getProx();
    }
}

//! Realiza uma busca em largura e retorna uma lista contendo informações da arvore gerada pela busca
bfs* Grafo::buscaLargura()
{
    if(direcionado)
        return obterSubjacente()->buscaLargura();

    int ordem = getOrdem();
    int tempo = 0;

    bool *visitados = new bool[ordem];
    std::queue<int> fila;
    bfs *nos = new bfs[ordem];

    for (int i = 0; i < ordem; ++i) {
        visitados[i] = false;
        nos[i].label = 0;
        nos[i].pai = 0;
        nos[i].descoberto = 0;
        nos[i].distancia = 0;
    }

    for (int i = 0; i < ordem; ++i) {
        if (!visitados[i]) {
            visitados[i] = true;
            fila.push(i+1);
        }

        while (!fila.empty()) {
            int id = fila.front();
            fila.pop();

            No *no = getNoPorId(id);
            nos[id-1].label = no->getLabel();
            nos[id-1].descoberto = ++tempo;

            Adjacencia* aux = no->getAdjRaiz();
            while (aux != NULL) {
                int idAux = aux->getNoFim()->getId();

                if (!visitados[idAux-1]) {
                    nos[idAux-1].pai = nos[id-1].label;
                    nos[idAux-1].distancia = nos[id-1].distancia + 1;
                    visitados[idAux-1] = true;
                    fila.push(idAux);
                }

                aux = aux->getProx();
            }
        }
    }

    return nos;
}


//! Auxiliares

//!Remove os nós de um grafo, auxiliar para a releitura de arquivos
void Grafo::limparNos(){
    while(noRaiz!=NULL){
        removerNoPorLabel(noRaiz->getLabel());
    }
}

//!Preenche o vetor pilha na ordem que os nós "morrem" na busca em profundidade
void Grafo::ordenacaoTopologica(int v, bool visitados[], std::vector<int>& pilha)
{
    // marca o vértice atual como visitado
    visitados[v-1] = true;

    Adjacencia* aux = getNoPorId(v)->getAdjRaiz();
    while(aux!=NULL){
        int destId = aux->getNoFim()->getId();
        if(visitados[destId-1] == false){
            ordenacaoTopologica(destId,visitados,pilha);
        }
        aux = aux->getProx();

    }
    pilha.push_back(v);
}

//!Realiza uma busca em profundidade imprimindo cada nó visitado
void Grafo::buscaProfundidadeImprimindo(int v, bool visitados[])
{
    // marca o vértice atual como visitado
    visitados[v-1] = true;

    // imprime o vértice
    std::cout<< std::endl<<"   | Id: "<<v<<", Dado: "<<getNoPorId(v)->getDado();

    // percorre os adjacentes de v
    Adjacencia* aux = getNoPorId(v)->getAdjRaiz();
    while(aux!=NULL){
        int destId = aux->getNoFim()->getId();
        if(visitados[destId-1] == false){
            buscaProfundidadeImprimindo(destId,visitados);
        }
        aux = aux->getProx();

    }
}

void Grafo::reordenaIds() {
    No* aux = noRaiz;
    int i = 1;
    while (aux != NULL) {
        aux->setId(i);
        i++;
        aux = aux->getProx();
    }
}


//! Função para obter subjacente do grafo
Grafo* Grafo::obterSubjacente(){
    if(!direcionado) return this;
    Grafo* subjacente = new Grafo(false, true);
    int n = getMaiorId();
    for (int i = 1; i <= n; i++) {
        if (getNoPorId(i) != NULL)
            subjacente->criarNo(getNoPorId(i)->getLabel(), getNoPorId(i)->getDado());
    }
    No* aux = noRaiz;
    while(aux!=NULL){
        Adjacencia* aux2 = aux->getAdjRaiz();
        while(aux2!=NULL){
            No *noInicio = subjacente->getNoPorLabel(aux->getLabel());
            No *noFim = subjacente->getNoPorLabel(aux2->getNoFim()->getLabel());
            subjacente->criarAdj(noInicio, noFim, aux2->getPeso());
            aux2 = aux2->getProx();
        }
        aux = aux->getProx();
    }
    return subjacente;

}

Grafo* Grafo::grafoReverso(){
    Grafo* reverso = new Grafo(true, true);
    int n = getOrdem();
    for (int i = 1; i <= n; i++) {
        if (getNoPorId(i) != NULL)
            reverso->criarNo(i, getNoPorId(i)->getDado());
    }
    No* aux = noRaiz;
    while(aux != NULL) {
        Adjacencia* aux2 = aux->getAdjRaiz();
        while(aux2 != NULL) {
            No *noInicio = reverso->getNoPorLabel(aux2->getNoFim()->getId());
            No *noFim = reverso->getNoPorLabel(aux->getId());
            reverso->criarAdj(noInicio, noFim, aux2->getPeso());
            aux2 = aux2->getProx();
        }
        aux = aux->getProx();
    }
    return reverso;

}


//! Função para contar o número de componentes conexas
//! Só funciona para grafos não direcionados
int Grafo::numComponentesConexas(){
    if(direcionado)
        return obterSubjacente()->numComponentesConexas();
    bool * visitados = new bool[getMaiorId()];
    int numComp= 0;
    for(int i = 0;i<getMaiorId();i++){
        visitados[i] = false;
    }
    No* aux = noRaiz;
    while(aux!=NULL){
        if(visitados[aux->getId() - 1]==false){
            numComp++;
            buscaProfundidade(aux->getId(),visitados);
        }
        aux = aux->getProx();
    }
    return numComp;
}


//! Função de busca em profundidade. Marca os elementos visitados com True
void Grafo::buscaProfundidade(int id, bool* visitados){
    if(visitados[id - 1] != true){
        visitados[id - 1] = true;
    }else{
        return;
    }
    Adjacencia* aux = getNoPorId(id)->getAdjRaiz();
    while(aux!=NULL){
        buscaProfundidade(aux->getNoFim()->getId(),visitados);
        aux = aux->getProx();
    }
}


//!Apesar do maior Id na maioria das vezes ser a ordem do nó, essa função vai evitar problemas caso o grafo tenha sofrido alguma remoção que diminua a ordem
int Grafo::getMaiorId(){
    int maior = 0;
    No* aux = noRaiz;
    while(aux!=NULL){
        if(aux->getId()>maior)
            maior = aux->getId();
        aux = aux->getProx();
    }
    return maior;

}


//! Função que remove todas as adjacências de um determinado nó. Complementa a remoção do nó.
void Grafo::removerTodasAdj(No *remover)
{
    if (remover == NULL) return;

    No* aux = noRaiz;
    while (aux != NULL) {
        aux->removerAdjs(remover);
        aux = aux->getProx();
    }
}


//! Impressão do Grafo
//! Imprime o grafo na tela no modelo:
//! No
//! |-adjacente, peso

void Grafo::imprimeGrafo()
{
    No *aux = noRaiz;
    while (aux != NULL) {
        std::cout << "Id " << aux->getId() << ", Label " << aux->getLabel() << ", Dado " << aux->getDado() <<", Frequencia: "<<aux->getFrequencia()<< std::endl;
        Adjacencia* aux2 = aux->getAdjRaiz();
        while(aux2!=NULL){
            std::cout<<"  |- Destino: " <<aux2->getNoFim()->getLabel()<<", Peso: "<<aux2->getPeso()<<std::endl;
            aux2 = aux2->getProx();
        }
        aux = aux->getProx();
    }
}

void Grafo::imprimeInterferencias()
{
    for(int i = 0;i<NUM_FREQ;i++){
        for(int j =0; j<NUM_FREQ;j++){
            std::cout<<interferencias[i][j]<<" \t";
        }
        std::cout<<std::endl;
    }
}

//! InsertionSort
void Grafo::ordenaVetor(int *vet, int n)
{
    int i, j, aux;

    for (i = 1; i < n; i++) {
        aux = vet[i];
        for (j = i - 1; j >= 0 && vet[j] > aux; j--)
            vet[j+1] = vet[j];
        vet[j+1] = aux;
    }
}


//! Verifica se o grafo é simples
//! Chama as funções do grafo para saber se ele é multigrafo ou tem selfloop
bool Grafo::verificarSimples() {
    return !verificarMultigrafo() && !verificarSelfLoop();
}


//! Verifica se o grafo tem selfloop
//! Percorre todos os nós chamando a função deles que verifica
//! se tem alguma adjacência que aponta para o próprio nó
bool Grafo::verificarSelfLoop() {
    No *aux = noRaiz;
    while (aux != NULL) {
        if(aux->verificarSelfLoop())
            return true;
        aux = aux->getProx();
    }
    return false;
}


//! Obter Nó
//! A função recebe um id e retorna um ponteiro para o nó correspondente.
No* auxGetNoPorId(No* no, int id)
{
    if(no == NULL) return NULL;

    if (no->getId() == id) return no;
    else return auxGetNoPorId(no->getProx(), id);
}

No* Grafo::getNoPorId(int id)
{
    return auxGetNoPorId(noRaiz, id);
}

//! Obter Nó
//! A função recebe uma label e retorna um ponteiro para o nó correspondente.
No* auxGetNoPorLabel(No* no, int label)
{
    if(no == NULL) return NULL;

    if (no->getLabel() == label) return no;
    else return auxGetNoPorLabel(no->getProx(), label);
}

No* Grafo::getNoPorLabel(int label)
{
    return auxGetNoPorLabel(noRaiz, label);
}

//! Gets e seters

int Grafo::getOrdem(){
    return ordem;
}
