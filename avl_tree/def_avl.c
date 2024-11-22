#include <stdlib.h>
#include <stdio.h>
#include "def_avl.h"

void balanceamento(Arvore*, No*);
int altura(No*);
int fb(No*);
No* rsd(Arvore*, No*);
No* rse(Arvore*, No*);
No* rdd(Arvore*, No*);
No* rde(Arvore*, No*);
No* criarNo(No*, int);

Arvore* criar() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    return arvore;
}

void clear(Arvore* arvore){
    clearNode(arvore->raiz);
    free(arvore);
}

void clearNode(No* no){
    if(no==NULL) return;
    clearNode(no->esquerda);
    clearNode(no->direita);
    free(no);
}


int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}
int max(int a,int b){
    if(a>b) return a;
    return b;
}
No* adicionarNo(No* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == NULL) {
            // printf("Adicionando %d\n",valor);
            No* novo = criarNo(no, valor);
            no->direita = novo;
            return novo;
        } else {
            return adicionarNo(no->direita, valor);
        }
    } else if (valor < no->valor){
        if (no->esquerda == NULL) {
            // printf("Adicionando %d\n",valor);
            No* novo = criarNo(no, valor);
            no->esquerda = novo;
            return novo;
        } else {
            return adicionarNo(no->esquerda, valor); 
        }
    }else{
        // printf("Valor ja existe!\n");
        return NULL;
    }
}

No* adicionar(Arvore* arvore, int valor) {
    if (vazia(arvore)) {
        // printf("Adicionando %d\n",valor);
        arvore->raiz = criarNo(NULL, valor);
        return arvore->raiz;
    } else {
        No* no = adicionarNo(arvore->raiz, valor);
        upHeight(no);
        balanceamento(arvore, no);
        return no;
    }
}

No* removerNo(No* no, int valor, Arvore* av) {
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

No* deleteLeaf(No* no, int esq, Arvore* av){
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

No* deleteSingle(No* no, int esq, Arvore* av){
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


No* remover(Arvore* arvore, int valor) {
    // printf("\nRemovendo %i\n",valor);
    if(vazia(arvore)) {
        // printf("\nArvore vazia");
        return NULL;
    } else {
        No* no = removerNo(arvore->raiz, valor,arvore);
        // printf("\nBALANCEAR");
        upHeight(no);
        balanceamento(arvore, no);
    }
}

No* criarNo(No* pai, int valor) {
    No* no = malloc(sizeof(No));
    no->valor = valor;
    no->pai = pai;
    no->altura=1;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

No* localizar(No* no, int valor) {
    if (no->valor == valor) {
        return no;
    } else {
        if (valor < no->valor) {
            if (no->esquerda != NULL) {
                return localizar(no->esquerda, valor);
            }
        } else {
            if (no->direita != NULL) {
                return localizar(no->direita, valor);
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

void balanceamento(Arvore* arvore, No* no) {
    while (no != NULL) {
        int fator = fb(no);
        if (fator > 1) { // arvore mais profunda para a esquerda
            // printf("\nMAIS PROFUNDA A ESQUERDA");
            if (fb(no->esquerda) > 0) {
                // printf(" RSD(%d)\n",no->valor);
                rsd(arvore, no); 
            } else {
                // printf(" RDD(%d)\n",no->valor);
                rdd(arvore, no); 
            }
        } else if (fator < -1) { // arvore mais profunda a direita
            // printf("\nMAIS PROFUNDA A DIREITA");
            if (fb(no->direita) < 0) {
                // printf(" RSE(%d)\n",no->valor);
                rse(arvore, no); 
            } else {
                // printf(" RDE(%d)\n",no->valor);
                rde(arvore, no);
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

No* rse(Arvore* arvore, No* no) {
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

No* rsd(Arvore* arvore, No* no) {
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

No* rde(Arvore* arvore, No* no) {
    no->direita = rsd(arvore, no->direita);
    upHeight(no);
    return rse(arvore, no);
}

No* rdd(Arvore* arvore, No* no) {
    no->esquerda = rse(arvore, no->esquerda);
    upHeight(no);
    return rsd(arvore, no);
}

void dfs(No* raiz) {
	if(raiz != NULL) {
		// printf("%d ", raiz->valor);
		dfs(raiz->esquerda);
		dfs(raiz->direita);
	}
}