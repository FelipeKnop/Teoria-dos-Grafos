#include "Grafo.h"

Grafo::Grafo(bool direcionado)
{
    noRaiz = NULL;
    ordem = 0;
    this->direcionado = direcionado;
}

Grafo::~Grafo()
{
}

//!a

//! Ler um arquivo
//! Função que lê o grafo de um arquivo
bool Grafo::lerArquivo(const char *caminho)
{
    std::ifstream file(caminho);

    if (!file) {
        return false;
    }

    int ordem, noInicio, noFim, peso;
    file >> ordem;

    for (int i = 1; i <= ordem; i++)
        criarNo(i, i * 100);

    while (file >> noInicio >> noFim >> peso)
        criarAdj(noInicio, noFim, peso);

    return true;
}


//! Salvar um arquivo
//! Função que imprime o grafo em um arquivo
void Grafo::salvarArquivo(const char *caminho)
{
    std::ofstream saida(caminho);
    saida << ordem << std::endl;

    No *aux = noRaiz;
    while (aux != NULL) {
        Adjacencia *aux2 = aux->getAdjRaiz();
        while (aux2 != NULL) {
            saida << aux->getId() << " " << aux2->getNoFim()->getId() << " " << aux2->getPeso() << std::endl;
            aux2 = aux2->getProx();
        }
        aux = aux->getProx();
    }
}


//!b

