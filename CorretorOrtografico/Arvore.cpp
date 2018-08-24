/* 
 * File:   Arvore.cpp
 * Author: 
 * Renato Araujo Rizzo          RA: 587788
 * Renato Candido Kurosaki      RA: 587834
 * Gustavo Leite                RA: 552615
 *
 * Created on 10 de Maio de 2018
 */

#include "Arvore.h"
#include "Palavra.h"
#include<iostream>
#include<fstream>
#include <list>

using namespace std;

// Construtor
Arvore::Arvore(){

    // Inicia a raíz com null.
    this->raiz = NULL;

}

// Destrutor
Arvore::~Arvore(){

    this->Limpar();

}

// Limpa a árvore (remove todos seus nós)
void Arvore::Limpar(){

    // O destrutor dos nos ira
    // destruir todas as subarvores.
    delete raiz;
    this->raiz = NULL;
}

// Se a Arvore esta vazia, retorna verdadeiro, caso contrario, falso
bool Arvore::Vazia(){
    if(this->raiz != NULL)
        return false;
    else
        return true;
}

void Arvore::rotacionaUma(No*& no, Direcao dir){

    int oposto = this->oposto(dir);

    No* child = no->SubArvore[dir];

    no->SubArvore[dir] = child->SubArvore[oposto];

    child->SubArvore[oposto] = no;

    no = child;

}

// Realiza uma rotação dupla numa determinada direção.
//  aceita como parâmetro um nó onde a operação será efetuada
//  e uma direção (esquerda ou direita) para realizar a rotação.
void Arvore::rotacionaDuas(No*& no, Direcao dir){

    int oposto = this->oposto(dir);

    No* child = no->SubArvore[dir]->SubArvore[oposto];

    no->SubArvore[dir]->SubArvore[oposto] = child->SubArvore[dir];

    child->SubArvore[dir] = no->SubArvore[dir];

    no->SubArvore[dir] = child;

    child = no->SubArvore[dir];

    no->SubArvore[dir] = child->SubArvore[oposto];

    child->SubArvore[oposto] = no;

    no = child;
}

// Retorna a direção oposta à direção dada
inline Direcao Arvore::oposto(Direcao dir){

    return (dir == DIREITA) ? ESQUERDA : DIREITA;
}

// Atualiza os fatores de balanceamento após uma rotação
void Arvore::atualizaBal(No* no, Direcao dir){

    int oposto = this->oposto(dir);

    int bal = no->SubArvore[dir]->SubArvore[oposto]->Balance;

    // Se esta desbalanceado no mesmo lado
    if (bal == dir){

        no->Balance = IGUAL;

        no->SubArvore[dir]->Balance = oposto;
    }

    // Se esta desbalanceado do lado oposto
    else if (bal == oposto){

        no->Balance = dir;

        no->SubArvore[dir]->Balance = IGUAL;
    }

    else{
        no->Balance = no->SubArvore[dir]->Balance = IGUAL;
    }

    no->SubArvore[dir]->SubArvore[oposto]->Balance = IGUAL;
}

// Rebalanceamento apos uma insercao
void Arvore::rebalInserir(No*& no, Direcao dir, bool& hChanged){

    int oposto = this->oposto(dir);

    // Se o fator de balanceamento do nó era
    //  igual a direção em que houve a inserção,
    if (no->Balance == dir){ 

        if (no->SubArvore[dir]->Balance == dir){

            no->SubArvore[dir]->Balance = 2;

            no->Balance = IGUAL;

            rotacionaUma(no, dir);
        }

        else{

            atualizaBal(no, dir);
            rotacionaDuas(no, dir);
        }

        hChanged = false;
    }

    else if (no->Balance == oposto){
        no->Balance = 2;

        hChanged = false;
    }

    else{
        no->Balance = dir;
    }
}

// Efetua o rebalanceamento após uma operação de remoção
void Arvore::rebalRemover(No*& no, Direcao dir, bool& hChanged){

    Direcao oposto = this->oposto(dir);

    if (no->Balance == dir){                      

        no->Balance = IGUAL;
    }

    else if (no->Balance == oposto){

        // Temos 3 casos:
        if (no->SubArvore[oposto]->Balance == oposto){

            no->SubArvore[oposto]->Balance = IGUAL;

            no->Balance = IGUAL;

            rotacionaUma(no, oposto);

        }

        else if (no->SubArvore[oposto]->Balance == IGUAL){

            no->SubArvore[oposto]->Balance = dir;

            rotacionaUma(no, oposto);
        }

        else{

            atualizaBal(no, oposto);

            rotacionaDuas(no, oposto);
        }

        hChanged = false;
    }

    else{

        no->Balance = oposto;

        hChanged = false;
    }
}

bool Arvore::Buscar(const string& chave){

    // No raiz
    No* atual = this->raiz;
    
    // Verifica se a Arvore esta vazia
    if(Vazia() == true)
        return false;

    while (atual != NULL){

        if (chave > (atual->word).getPalavra()){
            // O valor está mais à direita
            atual = atual->SubArvore[DIREITA];
        }

        else if (chave < (atual->word).getPalavra()){
            // O valor está mais à esquerda
            atual = atual->SubArvore[ESQUERDA];
        }

        else{
            // Achou a palavra
            return true;
        }

    }

    // Nao achou a palavra
    return false;

}

// Insere uma nova palavra na Arvore
void Arvore::Inserir(const string& chave){
    bool hChanged = false; // Para passagem por referência

    // Chama o metodo recursivo
    this->inserir(chave, this->raiz, hChanged);
}

