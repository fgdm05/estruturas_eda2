#include "def_rubro_negra.h"

No *criarNo(Arvore *arv, int valor) {
    No *no = (No *)malloc(sizeof(No));
    no->valor = valor;
    no->cor = Vermelho;
    no->esquerda = arv->nulo;
    no->direita = arv->nulo;
    no->pai = NULL;
    return no;
}

Arvore *criar() {
    Arvore *arv = (Arvore *)malloc(sizeof(Arvore));
    arv->nulo = (No *)malloc(sizeof(No));
    arv->nulo->cor = Preto;
    arv->nulo->esquerda = NULL;
    arv->nulo->direita = NULL;
    arv->raiz = arv->nulo;
    return arv;
}

void rotacionarEsquerda(Arvore *arv, No *x, int* ops) {
    No *y = x->direita;
    x->direita = y->esquerda;
    if (y->esquerda != arv->nulo)
        y->esquerda->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL)
        arv->raiz = y;
    else if (x == x->pai->esquerda)
        x->pai->esquerda = y;
    else
        x->pai->direita = y;
    y->esquerda = x;
    x->pai = y;
    (*ops)++;
}

void rotacionarDireita(Arvore *arv, No *y, int* ops) {
    No *x = y->esquerda;
    y->esquerda = x->direita;
    if (x->direita != arv->nulo)
        x->direita->pai = y;
    x->pai = y->pai;
    if (y->pai == NULL)
        arv->raiz = x;
    else if (y == y->pai->esquerda)
        y->pai->esquerda = x;
    else
        y->pai->direita = x;
    x->direita = y;
    y->pai = x;
    (*ops)++;

}

void insertFixup(Arvore *arv, No *z, int* ops) {
    while (z->pai && z->pai->cor == Vermelho) {
        if (z->pai == z->pai->pai->esquerda) {
            No *y = z->pai->pai->direita;
            if (y->cor == Vermelho) {  // Caso 1
                z->pai->cor = Preto;
                y->cor = Preto;
                z->pai->pai->cor = Vermelho;
                z = z->pai->pai;
            } else {
                if (z == z->pai->direita) {  // Caso 2
                    z = z->pai;
                    rotacionarEsquerda(arv, z, ops);
                }
                z->pai->cor = Preto;  // Caso 3
                z->pai->pai->cor = Vermelho;
                rotacionarDireita(arv, z->pai->pai, ops);
            }
        } else {
            No *y = z->pai->pai->esquerda;
            if (y->cor == Vermelho) {  // Caso 1
                z->pai->cor = Preto;
                y->cor = Preto;
                z->pai->pai->cor = Vermelho;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esquerda) {  // Caso 2
                    z = z->pai;
                    rotacionarDireita(arv, z, ops);
                }
                z->pai->cor = Preto;  // Caso 3
                z->pai->pai->cor = Vermelho;
                rotacionarEsquerda(arv, z->pai->pai, ops);
            }
        }
    }
    arv->raiz->cor = Preto;
}

void insert(Arvore *arv, int valor, int* ops) {
    No *z = criarNo(arv, valor);
    No *y = NULL;
    No *x = arv->raiz;

    while (x != arv->nulo) {
        y = x;
        if (z->valor < x->valor)
            x = x->esquerda;
        else 
            x = x->direita;
    }

    z->pai = y;
    if (y == NULL)
        arv->raiz = z;
    else if (z->valor < y->valor)
        y->esquerda = z;
    else
        y->direita = z;

    z->esquerda = arv->nulo;
    z->direita = arv->nulo;
    z->cor = Vermelho;

    insertFixup(arv, z, ops);
}

void transplantar(Arvore *arv, No *u, No *v) {
    if (u->pai == NULL)
        arv->raiz = v;
    else if (u == u->pai->esquerda)
        u->pai->esquerda = v;
    else
        u->pai->direita = v;
    v->pai = u->pai;
}

void deleteFixup(Arvore *arv, No *x, int* ops) {
    while (x != arv->raiz && x->cor == Preto) {
        if (x == x->pai->esquerda) {
            No *w = x->pai->direita;
            if (w->cor == Vermelho) {  // Caso 1
                w->cor = Preto;
                x->pai->cor = Vermelho;
                rotacionarEsquerda(arv, x->pai, ops);
                w = x->pai->direita;
            }
            if (w->esquerda->cor == Preto && w->direita->cor == Preto) {  // Caso 2
                w->cor = Vermelho;
                x = x->pai;
            } else {
                if (w->direita->cor == Preto) {  // Caso 3
                    w->esquerda->cor = Preto;
                    w->cor = Vermelho;
                    rotacionarDireita(arv, w, ops);
                    w = x->pai->direita;
                }
                w->cor = x->pai->cor;  // Caso 4
                x->pai->cor = Preto;
                w->direita->cor = Preto;
                rotacionarEsquerda(arv, x->pai, ops);
                x = arv->raiz;
            }
        } else {
            No *w = x->pai->esquerda;
            if (w->cor == Vermelho) {  // Caso 1
                w->cor = Preto;
                x->pai->cor = Vermelho;
                rotacionarDireita(arv, x->pai, ops);
                w = x->pai->esquerda;
            }
            if (w->direita->cor == Preto && w->esquerda->cor == Preto) {  // Caso 2
                w->cor = Vermelho;
                x = x->pai;
            } else {
                if (w->esquerda->cor == Preto) {  // Caso 3
                    w->direita->cor = Preto;
                    w->cor = Vermelho;
                    rotacionarEsquerda(arv, w, ops);
                    w = x->pai->esquerda;
                }
                w->cor = x->pai->cor;  // Caso 4
                x->pai->cor = Preto;
                w->esquerda->cor = Preto;
                rotacionarDireita(arv, x->pai, ops);
                x = arv->raiz;
            }
        }
    }
    x->cor = Preto;
}

void deletarNo(Arvore *arv, No *z, int* ops) {
    No *y = z;
    No *x;
    Cor yOriginalColor = y->cor;

    if (z->esquerda == arv->nulo) {
        x = z->direita;
        transplantar(arv, z, z->direita);
    } else if (z->direita == arv->nulo) {
        x = z->esquerda;
        transplantar(arv, z, z->esquerda);
    } else {
        y = z->direita;
        while (y->esquerda != arv->nulo)
            y = y->esquerda;
        yOriginalColor = y->cor;
        x = y->direita;
        if (y->pai == z)
            x->pai = y;
        else {
            transplantar(arv, y, y->direita);
            y->direita = z->direita;
            y->direita->pai = y;
        }
        transplantar(arv, z, y);
        y->esquerda = z->esquerda;
        y->esquerda->pai = y;
        y->cor = z->cor;
    }

    if (yOriginalColor == Preto)
        deleteFixup(arv, x, ops);
}

No *localizar(Arvore *arv, No *no, int valor) {
    if (no == arv->nulo || valor == no->valor)
        return no;
    if (valor < no->valor)
        return localizar(arv, no->esquerda, valor);
    return localizar(arv, no->direita, valor);
}

void inorder(Arvore *arv, No *no) {
    if (no != arv->nulo) {
        inorder(arv, no->esquerda);
        printf("%d ", no->valor);
        inorder(arv, no->direita);
    }
}