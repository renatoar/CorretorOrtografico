/* 
 * File:   Corretor.h
 * Author: 
 * Renato Araujo Rizzo          RA: 587788
 * Renato Candido Kurosaki      RA: 587834
 * Gustavo Leite                RA: 552615
 *
 * Created on 18 de Julho de 2018, 06:43
 */

#ifndef CORRETOR_H
#define CORRETOR_H

#include "Palavra.h"
#include "Texto.h"
#include "Dicionario.h"
#include <iostream>
#include <string>

using namespace std;

class Corretor{
private:
    Texto textoOriginal;
    Dicionario dicionario;
    list<Palavra> texto;
    list<Palavra> listaErros;
    list<Palavra> semelhantes;
    
    //lista de pares que associa uma palavra errada e o numero de vezes em que 
    //ela apareceu no texto.
    list<pair<Palavra, int>> erros;
    
public:
    Corretor();
    ~Corretor();
    //Carrega o texto na classe Texto. Associa essa lista carregada na lista do 
    //Corretor para poder ser manupulada.
    void carregarTexto();
    
    //void corrigirPalavra(string &palavra);
    void adicionarDicionario();
    
    void principal();
    
    //Salva o texto.
    void salvar();
};


#endif	// CORRETOR_H

