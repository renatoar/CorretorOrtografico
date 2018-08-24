/* 
 * File:   No.h
 * Author: 
 * Renato Araujo Rizzo          RA: 587788
 * Renato Candido Kurosaki      RA: 587834
 * Gustavo Leite                RA: 552615
 *
 * Created on 10 de Maio de 2018
 */

#ifndef NO_H
#define NO_H

#include <string>
#include "Palavra.h"

using namespace std;

enum Direcao{
    // Indica que a subarvore esquerda tem maior altura,
    // Que deve-se caminhar para a esquerda na pesquisa
    // ou que quer-se acessar a Subarvore da esquerda.
    ESQUERDA  = 0,

    // Indica que a subarvore direita tem maior altura,
    // Que deve-se caminhar para a direita na pesquisa
    // ou que quer-se acessar a Subárvore da direita.
    DIREITA = 1,

    // Indica que as subarvore tem alturas iguais.
    IGUAL = 2,
};

class No{
    public:

        No(const string& chave);    

        ~No();

        // Balanceamento do no
        unsigned short Balance;

        // Filhos da arvore
        // As subarvores direita e esquerda devem ser acessadas
        // utilizando apenas ->SubArvore[ESQUERDA] e ->SubArvore[DIREITA]
        No* SubArvore[2];

        //  palavra do dicionario e texto
        Palavra word;
};
#endif	// NO_H

