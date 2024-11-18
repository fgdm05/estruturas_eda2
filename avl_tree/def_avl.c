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

int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

No* adicionarNo(No* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == NULL) {
            printf("Adicionando %d\n",valor);
            No* novo = criarNo(no, valor);
            no->direita = novo;
				
            return novo;
        } else {
            return adicionarNo(no->direita, valor);
        }
    } else {
        if (no->esquerda == NULL) {
            printf("Adicionando %d\n",valor);
            No* novo = criarNo(no, valor);
            no->esquerda = novo;
			
            return novo;
        } else {
            return adicionarNo(no->esquerda, valor);
        }
    }
}

No* adicionar(Arvore* arvore, int valor) {
    if (vazia(arvore)) {
        printf("Adicionando %d\n",valor);
        arvore->raiz = criarNo(NULL, valor);
        return arvore->raiz;
    } else {
        No* no = adicionarNo(arvore->raiz, valor);
        balanceamento(arvore, no->pai);
        return no;
    }
}

No* removerNo(No* no, int valor) {
    if(valor < no->valor) {
        if(no->esquerda == NULL) {
            printf("\nValor inexistente");
            return NULL;
        } else {
            return removerNo(no->esquerda, valor);
        }
    } else if(valor > no->valor) {
        if(no->direita == NULL) {
            printf("\nValor inexistente");
            return NULL;
        } else {
            return removerNo(no->direita, valor);
        }
    } else {
        // Destruir no
        // caso tenha filhos, colocar um como pai
        No* pai = no->pai;
        if(pai != NULL) {
            if(valor < no-pai) {
                // filho a esquerda
                if(no->esquerda != NULL) {
                    no->esquerda->pai = pai;
                    pai->esquerda = no->esquerda;
                } else if(no->direita != NULL) {
                    no->direita->pai = pai;
                    pai->esquerda = no->direita;
                } else {
                    pai->esquerda = NULL;
                }
            } else {
                // filho a direita
                if(no->esquerda != NULL) {
                    no->esquerda->pai = pai;
                    pai->direita = no->esquerda;
                } else if(no->direita != NULL) {
                    no->direita->pai = pai;
                    pai->direita = no->direita;
                } else {
                    pai->direita = NULL;
                }    
            }
        }
    }
}

No* remover(Arvore* arvore, int valor) {
    if(vazia(arvore)) {
        printf("\nArvore vazia");
        return NULL;
    } else {
        No* no = removerNo(arvore->raiz, valor);
        printf("\nBALANCEAR");
        balanceamento(arvore, no);
    }
}

No* criarNo(No* pai, int valor) {
    No* no = malloc(sizeof(No));
    no->valor = valor;
    no->pai = pai;
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

        no->altura = (altura(no->esquerda) > altura(no->direita)
			? altura(no->esquerda) 
			: altura(no->direita)) + 1;	

        if (fator > 1) { // arvore mais profunda para a esquerda
            printf("\nMAIS PROFUNDA A ESQUERDA");
            if (fb(no->esquerda) > 0) {
                printf(" RSD(%d)\n",no->valor);
                rsd(arvore, no); 
            } else {
                printf(" RDD(%d)\n",no->valor);
                rdd(arvore, no); 
            }
        } else if (fator < -1) { // arvore mais profunda a direita
            printf("\nMAIS PROFUNDA A DIREITA");
            if (fb(no->direita) < 0) {
                printf(" RSE(%d)\n",no->valor);
                rse(arvore, no); 
            } else {
                printf(" RDE(%d)\n",no->valor);
                rde(arvore, no);
            }
        }
        no = no->pai; 
    }
}

int altura(No* no){
	if (no == NULL) {
		return 0;
	}
	
    int esquerda = altura(no->esquerda);
    int direita = altura(no->direita);
    
    return esquerda > direita ? esquerda + 1 : direita + 1;
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

    return esquerda;
}

No* rde(Arvore* arvore, No* no) {
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

No* rdd(Arvore* arvore, No* no) {
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
}

void dfs(No* raiz) {
	if(raiz != NULL) {
		printf("%d ", raiz->valor);
		dfs(raiz->esquerda);
		dfs(raiz->direita);
	}
}