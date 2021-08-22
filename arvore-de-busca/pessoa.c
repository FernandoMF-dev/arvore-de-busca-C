#include "pessoa.h"

/*
==================================================
CONSTANTES
==================================================
*/

#define ERRO_IDENTIFICADOR_INVALIDO "\n\tERRO: Identificador inválido!!\n"

#define ID_PESSOA_FISICA 'P'
#define ID_PESSOA_JURIDICA 'E'

/*
==================================================
DECLARAÇÃO DE MÉTODOS
==================================================
*/

void _imprimirPessoaFiscia(Pessoa pessoa);
void _imprimirPessoaJuridica(Pessoa pessoa);
Pessoa _lerPessoaFisica();
Pessoa _lerPessoaJuridica();
float _pessoaFisicaCmp(Pessoa pessoa1, Pessoa pessoa2);
float _pessoaJuridicaCmp(Pessoa pessoa1, Pessoa pessoa2);

Pessoa lerPessoa();
void imprimirPessoa(Pessoa pessoa);
float pessoaCmp(Pessoa pessoa1, Pessoa pessoa2);
float pessoaBusca(Pessoa chave, Pessoa pessoa);

/*
==================================================
MÉTODOS PRIVADOS
==================================================
*/

void _imprimirPessoaFiscia(Pessoa pessoa) {
    printf("\n%c", pessoa.identificador);
    printf("\n%s", pessoa.nome);
    printf("%d", pessoa.idade);
    printf("\n%.1f", pessoa.altura);
}

void _imprimirPessoaJuridica(Pessoa pessoa) {
    printf("\n%c", pessoa.identificador);
    printf("\n%s", pessoa.cnpj);
    printf("%s", pessoa.nome);
    printf("%.2f", pessoa.balanco);
}

Pessoa _lerPessoaFisica() {
    Pessoa pessoa;
    
    pessoa.identificador = ID_PESSOA_FISICA;
    strcpy(pessoa.cnpj, "");
    pessoa.balanco = 0;

    fgets(pessoa.nome, sizeof(pessoa.nome), stdin);
    scanf("%d", &pessoa.idade);
    scanf("%f", &pessoa.altura);

    return pessoa;
}

Pessoa _lerPessoaJuridica() {
    Pessoa pessoa;
    
    pessoa.identificador = ID_PESSOA_JURIDICA;
    pessoa.idade = 0;
    pessoa.altura = 0;

    fgets(pessoa.cnpj, sizeof(pessoa.cnpj), stdin);
    fgets(pessoa.nome, sizeof(pessoa.nome), stdin);
    scanf("%f", &pessoa.balanco);

    return pessoa;
}

float _pessoaFisicaCmp(Pessoa pessoa1, Pessoa pessoa2) {
    float saida;

    if (pessoa1.idade != pessoa2.idade) {
        return (pessoa1.idade - pessoa2.idade);
    }

    saida = strcmp(pessoa1.nome, pessoa2.nome);
    if (!saida) {
        saida = pessoa1.altura - pessoa2.altura;
    }
    return saida;
}

float _pessoaJuridicaCmp(Pessoa pessoa1, Pessoa pessoa2) {
    float saida;

    if (pessoa1.balanco != pessoa2.balanco) {
        return (pessoa1.balanco - pessoa2.balanco);
    }

    saida = strcmp(pessoa1.nome, pessoa2.nome);
    if (!saida) {
        saida = strcmp(pessoa1.cnpj, pessoa2.cnpj);
    }
    return saida;
}

/*
==================================================
MÉTODOS PÚBLICOS
==================================================
*/

Pessoa lerPessoa() {
    char identificador = ID_PESSOA_JURIDICA;

    while (1) {
        scanf(" %c", &identificador);
        getchar();

        if (identificador == ID_PESSOA_FISICA) {
            return _lerPessoaFisica();
        }
        if (identificador == ID_PESSOA_JURIDICA) {
            return _lerPessoaJuridica();
        }

        printf(ERRO_IDENTIFICADOR_INVALIDO);
    }
}

void imprimirPessoa(Pessoa pessoa) {
    if (pessoa.identificador == ID_PESSOA_FISICA) {
        _imprimirPessoaFiscia(pessoa);
    } else {
        _imprimirPessoaJuridica(pessoa);
    }
}

/*
=> Realiza a comparação entre duas structs 'Pessoa' com base em seus dados.

[1] Se {pessoa1} for maior que {pessoa 2}, retorna um valor maior que 0;
[2] Se {pessoa1} for igual a {pessoa 2}, retorna 0;
[3] Se {pessoa1} for menor que {pessoa 2}, retorna um valor menor que 0;
*/
float pessoaCmp(Pessoa pessoa1, Pessoa pessoa2) {
    if (pessoa1.identificador != pessoa2.identificador) {
        if (pessoa1.identificador == ID_PESSOA_JURIDICA) {
            return 1;
        } else {
            return -1;
        }
    }

    if (pessoa1.identificador == ID_PESSOA_JURIDICA) {
        return _pessoaJuridicaCmp(pessoa1, pessoa2);
    } else {
        return _pessoaFisicaCmp(pessoa1, pessoa2);
    }
}

/*
=> Verifica se {chave} corresponde a {pessoa}.

[1] Se {chave} for maior que {pessoa}, retorna um número maior que 0;
[2] Se {chave} corresponde a {pessoa}, retorna 0;
[3] Se {chave} for menor que {pessoa}, retorna um número menor que 0;
*/
float pessoaBusca(Pessoa chave, Pessoa pessoa) {
    if (chave.identificador != pessoa.identificador) {
        if (chave.identificador == ID_PESSOA_JURIDICA) {
            return 1;
        } else {
            return -1;
        }
    }

    if (chave.identificador == ID_PESSOA_JURIDICA) {
        return strcmp(chave.cnpj, pessoa.cnpj);
    } else {
        return chave.altura - pessoa.altura;
    }
}