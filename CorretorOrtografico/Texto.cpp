/* 
 * File:   Texto.cpp
 * Author: 
 * Renato Araujo Rizzo          RA: 587788
 * Renato Candido Kurosaki      RA: 587834
 * Gustavo Leite                RA: 552615
 *
 * Created on 14 de Julho de 2018, 07:22
 */

#include "Texto.h"
#include "Palavra.h"
#include <iostream>
#include <fstream>
#include <string>
#include <c++/6/bits/stl_list.h>

using namespace std;

Texto::Texto(){
    nome_arquivo = "";
    texto.clear();
}

Texto::~Texto(){
    texto.clear();
}

void Texto::setNomeArquivo(const string arquivo){
    nome_arquivo = arquivo;
}

void Texto::lerArquivo() {
    ifstream textoArquivo;
    //Tenta carregar o texto a partir do arquivo para a memoria
    try{
        textoArquivo.open(nome_arquivo);
        if(!textoArquivo.is_open())
            throw 200;
    }
    catch(int e){
        cout << "Erro ao abrir o arquivo para leitura!" << endl;
        return;
    }
    
    string aux;
    string linha;
    
    //@separador e uma lista de caracteres a serem descartados
    string separador{" \t\r\n,.!?;:"};
    
    //busca palavra por palavra do arquivo de texto descartando os separadores
    //definidos anteriormente
    //Faz a operacao linha por linha
    while(getline(textoArquivo, linha)){
        size_t e, s=0; //e: final da proxima palavra; s: offset da proxima palavra
        
        do{
            Palavra auxPalavra;
            //pula os caracteres separadores e para se nao ha mais palavras
            s = linha.find_first_not_of(separador, s);
            if(s == string::npos)
                break;
            
            //Acha o proximo separador e monta a palavra
            e = linha.find_first_of(separador, s);
            string aux(linha.substr(s, e-s));
            
            //Seta a string na classe Palavra e adiciona a palavra na lista
            auxPalavra.setPalavra(aux);
            texto.push_back(auxPalavra);
            
            //Posicao depois do separador
            s = e+1;
            
        //Ate chegar o final da linha
        } while(e != string::npos);
    }
    
    textoArquivo.close();
}

bool Texto::salvarTexto(const string& nomeArquivo, list<Palavra> &novoTexto){
    //Caso o nome do arquivo seja diferente, atualiza o nome do arquivo no objeto
    //da classe
    if(nomeArquivo != nome_arquivo && nomeArquivo != "")
        nome_arquivo = nomeArquivo;
    
    //Cria o arquivo textoArquivo para escrita
    ofstream textoArquivo;
    
    //Tenta abrir o arquivo com try-catch
    //Caso nao consiga, joga uma excecao e retorna falso
    try{
        textoArquivo.open(nomeArquivo);
        if(!textoArquivo.is_open())
            throw 200;
    }
    catch(int e){
        cout << "Erro ao abrir o arquivo para escrita!" << endl;
        return false;
    }
    
    //@aux armazenara a string palavra do objeto Palavra para ser escrito no arquivo
    //@it e o iterador da lista duplamente encadeada. Note que, por ser uma lista
    //duplamente encadeada, necessariamente precisamos desse iterador para percorrer
    //por toda lista.
    //it e setado no inicio da lista com "texto.begin()" e vai ate o final dela
    string aux;
    list<Palavra>::iterator it;
    it = novoTexto.begin();
    while(it != novoTexto.end()){
        //@it e ponteiro para a lista de objetos Palavra, por isso usa-se "->"
        aux = it->getPalavra();
        textoArquivo << aux << " ";
        //incrementa o iterador para passar para o proximo elemento da lista
        it++;
    }
    
    textoArquivo.close();
    return true;
}

list<Palavra> Texto::getTexto(){
    return texto;
}