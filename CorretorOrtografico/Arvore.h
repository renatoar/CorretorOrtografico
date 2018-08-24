/* 
 * File:   Arvore.h
 * Author: 
 * Renato Araujo Rizzo          RA: 587788
 * Renato Candido Kurosaki      RA: 587834
 * Gustavo Leite                RA: 552615
 *
 * Created on 10 de Maio de 2018
 */
#ifndef ARVORE_H
#define ARVORE_H

#include"No.h"
#include "Palavra.h"
#include<string>
#include <list>

using namespace std;

class Arvore

{

    public:

        // Construtor e destrutor padrões
        Arvore();

        ~Arvore();

        void Inserir(const string& word);

        bool Remover(const string& word);

        bool Buscar(const string& word);

        bool Vazia();
        
        void Limpar();

        // Para teste
        void Imprimir();

        static Arvore* Carregar(const char* path);

        bool Salvar(const char* path);
        
        //Buscar todas as palavras semelhantes a um potencial erro no texto
        void lista_semelhantes(Palavra palavra);

        //Retorna a lista de palavras semelhantes para o dicionario
        list<Palavra> getListaSemelhantes();
        
        void limpaListaSemelhantes();

    private:

        No* raiz;
        
        list<Palavra> semelhantes;

        // Rotações

        void rotacionaDuas(No*& no, Direcao dir);

        void rotacionaUma(No*& no, Direcao dir);

        // Rebalanceamentos

        void atualizaBal(No* tree,  Direcao dir);

        void rebalInserir(No*& tree, Direcao dir, bool& hChanged);

        void rebalRemover(No*& tree, Direcao dir, bool& hChanged);

        // Inserção e remoção recursivos

        void inserir(const string& word, No*& no, bool& hChanged);

        bool remover(const string& word, No*& no, bool& hChanged);

        // ----- //
        bool salvar(ofstream& stream, No* no);

        void imprimir(No* no);

        inline Direcao oposto(Direcao dir);
        
        void listaSemelhantes(No* no, Palavra palavra);
        
        bool checaListaSemelhantes(string palavra);

};


#endif	// ARVORE_H

