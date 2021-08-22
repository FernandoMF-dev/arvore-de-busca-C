#include "arvore-binaria.h"

/*
==================================================
CONSTANTES
==================================================
*/

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
#define ERROR_INSERIR_REPETIDO "\n\tERRO: Valor já existe na árvore binária!\n"
#define ERROR_VALOR_NAO_ENCONTRADO "\n\tERRO: Valor não encontrado!\n"
#define ERROR_ARVORE_VAZIA "\n\tERRO: Árvore binária vazia!\n"

/*
==================================================
DECLARAÇÃO DE MÉTODOS
==================================================
*/
No* _criarNo();
No* _insere(No *no, Pessoa valor);
Pessoa _findNo(No *no, Pessoa chave);
No* _removerNoComZeroFilhos(No *no);
No* _removerNoComUmFilho(No *no);
No* _removerNoComDoiFilhos(No *no, Pessoa chave);
No* _removeNo(No *no, Pessoa chave);
void _imprimirNo(No *no);
int _calcularTamanhoArvore(No *no);
int _calcularAlturaArvore(No *no);
void _preencherAlturaNo(No *no, int altura);

int _getAltura(No *no);
int _altura(No *no);
int _maior(int x, int y);
int _fatorBalaceamentoNo(No *no);
No* _rotacaoLL(No *raiz);
No* _rotacaoRR(No *raiz);
No* _rotacaoLR(No *raiz);
No* _rotacaoRL(No *raiz);
No* _balancearArvoreDireita(No *no, Pessoa valor);
No* _balancearArvoreEsquerda(No *no, Pessoa valor);
No* _balancearArvoreDireitaRemover(No *raiz);
No* _balancearArvoreEsquerdaRemover(No *raiz);

ArvoreBinaria *criarArvore();
void addArvore(ArvoreBinaria *arvore, Pessoa valor);
Pessoa findArvore(ArvoreBinaria *arvore, Pessoa chave);
void removeArvore(ArvoreBinaria *arvore, Pessoa chave);
void imprimirArvore(ArvoreBinaria *arvore);
void atualizarDadosArvore(ArvoreBinaria *arvore);

/*
==================================================
CONTROLES DE ALTERAÇÕES NA ÁRVORE
==================================================
*/

/*
=> Cria uma nova instância de uma struct 'No'

[1] Retorna essa instância
*/
No *_criarNo() {
    No* no = (No*)malloc(sizeof(No));

    if (no != NULL) {
        no->altura = 0;
        no->esquerda = NULL;
        no->direita = NULL;
    }

    return no;
}

/*
=> Cria uma nova instância de uma struct 'No';
=> Preenche o valor desse Nó com {valor}.

[1] Retorna essa instância
*/
No* alocarNo(Pessoa valor) {
    No* novo = _criarNo();

    novo->valor = valor;

    return novo;
}

/*
=> Controla a inserção de um novo Nó numa árvore
*/
No* _insere(No *no, Pessoa valor) {
    if(no == NULL) {
        no = alocarNo(valor);
    } else if(pessoaCmp(valor, no->valor) < 0) {
        no->esquerda = _insere(no->esquerda, valor);
        no = _balancearArvoreEsquerda(no, valor);
    } else if(pessoaCmp(valor, no->valor) > 0)   {
        no->direita = _insere(no->direita, valor);
        no = _balancearArvoreDireita(no, valor);
    }

    no->altura = _getAltura(no);
    return no;
}

/*
=> Controla a busca por um Nó específico conforme {chave}
*/
Pessoa _findNo(No *no, Pessoa chave) {
    if (no == NULL) {
        printf(ERROR_VALOR_NAO_ENCONTRADO);
        Pessoa vazio;
        return vazio;
    }
    if (pessoaBusca(chave, no->valor) > 0) {
        return _findNo(no->direita, chave);
    }
    if (pessoaBusca(chave, no->valor) < 0) {
        return _findNo(no->esquerda, chave);
    }

    return no->valor;
}

/*
=> Controla a remoção de um Nó que não possua qualque Nó filho numa árvore.
*/
No* _removerNoComZeroFilhos(No *no) {
    free(no);
    return NULL;
}

/*
=> Controla a remoção de um Nó que possua apenas um Nó filho numa árvore.
*/
No* _removerNoComUmFilho(No *no) {
    No *suporte;

    if (no->esquerda != NULL) {
        suporte = no->esquerda;
    } else {
        suporte = no->direita;
    }

    free(no);
    return suporte;
}

