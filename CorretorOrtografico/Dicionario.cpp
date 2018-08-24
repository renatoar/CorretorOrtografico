/* 
 * File:   Dicionario.cpp
 * Author: 
 * Renato Araujo Rizzo          RA: 587788
 * Renato Candido Kurosaki      RA: 587834
 * Gustavo Leite                RA: 552615
 *
 *
 * Created on 17 de Julho de 2018, 07:50
 */

#include <list>

#include "Dicionario.h"

using namespace std;

//Monta a AVL com as palavras no dicionario fornecido
Dicionario::Dicionario(){   
    try{
        avl = new Arvore();
    }
    catch(bad_alloc){
        cout << "Memoria insuficiente!" << endl;
    }
    
    
    try{
        avl = avl->Carregar("dict.txt");
        
        if(avl == NULL)
            throw 200;
    }
    catch(int e){
        cout << "Arvore nao pode ser carregada!" << endl;
    }
    
    cout << "Arvore carregada com sucesso!" << endl;
}

//Destrutor limpa a AVL e tambem limpa a lista de Palavras
Dicionario::~Dicionario(){
    avl->Salvar("dict.txt");
    avl->Limpar();
    delete avl;
    listaSemelhantes.clear();
}

void Dicionario::lista_Semelhantes(Palavra palavra){
    //Limpa a lista de palavras semelhantes do Dicionario
    limparListaSemelhantes();
    
    //Limpa a lista de semelhantes da AVL
    avl->limpaListaSemelhantes();
    
    //Monta uma lista na avl com as semelhantes passadas como parametro
    avl->lista_semelhantes(palavra);
    
    //Pega a lista da arvore e armazena na lista do dicionario
    listaSemelhantes = avl->getListaSemelhantes();
}

void Dicionario::limparListaSemelhantes(){
    listaSemelhantes.clear();
}

list<Palavra> Dicionario::getListaSemelhantes(){
    return listaSemelhantes;
}

//Insere a palavra na arvore para atualizar o dicionario
void Dicionario::incluirPalavra(string palavra){
    avl->Inserir(palavra);
}

bool Dicionario::consultar(Palavra palavra){
    /*Busca para ver se a palavra do texto existe no dicionario.
     * Caso nao exista, monta uma lista de palavras semelhantes
     * e retorna falso, pois nao existe a palavra no dicionario.
     * 
     */ 
    if(avl->Buscar( palavra.getPalavra() ) == false ){
        lista_Semelhantes(palavra);
        return false;
    }
    
    return true;
        
}