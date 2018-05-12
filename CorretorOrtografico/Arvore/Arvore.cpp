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
        if(palavra.compare(aux->palavra) > 0){
            aux = aux->subArvore[DIREITA];
        }
        
        else if(palavra.compare(aux->palavra) < 0){
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