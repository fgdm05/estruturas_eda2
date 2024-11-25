#ifndef DEF_ARVORE_B
#define DEF_ARVORE_B

#include <vector>
#include <algorithm>

struct No {
	int total;
    std::vector<int> chaves;
	std::vector<No*> filhos;
	No* pai;
	No(No* p, int ordem);
	// ~No();
	void insertKey(int val);
	void insertNode(No* no);
};

struct ArvoreB {
	No* raiz;
	int ordem;
	
	
	ArvoreB(int ordem);
	// ~ArvoreB();
	No* find(int val);
    bool count(int val);
    void overflow(No *tgt);
    void insert(int val);
	void erase(int val);

};




#endif