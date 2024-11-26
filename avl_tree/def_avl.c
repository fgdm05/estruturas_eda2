#include <stdlib.h>
#include <stdio.h>
#include "def_avl.h"

void balanceamento(AVL*, No*, int*);
int altura(No*);
int fb(No*);
No* rsd(AVL*, No*, int*);
No* rse(AVL*, No*, int*);
No* rdd(AVL*, No*, int*);
No* rde(AVL*, No*, int*);
No* criarNoAVL(No*, int);

AVL* criarAVL() {
    AVL *arvore = (AVL*)malloc(sizeof(AVL));
    arvore->raiz = NULL;
    return arvore;
}

void clear(AVL* arvore){
    clearNode(arvore->raiz);
    free(arvore);
}

void clearNode(No* no){
    if(no==NULL) return;
    clearNode(no->esquerda);
    clearNode(no->direita);
    free(no);
}


int vazia(AVL* arvore) {
    return arvore->raiz == NULL;
}
int max(int a,int b){
    if(a>b) return a;
    return b;
}
No* adicionarNo(No* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == NULL) {
            No* novo = criarNoAVL(no, valor);
            no->direita = novo;
            return novo;
        } else {
            return adicionarNo(no->direita, valor);
        }
    } else if (valor < no->valor){
        if (no->esquerda == NULL) {

            No* novo = criarNoAVL(no, valor);
            no->esquerda = novo;
            return novo;
        } else {
            return adicionarNo(no->esquerda, valor); 
        }
    }else{
        // printf("Valor ja existe!\n");
        return no;
    }
}

No* adicionar(AVL* arvore, int valor, int* ops) {
    if (vazia(arvore)) {
        arvore->raiz = criarNoAVL(NULL, valor);
        return arvore->raiz;
    } else {
        No* no = adicionarNo(arvore->raiz, valor);
        upHeight(no);
        balanceamento(arvore, no, ops);
        return no;
    }
}

No* removerNo(No* no, int valor, AVL* av) {
    if(valor < no->valor) {
        if(no->esquerda == NULL) {
            // printf("\nValor inexistente");
            return NULL;
        } else {
            return removerNo(no->esquerda, valor,av);
        }  
    } else if(valor > no->valor) {
        if(no->direita == NULL) {
            // printf("\nValor inexistente");
            return NULL;
        } else {
            return removerNo(no->direita, valor,av);;
        }
    } else {
        // Destruir no
        // caso tenha filhos, colocar um como pai
        No* pai = no->pai;
        int esq = 0;
        if(pai!=NULL) esq = valor < pai->valor;

        if(no->direita==NULL&&no->esquerda==NULL)
            return deleteLeaf(no,esq,av);

        if(no->direita==NULL||no->esquerda==NULL)
            return deleteSingle(no,esq,av);
        
        // Logo o nodo a ser deletado tem dois filhos
        No* tgt = no->direita;
        while(tgt->esquerda!=NULL) tgt = tgt->esquerda; // Sucessor a direita        
        no->valor = tgt->valor;
        
        pai = tgt->pai;
        esq = tgt->valor < pai->valor;
        
        if(tgt->direita==NULL&&tgt->esquerda==NULL)
            return deleteLeaf(tgt,esq,av);
        return deleteSingle(tgt,esq,av);

    }
}

No* deleteLeaf(No* no, int esq, AVL* av){
    No* pai = no->pai;
    free(no);
    if(pai==NULL){
        av->raiz=NULL;
        return NULL;
    }
    if(esq) pai->esquerda = NULL;
    else pai->direita = NULL;
    return pai;
}

No* deleteSingle(No* no, int esq, AVL* av){
    No* pai = no->pai;
    No* tgt;
    if(no->direita==NULL) tgt = no->esquerda;
    else tgt = no->direita;
    tgt->pai = pai;

    if(pai!=NULL)
        if(esq) pai->esquerda = tgt;
        else pai->direita = tgt;
    else av->raiz = tgt;
    free(no);
    return tgt;
}


No* remover(AVL* arvore, int valor, int* ops) {
    // printf("\nRemovendo %i\n",valor);
    if(vazia(arvore)) {
        // printf("\nArvore vazia");
        return NULL;
    } else {
        No* no = removerNo(arvore->raiz, valor,arvore);
        // printf("\nBALANCEAR");
        upHeight(no);
        balanceamento(arvore, no, ops);
        return no;
    }
}

No* criarNoAVL(No* pai, int valor) {
    No* no = (No*)malloc(sizeof(No));
    no->valor = valor;
    no->pai = pai;
    no->altura=1;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

No* localizarAVL(No* no, int valor) {
    if (no->valor == valor) {
        return no;
    } else {
        if (valor < no->valor) {
            if (no->esquerda != NULL) {
                return localizarAVL(no->esquerda, valor);
            }
        } else {
            if (no->direita != NULL) {
                return localizarAVL(no->direita, valor);
            }
        }
    }

    return NULL;
}

void percorrer(No* no, void (*callback)(int)) {
    if (no != NULL) {
        percorrer(no->esquerda,callback);
        callback(no->valor);
        percorrer(no->direita,callback);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}

void balanceamento(AVL* arvore, No* no, int* ops) {
    while (no != NULL) {
        int fator = fb(no);
        if (fator > 1) { // arvore mais profunda para a esquerda
            if (fb(no->esquerda) > 0) {
                rsd(arvore, no, ops); 
            } else {
                rdd(arvore, no, ops);
            }
        } else if (fator < -1) { // arvore mais profunda a direita
            if (fb(no->direita) < 0) {
                rse(arvore, no, ops);
            } else {
                rde(arvore, no, ops);
            }
        }
        upHeight(no);
        no = no->pai; 
    }
}

void upHeight(No* no){
    if(no==NULL) return;
    no->altura = max(altura(no->esquerda),altura(no->direita))+1;
    upHeight(no->pai);
}

int altura(No* no){
	if (no == NULL) 
		return 0;
    return no->altura;	
}

int fb(No* no) {
    return altura(no->esquerda) - altura(no->direita);
}

No* rse(AVL* arvore, No* no, int* ops) {
    (*ops)+=1;
    No* pai = no->pai;
    No* direita = no->direita;

    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }
    
    upHeight(no);
    return direita;
}

No* rsd(AVL* arvore, No* no, int* ops) {
    (*ops)+=1;
    No* pai = no->pai;
    No* esquerda = no->esquerda;

    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }
    upHeight(no);
    return esquerda;
}

No* rde(AVL* arvore, No* no, int* ops) {
    (*ops)+=2;
    no->direita = rsd(arvore, no->direita, ops);
    upHeight(no);
    return rse(arvore, no, ops);
}

No* rdd(AVL* arvore, No* no, int* ops) {
    (*ops)+=2;
    no->esquerda = rse(arvore, no->esquerda, ops);
    upHeight(no);
    return rsd(arvore, no, ops);
}

void dfs(No* raiz) {
	if(raiz != NULL) {
		// printf("%d ", raiz->valor);
		dfs(raiz->esquerda);
		dfs(raiz->direita);
	}
}