/*
=> Controla a remoção de um Nó que possua dois Nós filhos numa árvore.
*/
No* _removerNoComDoiFilhos(No *no, Pessoa chave) {
    No *suporte = no->esquerda;
    Pessoa backup = no->valor;

    while (suporte->direita != NULL) {
        suporte = suporte->direita;
    }
    no->valor = suporte->valor;
    suporte->valor = backup;
    no->esquerda = _removeNo(no->esquerda, chave);

    return no;
}

/*
=> Busca qual nó deve ser removido numa árvore conforme {chave}.
*/
No* _removeNo(No *no, Pessoa chave) {
    if (no == NULL) {
        printf(ERROR_VALOR_NAO_ENCONTRADO);
        return NULL;
    }

    if (pessoaBusca(chave, no->valor) == 0) {
        if (no->esquerda == NULL && no->direita == NULL) {
            return _removerNoComZeroFilhos(no);
        }
        if (no->esquerda == NULL || no->direita == NULL) {
            return _removerNoComUmFilho(no);
        }
        no = _removerNoComDoiFilhos(no, chave);
        return _balancearArvoreEsquerdaRemover(no);
    } else {
        if (pessoaBusca(chave, no->valor) > 0) {
            no->direita = _removeNo(no->direita, chave);
            no = _balancearArvoreDireitaRemover(no);
        } else {
            no->esquerda = _removeNo(no->esquerda, chave);
            no = _balancearArvoreEsquerdaRemover(no);
        }
        return no;
    }
}

/*
=> Imprime um Nó.
*/
void _imprimirNo(No *no) {
    if (no != NULL) {
        if (no->valor.identificador == 'E') {
            imprimirPessoa(no->valor);
            _imprimirNo(no->esquerda);
            _imprimirNo(no->direita);
        } else {
            _imprimirNo(no->esquerda);
            imprimirPessoa(no->valor);
            _imprimirNo(no->direita);
        }
    }
}

/*
=> Calcular o número de elementos salvos numa árvore.

[1] Retorna o valor calculado.
*/
int _calcularTamanhoArvore(No *no) {
    if (no == NULL) {
        return 0;
    }

    int size = 1;
    
    size += _calcularTamanhoArvore(no->esquerda);
    size += _calcularTamanhoArvore(no->direita);

    return size;
}

/*
=> Calcula a altura de uma ÁrvoreBinária.

[1] Retorna o valor calculado.
*/
int _calcularAlturaArvore(No *no) {
    if (no == NULL) {
        return -1;
    }

    return _maior(_calcularAlturaArvore(no->esquerda), _calcularAlturaArvore(no->direita)) + 1;
}

/*
=> Calcula e preenche a altura de de cada Nó numa árvore com base na altura dessa.
*/
void _preencherAlturaNo(No *no, int altura) {
    if (no == NULL) {
        return;
    }

    no->altura = altura;
    _preencherAlturaNo(no->esquerda, altura - 1);
    _preencherAlturaNo(no->direita, altura - 1);
}

/*
==================================================
BALANCEAMENTO
==================================================
*/

/*
=> Calcula a altura de um Nó baseado em seus filhos.

[1] Retorna esse valor.
*/
int _getAltura(No *no) {
    return _maior(_altura(no->esquerda), _altura(no->direita)) + 1;
}

/*
[1] Se {no} for nulo, retorna -1.
[2] Se {no} não for nulo, retorna a altura de {no}.
*/
int _altura(No *no) {
    if (no == NULL) {
        return -1;
    }
    return no->altura;
}

/*
=> Calcula e retorna o maior entre dois inteiros.

[1] Se {x} for maior que {y}, retorna {x}.
[1] Se {y} for maior ou igual a {x}, retorna {y}.
*/
int _maior(int x, int y) {
    if (x > y) {
        return x;
    }
    return y;
}

/*
=> Mede a diferença entre as alturas dos filhos de {no}.

[1] Retorna esse valor.
*/
int _fatorBalaceamentoNo(No *no) {
    return labs(_altura(no->esquerda) - _altura(no->direita));
}

No* _rotacaoLL(No *raiz) {
    No *suporte = raiz->esquerda;

    raiz->esquerda = suporte->direita;
    suporte->direita = raiz;

    raiz->altura = _getAltura(raiz);
    suporte->altura = _maior(_altura(suporte->esquerda), raiz->altura) + 1;
    
    return suporte;
}