// Insere recursivo
void Arvore::inserir(const string& chave, No*& no, bool& hChanged){

    // Se o nó atual é nulo,
    if (no == NULL){
        no = new No(chave);

        // A altura mudou
        hChanged = true;
    }

    else if ( (no->word).getPalavra() == chave){
        // A informação já estava na árvore
        return;
    }

    else{
        Direcao dir = (chave > (no->word).getPalavra()) ? DIREITA : ESQUERDA;

        hChanged = false; // chamamos recursão

        inserir(chave, no->SubArvore[dir], hChanged);

        if (hChanged){
            // Rebalanceia
            this->rebalInserir(no, dir, hChanged);

        }
    }
}


bool Arvore::Remover(const string& palavra){

    bool hChanged = false; // para passagem por referência

    // Chama o metodo recursivo
    return this->remover(palavra, this->raiz, hChanged);

}

// Remove uma palavra da Arvore retornando true caso tenha sucesso
bool Arvore::remover(const string& chave, No*& no, bool& hChanged){
    bool success = false;

    // No nao encontrado
    if (no == NULL){
        hChanged = false;

        return false;
    }

    // Achamos o nó
    else if (chave == no->word.getPalavra()){

        // Caso tenha dois filhos
        if (no->SubArvore[ESQUERDA] != NULL && no->SubArvore[DIREITA] != NULL ){
            No* substitute = no->SubArvore[ESQUERDA];

            while (substitute->SubArvore[DIREITA] != NULL){
                substitute = substitute->SubArvore[DIREITA];
            }

            no->word = substitute->word;

            success = remover(no->word.getPalavra(), no->SubArvore[ESQUERDA], hChanged);

            if (hChanged){
                rebalRemover(no, ESQUERDA, hChanged);
            }
        }

        else{

            // Para apagar o nó
            No* temp = no;

            // Se um dos seus filhos e diferente de NULL
            Direcao dir = (no->SubArvore[ESQUERDA] == NULL) ? DIREITA : ESQUERDA;

            // Substituímos o nó por um dos seus filhos
            no = no->SubArvore[dir];
            temp->SubArvore[ESQUERDA]  = NULL;
            temp->SubArvore[DIREITA] = NULL;

            delete temp;

            // Se altura mudou, propagamos a mudança
            hChanged = true;
        }
        return true;
    }

    else{

        Direcao dir = (chave > no->word.getPalavra()) ? DIREITA : ESQUERDA;

        if (no->SubArvore[dir] != NULL){

            // Recursao para a direcao onde devera estar a palavra
            success = this->remover(chave, no->SubArvore[dir], hChanged);

        }

        else{
            // O no nao esta na arvore
            hChanged = false;

            return false;
        }

        if (hChanged){ //Se a altura mudou

            this->rebalRemover(no, dir, hChanged);
        }
        return success;

    }

}

Arvore* Arvore::Carregar(const char* path){

    // Constrói a arvore a partir do arquivo
    ifstream stream(path);

    if (stream.is_open()){

        Arvore* tree = new Arvore();

        string chave;

        while (!stream.eof()){
            stream >> chave;

            if (stream.fail()) break;
            tree->Inserir(chave);
        }
        
        stream.close();
        return tree;

    }
    return NULL;
}

// Salva a arvore para um arquivo em disco, aceitando
//  uma cadeia de caracteres indicando seu caminho.
//  Retorna true em caso de sucesso, falso caso contrario.
bool Arvore::Salvar(const char* path){
    // Se a árvore está vazia,
    if (this->raiz == NULL){
        // Apagamos o arquivo.
        std::remove(path);
        return true;

    }

    ofstream stream(path);

    if (stream.is_open()){
        // Chamamos função recursiva

        this->salvar(stream, this->raiz);
        stream.close();

        // Arquivo salvo com sucesso
        return true;
    }

    else{
        // Erro ao salvar arquivo
        return false;

    }
}

// Salva a arvore para um arquivo em pre-ordem, retornando false em caso de erro
bool Arvore::salvar(ofstream& stream, No* no){

    if (stream.is_open()){

        if (no != NULL){
            stream << (no->word).getPalavra()   << endl;

            this->salvar(stream, no->SubArvore[ESQUERDA]);
            this->salvar(stream, no->SubArvore[DIREITA]);
        }
        return true;

    }
    else return false;
}

void Arvore::lista_semelhantes(Palavra palavra){
    this->listaSemelhantes(this->raiz, palavra);
}

/*Percorre por toda a arvore buscando as palavras semelhantes a passada como 
 * parametro. Caso encontre, essa palavra e adicionada a uma lista de Palavras
 */
void Arvore::listaSemelhantes(No* no, Palavra palavra){
    if (no != NULL){        
        this->listaSemelhantes(no->SubArvore[ESQUERDA], palavra);
        
        
        string aux;
        aux = palavra.getPalavra();
        if(no->word.semelhante( aux ) == true && this->checaListaSemelhantes( no->word.getPalavra() ) == true){ 
            semelhantes.push_back( no->word );
        }
        
        this->listaSemelhantes(no->SubArvore[DIREITA], palavra);
    }
}

list<Palavra> Arvore::getListaSemelhantes(){
    return semelhantes;
}

void Arvore::limpaListaSemelhantes(){
    semelhantes.clear();
    return;
}

//Verifica se a palavra semelhante do dicionario ja foi incluida na lista de
//palavras semelhantes
bool Arvore::checaListaSemelhantes(string palavra){
    if(semelhantes.empty())
        return true;
    
    
    list<Palavra>::iterator iterador = semelhantes.begin();
    
    while(iterador != semelhantes.end()){
        if(iterador->getPalavra() == palavra){
            return false;
        }
        iterador++;
    }
    
    return true;
}