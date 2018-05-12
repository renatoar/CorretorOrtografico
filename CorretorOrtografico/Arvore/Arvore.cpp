/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Arvore.cpp
 * Author: Renato Rizzo, Renato Kurosaki, Gustavo Leite
 *
 * Created on 10 de Maio de 2018, 18:10
 */
#include "Arvore.h"
#include <iostream>
#include <cstring>
using namespace std::string;
/*
 * Definicao das funcoes da classe Arvore e tambem da classe No 
 */

Arvore::Arvore(){ //Construtor da Arvore. Inicializa a raiz como nula
    this->raiz = NULL;
}
    
Arvore::~Arvore(){ //Remove todos os nos da Arvore
    this->limpa();
}

void Arvore::limpa(){ //O destrutor ira destruir as subarvores
    delete raiz;
    this->raiz = NULL;
}

bool Arvore::busca(const std::string& palavra){
    No* aux = this->raiz;
    while(aux != NULL){
        if(palavra > aux->palavra){
            aux = aux->subArvore[DIREITA];
        }
        
        else if(palavra < aux->palavra){
            aux = aux->subArvore[ESQUERDA];
        }
        
        else{
            return true;
        }
    }
}

//Faz a rotacao simples em uma direcao determinada por dir
void Arvore::rotaciona1(No*& no, Direcao dir){
    int oposto = this->oposto(dir);
    No* filho = no->subArvore[dir];
    no->subArvore[dir] = filho->subArvore[oposto];
    filho->subArvore[oposto] = no;
    no = filho;
}

//Faz a rotacao dupla em uma direcao determinada por dir
void Arvore::rotaciona2(No*& no, Direcao dir){
    int oposto = this->oposto(dir);
    No* filho = no->subArvore[dir]->subArvore[oposto];
    filho->subArvore[dir]->subArvore[oposto] = filho->subArvore[dir];
    filho->subArvore[dir] = no->subArvore[dir];
    no->subArvore[dir] = filho;
    filho = no->subArvore[dir];
    no->subArvore[dir] = filho->subArvore[oposto];
    filho->subArvore[oposto] = no;
    no = filho;
}

//Troca a direcao dada
inline Direcao Arvore::oposto(Direcao dir){
    return (dir == DIREITA) ? ESQUERDA : DIREITA;
}

//Atualiza o balanceamento apos uma rotacao
void Arvore::atualizaBalanceamento(No* no, Direcao dir){
    int oposto = this->oposto(dir);
    int bal = no->subArvore[dir]->subArvore[oposto]->balanceado;
    
    if (bal == dir){
        no->balanceado = IGUAL;
        no->subArvore[dir]->balanceado = oposto;
    }
    else if (bal == oposto){
        no->balanceado = dir;
        no->subArvore[dir]->balanceado = IGUAL;
    }
    else{
        no->balanceado = no->subArvore[dir]->balanceado = IGUAL;
    }
    no->subArvore[dir]->subArvore[oposto]->balanceado = IGUAL;
}

//Atualiza o balanceamento apos insercao
void Arvore::rebalInsere(No*& no, Direcao dir, bool& alterado){
    int oposto = this->oposto(dir);
    
    if (no->balanceado == dir){
        if(no->subArvore[dir]->balanceado == dir){
            no->subArvore[dir]->balanceado = 2;
            no->balanceado = IGUAL;
            rotaciona1(no, dir);
        }
        else{
            atualizaBalanceamento(no, dir);
            rotaciona2(no, dir);
        }
        alterado = false;
    }
    else if(no->balanceado == oposto){
        no->balanceado = 2;
        alterado = false;
    }
    else{
        no->balanceado = dir;
    }
}


//Faz o balanceamento apos uma remocao
void Arvore::rebalRemove(No*& no, Direcao dir, bool& alterado){
    Direcao oposto = this->oposto(dir);
    
    if(no->balanceado == dir){
        no->balanceado = IGUAL;
    }
    else if(no->balanceado == oposto){
        if(no->subArvore[oposto]->balanceado == oposto){
            no->subArvore[oposto]->balanceado = IGUAL;
            no->balanceado = IGUAL;
            rotaciona1(no, oposto);
        }
        else if(no->subArvore[oposto]->balanceado == IGUAL){
            no->subArvore[oposto]->balanceado = dir;
            rotaciona1(no, oposto);
        }
        else{
            atualizaBalanceamento(no, oposto);
            rotaciona2(no, oposto);
        }
        alterado = false;
    }
    
    else{
        no->balanceado = oposto;
        alterado = false;
    }
}

void Arvore::inserir(const std::string& palavra){
    bool alterado = false;
    //Chama o insere recursivo
    this->insereRecursivo(palavra, this->raiz, alterado);
}

//Todas as alocacoes dinamicas sao tratadas com try-catch no caso de haver uma
//excessao bad_alloc
void Arvore::insereRecursivo(const std::string& palavra, No*& no, bool& alterado){
    if(no == NULL){
        try{
            no = new No(palavra);
            alterado = true;
        }
        catch(std::bad_alloc){
            std::cout << "Nao ha memoria suficiente!" << std::endl;
        }
    }
    //verifica se a palavra ja existe na Arvore
    else if(no->palavra == palavra)
        return;
    else{
        Direcao dir = (palavra > no->palavra) ? DIREITA : ESQUERDA;
        alterado = false;
        insereRecursivo(palavra, no->subArvore[dir], alterado);
        if(alterado)
            this->rebalInsere(no, dir, alterado);
    }
}

bool Arvore::remover(const std::string& palavra){
    bool alterado = false;
    //funcao recursiva para remover
    return this->removeRecursivo(palavra, this->raiz, alterado);
}

//remove uma palavra da arvore e retorna true ou false caso nao tenha encontrado
//a palavra
bool Arvore::removeRecursivo(const std::string& palavra, No*& no, bool& alterado){
    bool retorno = false; //retorno guarda se bem ou mal sucedida a operacao
    //No nao foi encontrado
    if(no == NULL){
        alterado = false;
        return false;
    }
    //Foi encontrado
    else if(palavra == no->palavra){
        //Se o no tiver dois filhos
        if(no->subArvore[ESQUERDA] != NULL && no->subArvore[DIREITA] != NULL){
            //encontra-se um novo substituto
            No* substituto = no->subArvore[ESQUERDA];
            
            while(substituto->subArvore[DIREITA] != NULL)
                substituto = substituto->subArvore[DIREITA];
            
            no->palavra = substituto->palavra;
            retorno = removeRecursivo(no->palavra, no->subArvore[ESQUERDA], alterado);
            
            if(alterado) //se a altura mudou
                rebalRemove(no, ESQUERDA, alterado);
        }
        //O no tem apenas um filho
        else{
            No* aux = no;
            Direcao dir = (no->subArvore[ESQUERDA] == NULL) ? DIREITA : ESQUERDA;
            no = no->subArvore[dir];
            aux->subArvore[ESQUERDA] = NULL;
            aux->subArvore[DIREITA] = NULL;
            delete aux;
            alterado = true;
        }
        return true;
    }
    //No ainda nao encontrado
    else{
        Direcao dir = (palavra > no->palavra) ? DIREITA : ESQUERDA;
        if(no->subArvore[dir] != NULL){
            retorno = this->removeRecursivo(palavra, no->subArvore[dir], alterado);
        }
        else{
            alterado = false;
            return false;
        }
        if(alterado){
            this->rebalRemove(no, dir, alterado);
        }
        return retorno;
    }
}