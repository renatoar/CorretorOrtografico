/* 
 * File:   No.cpp
 * Author: 
 * Renato Araujo Rizzo          RA: 587788
 * Renato Candido Kurosaki      RA: 587834
 * Gustavo Leite                RA: 552615
 *
 * Created on 10 de Maio de 2018
 */

#include "No.h"
#include "Palavra.h"
#include <string>

No::No(const string& chave){
            (this->word).setPalavra(chave);
            this->SubArvore[ESQUERDA]  = NULL;
            this->SubArvore[DIREITA] = NULL;
            this->Balance = IGUAL;
}

No::~No(){
    delete this->SubArvore[ESQUERDA];
    delete this->SubArvore[DIREITA];
}