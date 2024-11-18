#include "def_arvore_b.h"

No* criaNo(ArvoreB* arvore) {
    int max = arvore->ordem * 2;
    No* no = malloc(sizeof(No));

    no->pai = NULL;

    no->chaves = malloc(sizeof(int) * (max + 1));
    no->filhos = malloc(sizeof(No) * (max + 2));
    no->total = 0;

    int i;
    for(i = 0; i < max + 2; i++)
        no->filhos[i] = NULL;
    return no;
}

ArvoreB* criaArvore(int ordem) {
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = criaNo(a);
    return a;
}

void visita(int valor) {
    print("%d ", valor);
}

void percorreArvore(No* no, void (visita)(int chave)) {
    if(no != NULL) {
        int i;
        for(i = 0; i < no->total; i++) {
            percorreArvore(no->filhos[i], visita);
            visita(no->chaves[i]);
        }
    }
}

int localizaChave(ArvoreB* arvore, int chave) {
    No* no = arvore->raiz;
    while(no!=NULL) {
        int i = pesquisaBinaria(no, chave);
        if(i < no->total && no->chaves[i] == chave) {
            return 1;
        } else {
            no = no->filhos[i];
        }
    }
    return 0;
}