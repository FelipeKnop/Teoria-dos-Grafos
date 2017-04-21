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


//! Criação de adjacência
//! A função recebe dois ids e um peso para a aresta, e adiciona a adjacência em ambos os nós para o grafo não direcionado, ou apenas no primeiro para o direcionado
void Grafo::criarAdj(int idNoInicio, int idNoFim, int peso)
{
    No *no1 = getNo(idNoInicio), *no2 = getNo(idNoFim);
    if (no1 != NULL && no2 != NULL) {
        no1->adicionarAdj(no2, peso);
        if (!direcionado)
            no2->adicionarAdj(no1, peso);
        else
            no2->addGrauEntrada(1);
    } else {
        std::cout << "Adjac" << char(136) << "ncia " << idNoInicio << "," << idNoFim << " n" << char(198) << "o p" << char(147) << "de ser criada!" << std::endl;
    }
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


//! Informa a ordem do grafo
//! Chama a própria função getOrdem para obter essa informação e a imprime na tela
void Grafo::informaOrdem()
{
    int ordemGrafo = getOrdem();
    std::cout << "Ordem do grafo: " << ordemGrafo << std::endl;
}

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
    ordenaSequencia(sequencia, n);
    std::cout << "Sequ" << char(136) << "ncia de graus: ";
    for (i = 0; i < n; i++)
        std::cout << sequencia[i] << " ";
    std::cout << std::endl;
}

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

void Grafo::informaGrau()
{
    std::cout << "Grau do grafo: " << calculaGrau() << std::endl;
}

void Grafo::ordenaSequencia(int *sequencia, int n)
{
    int i, j, aux;

    for (i = 1; i < n; i++) {
        aux = sequencia[i];
        for (j = i - 1; j >= 0 && sequencia[j] > aux; j--)
            sequencia[j+1] = sequencia[j];
        sequencia[j+1] = aux;
    }
}

//! Imprime o subgrafo induzido por um conjunto de nós informados pelos seus ids
void Grafo::imprimeSubInduzido(int total, std::vector<int> &n)
{
    No *aux;
    Adjacencia *adj;
    int noId;
    for (int i = 0; i < total; i++) {
        aux = getNo(n.at(i));
        if (aux != NULL)
        {
            std::cout << "No " << n.at(i) << ":" << std::endl;
            adj = aux->getAdjRaiz();
            while (adj != NULL) {
                noId = adj->getNoFim()->getId();
                for (int k = 0; k < total; k++) {
                    if (noId == n.at(k)) {
                        std::cout << "\t" << n.at(i) << "\t" << n.at(k) << "\t" << adj->getPeso() << std::endl;
                        break;
                    }
                }
                adj = adj->getProx();
            }
        }

    }
}


//! Imprime a vizinhanca aberta de um no
void Grafo::vizinhancaAberta(int id)
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
    imprimeSubInduzido(nos.size(), nos);
}


//! Imprime a vizinhanca fechada de um no
void Grafo::vizinhancaFechada(int id)
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
    imprimeSubInduzido(nos.size(), nos);
}

//! Verifica se o grafo é completo
//! Obtém o grau do grafo e usa a função de verificar regularidade
//! para saber se ele é k-1-regular, depois verifica se é simples
bool Grafo::verificarCompleto() {
    int n = getOrdem();
    return verificaRegularidade(n-1) && verificarSimples();
}

bool Grafo::verificarSelfLoop() {
    No *aux = noRaiz;
    while (aux != NULL) {
        if(aux->verificarSelfLoop())
            return true;
        aux = aux->getProx();
    }
    return false;
}

bool Grafo::verificarSimples() {
    return !verificarMultigrafo() && !verificarSelfLoop();
}

//! Verifica se o grafo é bipartido
//! Função auxiliar realiza busca em profundidade para definir as partições
bool profBipartido(No* no, int* particoes,int parte){
    int id = no->getId();

    if(particoes[id-1]==0) particoes[id-1] = parte;
    else if(particoes[id-1]!=parte) {
        return false;
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

//! Obter complementar
//! Função retorna o complementar de um grafo
Grafo* Grafo::obterComplementar(){
    Grafo* comp = new Grafo(direcionado);
    int n = getMaiorId();
    for(int i=1;i<=getMaiorId();i++){
        if(getNo(i)!=NULL)
            comp->criarNo(i,getNo(i)->getDado());
    }
    No* aux = noRaiz;
    while(aux!=NULL){
        for(int i = 1;i<=getMaiorId();i++){
            if(!aux->existeAdj(i))
                comp->criarAdj(aux->getId(),i,0);
        }
        aux = aux->getProx();
    }
    return comp;

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

//! Gets e seters


int Grafo::getOrdem(){
    return ordem;
}
