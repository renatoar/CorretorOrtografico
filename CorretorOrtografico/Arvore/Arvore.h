/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Arvore.h
 * Author: Renato Rizzo, Renato Kurosaki, Gustavo Leite
 *
 * Created on 10 de Maio de 2018, 14:07
 */
#include <cstring>

#ifndef ARVORE_H
#define ARVORE_H

//Enumeracao para o acesso das subarvores e para o fator de balanceamento
enum Direcao{ESQUERDA = 0, DIREITA = 1, IGUAL = 2};

class Arvore{
    //Classe No e aninhada, pois apenas a classe Arvore a usa
    class No{
    public:
        No(const std::string& valor);
        ~No();
        unsigned short balanceado;
        No* subArvore[2]; //Serao acessadas as subarvores usasndo ESQUERDA e DIREITA
        std::string palavra;
    };
    
    
public:
    Arvore();
    ~Arvore();
    void inserir(const std::string& palavra);
    void remover(const std::string& palavra);
    bool busca(const std::string& palavra);
    bool vazia(); //verifica se a arvore esta vazia
    
private:
    void limpa();
    static Arvore* carrega(const char* path); //Carrega Arvore a partir de um arquivo de caminho "path"
    bool Salvar(const char* path); //Salva a arvore no caminho dado para "path"
    void rotaciona2(No*& no, Direcao dir); //Rotciona duas vezes
    void rotaciona1(No*& no, Direcao dir); //Rotaciona uma vez
    void atualizaBalanceamento(No* no, Direcao dir);
    void rebalInsere(No*& no, Direcao dir, bool& alterado); //rebalanceamento apos insercao
    void rebalRemove(No*& no, Direcao dir, bool& alterado); //rebalanceamento apos remocao
    void insereRecursivo(const std::string& palavra, No*& no, bool& alterado);
    void removeRecursivo(const std::string& palavra, No*& no, bool& alterado);
    bool salvar(std::ofstream& stream, No* no);
    inline Direcao oposto(Direcao dir);
    
    No* raiz;
};



#endif /* ARVORE_H */

