#ifndef ARVORE_BINARIA_H_INCLUDED
#define ARVORE_BINARIA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "pessoa.h"

typedef struct No {
    Pessoa valor;
    int altura;
    struct No *esquerda;
    struct No *direita;
}No;

typedef struct ArvoreBinaria {
    No *raiz;
    int tamanho;
    int altura;
}ArvoreBinaria;

ArvoreBinaria *criarArvore();

void addArvore(ArvoreBinaria *arvore, Pessoa valor);

Pessoa findArvore(ArvoreBinaria *arvore, Pessoa chave);

void removeArvore(ArvoreBinaria *arvore, Pessoa chave);

void imprimirArvore(ArvoreBinaria *arvore);

void atualizarDadosArvore(ArvoreBinaria *arvore);

#endif // ARVORE_BINARIA_H_INCLUDED