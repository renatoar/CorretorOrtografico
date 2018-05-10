/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Arvore.cpp
 * Author: Renato Rizzo, Renato Kurosaki, Gustvo Leite
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

