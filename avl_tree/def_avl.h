#ifndef DEF_AVL
#define DEF_AVL


typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
    int altura;
} No;

typedef struct arvore {
    struct no* raiz;
} Arvore;

Arvore* criar();
int max(int a, int b);
int vazia(Arvore* arvore);
No* adicionaNo(No* no, int valor);
No* adicionar(Arvore* arvore, int valor);
No* removerNo(No* no, int valor, Arvore* av);
No* remover(Arvore* arvore, int valor);
No* deleteLeaf(No* no, int esq, Arvore* av);
No* deleteSingle(No* no, int esq, Arvore* av);
No* criarNo(No* pai, int valor);
No* localizar(No* no, int valor);
void percorrer(No* no, void (*callback)(int));
void visitar(int valor);
void balanceamento(Arvore* arvore, No* no);
int altura(No* no);
int fb(No* no);
No* rse(Arvore* arvore, No* no);
No* rsd(Arvore* arvore, No* no);
No* rde(Arvore* arvore, No* no);
No* rdd(Arvore* arvore, No* no);
void dfs(No* raiz);

#endif