/* 
 * File:   Texto.h
 * Author: 
 * Renato Araujo Rizzo          RA: 587788
 * Renato Candido Kurosaki      RA: 587834
 * Gustavo Leite                RA: 552615
 *
 * Created on 14 de Julho de 2018, 07:03
 */

#include "Palavra.h"
#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

class Texto{
private:
    string nome_arquivo;
    list<Palavra> texto;
    
public:
    Texto();
    
    ~Texto();
    
    //Armazena o nome do arquivo texto
    void setNomeArquivo(const string arquivo);
    
    //Passado como parametro o nome do arquivo a ser aberto pela classe Corretor
    void lerArquivo();
    
    //Salvar o texto em um arquivo
    bool salvarTexto(const string &nomeArquivo, list<Palavra> &novoTexto);
    
    //Retorna a lista que contem as Palavras do texto
    list<Palavra> getTexto();
};