No* _rotacaoRR(No *raiz) {
    No *suporte = raiz->direita;

    raiz->direita = suporte->esquerda;
    suporte->esquerda = raiz;

    raiz->altura = _getAltura(raiz);
    suporte->altura = _maior(_altura(suporte->direita), raiz->altura) + 1;

    return suporte;
}

No* _rotacaoLR(No *raiz) {
    raiz->esquerda = _rotacaoRR(raiz->esquerda);
    return _rotacaoLL(raiz);
}

No* _rotacaoRL(No *raiz) {
    raiz->direita = _rotacaoLL(raiz->direita);
    return _rotacaoRR(raiz);
}

No* _balancearArvoreDireita(No *raiz, Pessoa valor) {
    if (_fatorBalaceamentoNo(raiz) > 1) {
        if (pessoaCmp(valor, raiz->direita->valor) > 0) {
            raiz = _rotacaoRR(raiz);
        } else {
            raiz = _rotacaoRL(raiz);
        }
    }
    return raiz;
}

No* _balancearArvoreEsquerda(No *raiz, Pessoa valor) {
    if (_fatorBalaceamentoNo(raiz) > 1) {
        if (pessoaCmp(valor, raiz->direita->valor) < 0) {
            raiz = _rotacaoLL(raiz);
        } else {
            raiz = _rotacaoLR(raiz);
        }
    }
    return raiz;
}

No* _balancearArvoreDireitaRemover(No *raiz) {
    if (_fatorBalaceamentoNo(raiz) > 1) {
        if (_altura(raiz->esquerda->direita) > _altura(raiz->esquerda->esquerda)) {
            raiz = _rotacaoLR(raiz);
        } else {
            raiz = _rotacaoLL(raiz);
        }
    }
    return raiz;
}

No* _balancearArvoreEsquerdaRemover(No *raiz) {
    if (_fatorBalaceamentoNo(raiz) > 1) {
        if (_altura(raiz->direita->direita) < _altura(raiz->direita->esquerda)) {
            raiz = _rotacaoRL(raiz);
        } else {
            raiz = _rotacaoRR(raiz);
        }
    }
    return raiz;
}

/*
==================================================
MÉTODOS PÚBLICOS
==================================================
*/

/*
Cria e retorna uma nova instância de uma struct 'ArvoreBinaria'
*/
ArvoreBinaria *criarArvore() {
    ArvoreBinaria *arvore = (ArvoreBinaria*)malloc(sizeof(ArvoreBinaria));

    arvore->raiz = NULL;
    arvore->tamanho = 0;
    arvore->altura = 0;

    return arvore;
}

/*
=> Adiciona um Nó numa ArvoreBinaria
*/
void addArvore(ArvoreBinaria *arvore, Pessoa valor) {
    arvore->raiz = _insere(arvore->raiz, valor);
    atualizarDadosArvore(arvore);
}

/*
=> Procura um Nó numa ArvoreBinaria com base no valor de {chave}.

[1] Se existir um Nó que coincida com {chave}, retorna o valor desse Nó;
[2] Se não existir um Nó que coincida com {chave}, retorna uma struct 'Pessoa' vazia;
*/
Pessoa findArvore(ArvoreBinaria *arvore, Pessoa chave) {
    Pessoa retorno;

    if (arvore->raiz != NULL) {
        retorno = _findNo(arvore->raiz, chave);
    }
    printf(ERROR_ARVORE_VAZIA);
    return retorno;
}

/*
=> Procura e remove um Nó de uma ÁrvoreBinária com base no valor de {chave}
*/
void removeArvore(ArvoreBinaria *arvore, Pessoa chave) {
    if (arvore->raiz != NULL) {
        arvore->raiz = _removeNo(arvore->raiz, chave);
        atualizarDadosArvore(arvore);
    } else {
        printf(ERROR_ARVORE_VAZIA);
    }
}

/*
=> Imprime os dados e os Nós de uma ÁrvoreBinária.
*/
void imprimirArvore(ArvoreBinaria *arvore) {
    printf("\n");
    if (arvore->raiz != NULL) {
        _imprimirNo(arvore->raiz);
    }
    printf("\n");
}

/*
=> Calcula e preenche o 'tamanho' e a 'altura' de uma ÁrvoreBinária;
=> Calcula e preenche a altura de de cada Nó dessa árvore.
*/
void atualizarDadosArvore(ArvoreBinaria *arvore) {
    arvore->tamanho = _calcularTamanhoArvore(arvore->raiz);
    arvore->altura = _calcularAlturaArvore(arvore->raiz);
    _preencherAlturaNo(arvore->raiz, arvore->altura);
}
