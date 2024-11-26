/* B-Tree
 * Author:	Caleb Baker
 * Date:	10/8/17
 * Summary:	A B-Tree data structure. Supports lg(n) time search, insert, and delete.
 * Traduzido Por Max HT
 */


#pragma once


#include <stdlib.h>
#include <utility>
#include <stdio.h>
#include "bTree.h"

using namespace std;


#define NEW_ROOT 2
#define MODIFIED_NOT_ROOT 1
#define NOT_MODIFIED 0


template <typename T>
BTree<T>::BTree(unsigned t, bool (*compare)(T, T), void (*printK)(T)) {
	minDegree = t;
	lessThan = compare;
	raiz = (BNode<T>*) malloc(sizeof(BNode<T>));
	initializeNode(raiz);
	raiz->folha = true;
	printKey = printK;
}


template <typename T>
BTree<T>::~BTree<T>() {
	freeNode(raiz);
}


template <typename T>
void BTree<T>::insert(T k) {

	// eleva raiz caso esteja cheia
	if (raiz->size == 2 * minDegree - 1) {
		BNode<T> *newRoot = (BNode<T>*) malloc(sizeof(BNode<T>));
		initializeNode(newRoot);
		newRoot->folha = false;
		newRoot->filho[0] = raiz;
		raiz = newRoot;
		splitChild(newRoot, 0);
	}

	//Navegação na árvore
	BNode<T> *curr = raiz;
	while (!curr->folha) {

		// Busca sequencial
		int index = curr->size - 1;
		while (index >= 0 && lessThan(k, curr->chaves[index])) {
			index--;
		}
		index++;

		// SPLIT
		if (curr->filho[index]->size == 2 * minDegree - 1) {
			splitChild(curr, index);
			if (lessThan(curr->chaves[index], k)) {
				index++;
			}
		}
		curr = curr->filho[index];
	}

	nodeInsert(curr, k);
}


template <typename T>
T BTree<T>::remove(T k) {
	BNode<T> *curr = raiz;
	while (true) {
		unsigned i = findIndex(curr, k);

		//	Procura valor a ser removido
		if (i < curr->size && !(lessThan(curr->chaves[i], k) || lessThan(k, curr->chaves[i]))) {
			T toReturn = curr->chaves[i];

			// Caso folha -> Deleta
			if (curr->folha) {
				nodeDelete(curr, i);
			}

			// Se não, então troca por sucessor ou une filhos
			else {
				BNode<T> *leftKid = curr->filho[i];
				BNode<T> *rightKid = curr->filho[i + 1];

				// troca por antecessor
				if (leftKid->size >= minDegree) {
					while (!(leftKid->folha)) {
						fixChildSize(leftKid, leftKid->size);
						leftKid = leftKid->filho[leftKid->size];
					}
					curr->chaves[i] = nodeDelete(leftKid, leftKid->size - 1);
				}

				// troca por sucessor
				else if (rightKid->size >= minDegree) {
					while (!(rightKid->folha)) {
						fixChildSize(rightKid, 0);
						rightKid = rightKid->filho[0];
					}
					curr->chaves[i] = nodeDelete(rightKid, 0);
				}

				// União dos filhos
				else {
					mergeChildren(curr, i);
					curr = leftKid;
					continue;
				}
			}
			return toReturn;
		}

		// Caso valor não seja achado, continua navegando
		else {

			// Caso chegue na folha, o valor não existe.
			if (curr->folha) {
				throw (BTREE_EXCEPTION) REMOVE_KEY_NOT_FOUND;
			}

			// Balanceia nodo caso necessario, e continua a descer a árvore
			char result = fixChildSize(curr, i);
			if (result == NEW_ROOT) {
				curr = raiz;
			}
			else {
				curr = curr->filho[findIndex(curr, k)];
			}
		}
	}
}


// Retorna nodo e indice do valor buscado
template <typename T>
pair<BNode<T>*, unsigned> BTree<T>::search(T k) {

	BNode<T> *x = raiz;

	while (true) {

		// Acha indice atual
		unsigned i = findIndex(x, k);

		if (i < x->size && !(lessThan(k, x->chaves[i]) || lessThan(x->chaves[i], k))) {
			return pair<BNode<T>*, unsigned>(x, i);
		}
		else if (x->folha) {
			return pair<BNode<T>*, unsigned>(NULL, 0);
		}
		else {
			x = x->filho[i];
		}
	}
}

// Lança excessão caso indice não exista
template <typename T>
T BTree<T>::searchKey(T k) {
	pair<BNode<T>*, unsigned> node = search(k);
	if (node.first == NULL) {
		throw (BTREE_EXCEPTION) SEARCH_KEY_NOT_FOUND;
	}
	return node.first->chaves[node.second];
}

// Imprime a arvore
template <typename T>
void BTree<T>::print() {
	if (printKey != NULL && raiz != NULL) {
		printf("\n");
		printNode(raiz, 0);
		printf("\n");
	}
}


