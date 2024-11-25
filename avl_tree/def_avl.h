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
} AVL;

AVL* criarAVL();
int max(int a, int b);
int vazia(AVL* arvore);
No* adicionaNo(No* no, int valor,int*);
No* adicionar(AVL* arvore, int valor,int*);
No* removerNo(No* no, int valor, AVL* av);
No* remover(AVL* arvore, int valor,int*);
No* deleteLeaf(No* no, int esq, AVL* av);
No* deleteSingle(No* no, int esq, AVL* av);
No* criarNoAVL(No* pai, int valor);
No* localizarAVL(No* no, int valor);
void percorrer(No* no, void (*callback)(int));
void visitar(int valor);
void balanceamento(AVL* arvore, No* no, int*);
int altura(No* no);
void upHeight(No* no);
void clear(AVL* arvore);
void clearNode(No* no);
int fb(No* no);
No* rse(AVL* arvore, No* no, int*);
No* rsd(AVL* arvore, No* no, int*);
No* rde(AVL* arvore, No* no, int*);
No* rdd(AVL* arvore, No* no, int*);
void dfs(No* raiz);

#endif