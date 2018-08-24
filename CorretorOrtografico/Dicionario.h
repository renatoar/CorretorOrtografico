/* 
 * File:   Dicionario.h
 * Author: 
 * Renato Araujo Rizzo          RA: 587788
 * Renato Candido Kurosaki      RA: 587834
 * Gustavo Leite                RA: 552615
 *
 *
 * Created on 17 de Julho de 2018, 06:13
 */

#include "Arvore.h"
#include "Palavra.h"
#include <iostream>

using namespace std;

class Dicionario{
private:
    //Uma AVL para armazenar as palavras do dicionario
    Arvore *avl;
    
    //Lista para armazenar as palavras semelhantes a uma palavra do texto
    list<Palavra> listaSemelhantes;
    
public:
    //Construtor da classe que ja carrega o dicionario e monta a AVL
    Dicionario();
    
    //Destrutor limpa a AVL e tambem a lista de Palavras
    ~Dicionario();
    
    //Adiciona uma palavra no dicionario
    void incluirPalavra(string palavra);
    
    //Consula uma palavra do texto no dicionario para verificar a sua existencia
    bool consultar(Palavra palavra);
    
    //Monta uma lista de palavras semelhantes a palavra passada como parametro
    void lista_Semelhantes(Palavra palavra);
    
    list<Palavra> getListaSemelhantes();
    
    void limparListaSemelhantes();
};
