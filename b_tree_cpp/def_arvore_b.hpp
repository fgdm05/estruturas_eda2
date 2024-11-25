#ifndef DEF_ARVORE_B
#define DEF_ARVORE_B

#include <vector>
#include <algorithm>
#include <iostream>

struct No {
	int total;
    std::vector<int> chaves;
	std::vector<No*> filhos;
	No* pai;
	No(No* p, int ordem);
	// ~No();
	void insertKey(int val);
	void insertNode(No* no);
	void print();
};

struct ArvoreB {
	No* raiz;
	int ordem;
	
	
	ArvoreB(int ordem);
	// ~ArvoreB();
	void print();
	No* find(int val);
    bool count(int val);
    void overflow(No *tgt);
    void insert(int val);
	void erase(No* tgt,int val);
	void erase(int val);
    No *find(int val, No *no);
    bool count(int val, No *nd);
    No *findErasable(No *no, int val);
    void merge(No* lsib, No* f, No* tgt, int i);
	void deleteInternalNode(No* tgt, int i);
};




#endif