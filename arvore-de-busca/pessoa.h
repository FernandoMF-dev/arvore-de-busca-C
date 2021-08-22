#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa {
    char identificador;
    char nome[51];
    char cnpj[51];
    int idade;
    float altura;
    float balanco;
} Pessoa;

Pessoa lerPessoa();

void imprimirPessoa(Pessoa pessoa);

float pessoaCmp(Pessoa pessoa1, Pessoa pessoa2);

float pessoaBusca(Pessoa chave, Pessoa pessoa);

#endif // PESSOA_H_INCLUDED