/* File:   Palavra.cpp
 * Author: 
 * Renato Araujo Rizzo          RA: 587788
 * Renato Candido Kurosaki      RA: 587834
 * Gustavo Leite 
 *
 * Created on 26 de Junho de 2018, 07:42
 */

#include"Palavra.h"

using namespace std;

Palavra::Palavra(const Palavra &palavra){
    this->palavra = palavra.palavra;
}

Palavra::Palavra( string& palavra){
    this->palavra = palavra;
}

Palavra::Palavra(){
    palavra = "";
}

void Palavra::setPalavra(Palavra palavra){
    this->palavra = palavra.palavra;
}

void Palavra::setPalavra( string palavra){
    this->palavra = palavra;
}

string Palavra::getPalavra() const{
    return palavra;
}

//Compara as duas primeiras letras das palavras.
//Serao semelhantes se as duas forem iguais, retornando true
//Caso nao sejam, retorna false
bool Palavra::semelhante(string palavra) const {
    if(this->palavra[0] == palavra[0] && this->palavra[1] == palavra[1])
        return true;
    
    return false;
           
}

//Verifica se as palavras sao identivas.
bool Palavra::operator ==(Palavra& palavra){
    return (this->palavra == palavra.palavra);
}