template <typename T>
void BTree<T>::initializeNode(BNode<T> *x) {
	x->size = 0;
	x->chaves = (T*) malloc((2 * minDegree - 1) * sizeof(T));
	x->filho = (BNode<T>**) malloc(2 * minDegree * sizeof(BNode<T>*));
}

template <typename T>
void BTree<T>::freeNode(BNode<T> *x) {
	if (!x->folha) {
		for (unsigned i = 0; i <= x->size; i++) {
			freeNode(x->filho[i]);
		}
	}
	free(x->filho);
	free(x->chaves);
	free(x);
}

// Busca sequencial
template <typename T>
unsigned BTree<T>::findIndex(BNode<T> *x, T k) {
	unsigned i = 0;
	while (i < x->size && lessThan(x->chaves[i], k)) {
		i++;
	}
	return i;
}


template <typename T>
unsigned BTree<T>::nodeInsert(BNode<T> *x, T k) {
	int index;

	for (index = x->size; index > 0 && lessThan(k, x->chaves[index - 1]); index--) {
		x->chaves[index] = x->chaves[index - 1];
		x->filho[index + 1] = x->filho[index];
	}

	x->filho[index + 1] = x->filho[index];
	x->chaves[index] = k;
	x->size++;

	return index;
}


template <typename T>
T BTree<T>::nodeDelete(BNode<T> *x, unsigned index) {

	T toReturn = x->chaves[index];

	x->size--;
	while (index < x->size) {
		x->chaves[index] = x->chaves[index + 1];
		x->filho[index + 1] = x->filho[index + 2];
		index++;
	}
	return toReturn;
}

// SPLIT
template <typename T>
void BTree<T>::splitChild(BNode<T> *x, int i) {

	BNode<T> *toSplit = x->filho[i];
	BNode<T>* newNode = (BNode<T>*) malloc(sizeof(BNode<T>));;
	initializeNode(newNode);
	newNode->folha = toSplit->folha;
	newNode->size = minDegree - 1;

	// Joga os valores para o nodo novo
	for (unsigned j = 0; j < minDegree - 1; j++) {
		newNode->chaves[j] = toSplit->chaves[j + minDegree];
	}
	if (!toSplit->folha) {
		for (unsigned j = 0; j < minDegree; j++) {
			newNode->filho[j] = toSplit->filho[j + minDegree];
		}
	}
	toSplit->size = minDegree - 1;

	nodeInsert(x, toSplit->chaves[minDegree - 1]);
	x->filho[i + 1] = newNode;
}


// Une nodo com irmão seguinte
template <typename T>
char BTree<T>::mergeChildren(BNode<T> *parent, unsigned i) {

	BNode<T> *leftKid = parent->filho[i];
	BNode<T> *rightKid = parent->filho[i + 1];

	// Recebe valor intermediario do pai
	leftKid->chaves[leftKid->size] = nodeDelete(parent, i);
	unsigned j = ++(leftKid->size);

	// concatena valores do irmão a direita
	for (unsigned k = 0; k < rightKid->size; k++) {
		leftKid->chaves[j + k] = rightKid->chaves[k];
		leftKid->filho[j + k] = rightKid->filho[k];
	}
	leftKid->size += rightKid->size;
	leftKid->filho[leftKid->size] = rightKid->filho[rightKid->size];

	// Limpeza
	free(rightKid->filho);
	free(rightKid->chaves);
	free(rightKid);

	// Caso pai fique vazio, tinha que ser a raiz
	if (parent->size == 0) {
		raiz = leftKid;
		free(parent->filho);
		free(parent->chaves);
		free(parent);
		return NEW_ROOT;
	}

	return MODIFIED_NOT_ROOT;
}


//Garante tamanho minimo para o nodo
template <typename T>
char BTree<T>::fixChildSize(BNode<T> *parent, unsigned index) {
	BNode<T> *kid = parent->filho[index];

	if (kid->size < minDegree) {

		// Tenta puxar da esquerda
		if (index != 0 && parent->filho[index - 1]->size >= minDegree) {
			BNode<T> *leftKid = parent->filho[index - 1];

			for (unsigned i = nodeInsert(kid, parent->chaves[index - 1]); i != 0; i--) {
				kid->filho[i] = kid->filho[i - 1];
			}
			kid->filho[0] = leftKid->filho[leftKid->size];
			parent->chaves[index - 1] = nodeDelete(leftKid, leftKid->size - 1);
		}

		// tenta puxar da direita
		else if (index != parent->size && parent->filho[index + 1]->size >= minDegree) {
			BNode<T> *rightKid = parent->filho[index + 1];
			
			nodeInsert(kid, parent->chaves[index]);
			kid->filho[kid->size] = rightKid->filho[0];
			rightKid->filho[0] = rightKid->filho[1];
			
			parent->chaves[index] = nodeDelete(rightKid, 0);
		}

		// Caso falhe, nodos tem tamanho pequeno o suficiente para unir.
		else if (index != 0) {
			return mergeChildren(parent, index - 1);
		}
		else {
			return mergeChildren(parent, index);
		}
		return MODIFIED_NOT_ROOT;
	}

	// Tudo OK
	return NOT_MODIFIED;
}

