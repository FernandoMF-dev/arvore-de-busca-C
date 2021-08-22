#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "arvore-binaria.h"
#include "pessoa.h"

int main(int argc, char const *argv[]) {
    setlocale(LC_ALL, "Portuguese");
    ArvoreBinaria *arvore = criarArvore();
    int count;

    scanf("%d", &count);
    for (int i = 0; i < count; i++) {
        addArvore(arvore, lerPessoa());
    }
    imprimirArvore(arvore);

    free(arvore);
    return EXIT_SUCCESS;
}