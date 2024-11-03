#include "def_avl.h"
#include <stdio.h>
AVL* criar() {
	AVL* avl = malloc(sizeof(AVL));
	avl->raiz = NULL;
	return avl;
}
No* criarNo(No* pai, int valor) {
	No* no = malloc(sizeof(No));
	no->pai = pai;
	no->valor = valor;
	no->esquerda = no->direita = NULL;
	return no;
}
void adicionarNo(AVL* avl, int valor) {
	printf("\nADICIONANDO NO %d", valor);
	No* aux = avl->raiz;
	if(aux == NULL) {
		printf("\nCASO BASE");
		avl->raiz = criarNo(NULL, valor);
		return;
	}
	
	printf("\nCASO INDUTIVO");
	while(aux != NULL) {
		int aux_valor = aux->valor;
		if(valor < aux_valor) {
			if(aux->esquerda == NULL) {
				printf("\nINSERINDO A ESQUERDA");
				aux->esquerda = criarNo(aux, valor);
				break;
			}
			else {
				printf("\nESQUERDA");
				aux = aux->esquerda;	
			}
		}
		else if(valor > aux_valor) {
			if(aux->direita == NULL) {
				printf("\nINSERINDO A DIREITA");
				aux->direita = criarNo(aux, valor);
				break;
			}
			else {
				printf("\nDIREITA");
				aux = aux->direita;
			}
		}
		else { break; }
	}
}
