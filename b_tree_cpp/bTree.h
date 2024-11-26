/* B-Tree
 * Author:	Caleb Baker
 * Date:	10/8/17
 * Summary:	A B-Tree data structure.
 *			Most standard operations run in O(lg(n)) time.
 *			Uses O(n) memory.
 *			Where n is the number of items in the tree.
 */


#pragma once

#include <utility>

#define NULL 0
#define SEARCH_KEY_NOT_FOUND 's'
#define REMOVE_KEY_NOT_FOUND 'r'


// struct for representing nodes of a b tree
template <typename T>
struct BNode {
	BNode<T> **filho;	// Array of pointers to children.
	T *chaves;				// Array of keys.
	unsigned size;		// Number of keys.
	bool folha;			// Whether the node is a leaf.
};


typedef char BTREE_EXCEPTION;


// class for representing b trees.
template <typename T>
class BTree {
public:
	// Construtor
	// Recebe grau minimo
	BTree(unsigned, bool (*)(T, T), void (*)(T) = NULL);

	// Destrutor.
	~BTree<T>();

	void insert(T);
	T remove(T);
	std::pair<BNode<T>*, unsigned> search(T);
	T searchKey(T);
	void print();

private:

	void initializeNode(BNode<T>*);
	//Função do destrutor
	void freeNode(BNode<T>*);
	unsigned findIndex(BNode<T>*, T);
	unsigned nodeInsert(BNode<T>*, T);
	T nodeDelete(BNode<T>*, unsigned);
	// Divide nodos durante inserção
	void splitChild(BNode<T>*, int);
	// Junta nodos durante remoção
	char mergeChildren(BNode<T>*, unsigned);
	// Conserta nodos para poder realizar remoção
	char fixChildSize(BNode<T>*, unsigned);
	// Função auxiliar de Print
	void printNode(BNode<T>*, unsigned);
	
	BNode<T> *raiz;

	// Função base de comparação
	bool (*lessThan)(T, T);

	// Chama função de impressão para seu tipo
	void (*printKey)(T);

	//Ordem da árvore
	unsigned minDegree;
};


#include "bTree.cpp"