//! Criação de nós
//! Função recebe um id e um dado e adiciona o nó na lista encadeada
void Grafo::criarNo(int id, int dado)
{
    No *no = new No(id, dado);
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
//! Função que recebe um id e remove o nó correpondente
void Grafo::removerNo(int id)
{
    No *aux = noRaiz;
    if(aux == NULL) return;

    removerTodasAdj(id);

    if (aux->getId() == id) {
        noRaiz = aux->getProx();
        delete aux;
        ordem--;
    } else {
        while (aux->getProx() != NULL && aux->getProx()->getId() != id)
            aux = aux->getProx();

        if (aux->getProx() != NULL) {
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
bool Grafo::criarAdj(int idNoInicio, int idNoFim, int peso)
{
    No *no1 = getNo(idNoInicio), *no2 = getNo(idNoFim);

    if (no1 == NULL || no2 == NULL)
        return false;

    no1->adicionarAdj(no2, peso);
    if (!direcionado)
        no2->adicionarAdj(no1, peso);
    else
        no2->addGrauEntrada(1);

    // std::cout << "Adjac" << char(136) << "ncia " << idNoInicio << "," << idNoFim << " n" << char(198) << "o p" << char(147) << "de ser criada!" << std::endl;
    return true;
}


//! Remoção de adjacencia
//! A função recebe dois nós e o peso da aresta, e a remove devidamente do grafo, seja direcionado ou não
void Grafo::removerAdj(int idNo1, int idNo2, int peso)
{
    No *no1 = getNo(idNo1), *no2 = getNo(idNo2);
    if (no1 != NULL && no2 != NULL)
    {
        no1->removerAdj(no2, peso);
        if (!direcionado)
            no2->removerAdj(no1, peso);
        else
            no2->addGrauEntrada(-1);
    }
}


//!c

//! Informar grau de nó
//! Função informa o grau de um nó em um grafo não direcionado, ou o grau de saída e entrada de um nó em um digrafo
void Grafo::informaGrauNo(int idNo)
{
    No *no = getNo(idNo);
    if (no != NULL) {
        if (!direcionado)
            std::cout << "Grau do n" << char(162) << " " << idNo << ": " << no->getGrau() << std::endl;
        else
            std::cout << "Grau de entrada do n" << char(162) << " " << idNo << ": " << no->getGrauEntrada() << ", grau de sa" << char(161) << "da: " << no->getGrau() << std::endl;
    } else {
        std::cout << "N" << char(162) << " n" << char(198) << "o encontrado!" << std::endl;
    }
}


//!d

//! Verifica se o grafo é k-regular
//! Percorre a lista encadeada buscando nós com grau diferente de k
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


//!h

//! Gera a vizinhanca aberta de um nó
Grafo* Grafo::vizinhancaAberta(int id)
{
    No *aux = getNo(id);
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
Grafo* Grafo::vizinhancaFechada(int id)
{
    No *aux = getNo(id);
    Adjacencia *adj = aux->getAdjRaiz();
    std::vector<int> nos;
    int i = 1;
    nos.reserve(i);
    nos.push_back(id);
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
    No* aux = getNo(idOrigem);

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
        aux = getNo(idMenor);

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
    std::vector< std::vector<int> > > matrizes = geraMatrizesFloyd();

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
std::vector< std::vector<int> > > Grafo::geraMatrizesFloyd() {
    int i, j, k, n = getOrdem();

    std::vector< std::vector<double> > distancias(n, std::vector<double>(n, std::numeric_limits<double>::infinity()));

    No* aux = noRaiz;
    while (aux != NULL) {
        Adjacencia* adj = aux->getAdjRaiz();
        while (adj != NULL) {
            int id1 = adj->getNoInicio()->getId();
            int id2 = adj->getNoFim()->getId();
            distancias[id1 - 1][id2 - 1] = adj->getPeso();
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
    Grafo *grafo = new Grafo(true);
    Adjacencia *adj;
    int noId;
    for (int i = 0; i < total; i++) {
        aux = getNo(n.at(i));
        if (aux != NULL)
            grafo->criarNo(n.at(i), aux->getDado());
    }
    for (int i = 0; i < total; i++) {
        aux = getNo(n.at(i));
        if (aux != NULL)
        {
            adj = aux->getAdjRaiz();
            while (adj != NULL) {
                noId = adj->getNoFim()->getId();
                for (int k = 0; k < total; k++) {
                    if (noId == n.at(k)) {
                        grafo->criarAdj(n.at(i), n.at(k), adj->getPeso());
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
    Grafo* comp = new Grafo(direcionado);
    int n = getMaiorId();
    for(int i=1;i<=n;i++){
        if(getNo(i)!=NULL)
            comp->criarNo(i,getNo(i)->getDado());
    }
    No* aux = noRaiz;
    while(aux!=NULL){
        for(int i = 1;i<=n;i++){
            if(!aux->existeAdj(i))
                comp->criarAdj(aux->getId(),i,0);
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


//v
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


//!x

//! Apresentar raio, diâmetro, centro e periferia do grafo
void Grafo::imprimeRaioDiaCentPerif() {
    int i, j, n = getOrdem();

    std::pair< std::vector< std::vector<double> >,
    std::vector< std::vector<int> > > matrizes = geraMatrizesFloyd();

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
    Grafo* sub1 = subInduzido(static_cast<int>(nosCentrais.size()), nosCentrais);
    sub1->imprimeGrafo();
    std::cout << "Periferia: " << std::endl;
    Grafo* sub2 = subInduzido(static_cast<int>(nosPerifericos.size()), nosPerifericos);
    sub2->imprimeGrafo();
}

//!y

//! Gera a Arvore Geradora Minima pelo algoritmo de Prim

Grafo* Grafo::AGM(){
    std::vector<No*> visitados, restantes;
    No* aux = noRaiz;
    Adjacencia* adj;
    Grafo* arvore = new Grafo(true);
    int minimo, noIniId, noDestId, noDestDado, noDestIndex;
    while(aux!=NULL){
        restantes.push_back(aux);
        aux = aux->getProx();
    }
    aux = restantes.at(0);
    arvore->criarNo(aux->getId(), aux->getDado());
    visitados.push_back(restantes.at(0));
    restantes.erase(restantes.begin());
    while(restantes.size()>0){
        minimo = 9999;
        for(int i = 0;i<visitados.size();i++){
            aux = visitados.at(i);
            adj = aux->getAdjRaiz();
            while(adj!=NULL){
                for(int j=0;j<restantes.size();j++){
                    if(adj->getNoFim()==restantes.at(j)){
                        if(adj->getPeso()<minimo){
                            minimo = adj->getPeso();
                            noIniId = visitados.at(i)->getId();
                            noDestId = restantes.at(j)->getId();
                            noDestDado = restantes.at(j)->getDado();
                            noDestIndex = j;
                        }
                    }
                }
                adj = adj->getProx();
            }
        }
        arvore->criarNo(noDestId, noDestDado);
        arvore->criarAdj(noIniId, noDestId, minimo);
        visitados.push_back(restantes.at(noDestIndex));
        restantes.erase(restantes.begin()+noDestIndex);
    }
    return arvore;
}

//z
dfs* Grafo::buscaProfundidade()
{
    int ordem = getOrdem();
    int tempo = 0;

    bool *visitados = new bool[ordem];
    dfs *nos = new dfs[ordem];

    for (int id = 1; id <= ordem; ++id) {
        visitados[id-1] = false;
        nos[id-1].pai = 0;
        nos[id-1].descoberto = 0;
        nos[id-1].menor = 0;
        nos[id-1].articulacao = false;
    }


    for (int id = 1; id <= ordem; ++id) {
        if (!visitados[id-1])
            buscaProfundidade(id, visitados, nos, &tempo);
    }

    return nos;
}

void Grafo::buscaProfundidade(int id, bool *visitados, dfs *nos, int *tempo)
{
    nos[id-1].descoberto = nos[id-1].menor = ++(*tempo);
    visitados[id-1] = true;
    int numFilhos = 0;

    Adjacencia* aux = getNo(id)->getAdjRaiz();
    while (aux != NULL) {
        int idAux = aux->getNoFim()->getId();

        if (!visitados[idAux-1]) {
            nos[idAux-1].pai = id;
            buscaProfundidade(idAux, visitados, nos, tempo);

            numFilhos++;
            nos[id-1].menor = std::min(nos[id-1].menor, nos[idAux-1].menor);

            if (nos[id-1].pai == 0 && numFilhos > 1)
                nos[id-1].articulacao = true;

            if (nos[id-1].pai != 0 && nos[idAux-1].menor >= nos[id-1].descoberto) {
                nos[id-1].articulacao = true;
            }
        } else if (idAux != nos[id-1].pai) {
            nos[id-1].menor = std::min(nos[id-1].menor, nos[idAux-1].descoberto);
        }

        aux = aux->getProx();
    }
}


//! Auxiliares

//!Preenche o vetor pilha na ordem que os nós "morrem" na busca em profundidade
void Grafo::ordenacaoTopologica(int v, bool visitados[], std::vector<int>& pilha)
{
    // marca o vértice atual como visitado
    visitados[v-1] = true;

    Adjacencia* aux = getNo(v)->getAdjRaiz();
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
    std::cout<< std::endl<<"   | Id: "<<v<<", Dado: "<<getNo(v)->getDado();

    // percorre os adjacentes de v
    Adjacencia* aux = getNo(v)->getAdjRaiz();
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
    Grafo* subjacente = new Grafo(false);
    int n = getMaiorId();
    for(int i=1;i<=n;i++){
        if(getNo(i)!=NULL)
            subjacente->criarNo(i,getNo(i)->getDado());
    }
    No* aux = noRaiz;
    while(aux!=NULL){
        Adjacencia* aux2 = aux->getAdjRaiz();
        while(aux2!=NULL){
            subjacente->criarAdj(aux->getId(),aux2->getNoFim()->getId(),aux2->getPeso());
            aux2 = aux2->getProx();
        }
        aux = aux->getProx();
    }
    return subjacente;

}

Grafo* Grafo::grafoReverso(){
    Grafo* reverso = new Grafo(true);
    int n = getOrdem();
    for(int i=1;i<=n;i++){
        if(getNo(i)!=NULL)
            reverso->criarNo(i,getNo(i)->getDado());
    }
    No* aux = noRaiz;
    while(aux!=NULL){
        Adjacencia* aux2 = aux->getAdjRaiz();
        while(aux2!=NULL){
            reverso->criarAdj(aux2->getNoFim()->getId(),aux->getId(),aux2->getPeso());
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
    Adjacencia* aux = getNo(id)->getAdjRaiz();
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


//! Função que remove todas as adjacências com um determinado id. Complementa a remoção do nó.
void Grafo::removerTodasAdj(int id)
{
    No *remover = getNo(id);
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
    No* aux = noRaiz;
    while(aux!=NULL){
        std::cout<<"Id " <<aux->getId()<<", Info "<<aux->getDado()<<std::endl;
        Adjacencia* aux2 = aux->getAdjRaiz();
        while(aux2!=NULL){
            std::cout<<"  |- Destino: " <<aux2->getNoFim()->getId()<<", Peso: "<<aux2->getPeso()<<std::endl;
            aux2 = aux2->getProx();
        }
        aux = aux->getProx();
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
No* auxGetNo(No* no, int id)
{
    if(no == NULL) return NULL;

    if (no->getId() == id) return no;
    else return auxGetNo(no->getProx(),id);
}

No* Grafo::getNo(int id)
{
    return auxGetNo(noRaiz,id);
}



//! Gets e seters

int Grafo::getOrdem(){
    return ordem;
}
