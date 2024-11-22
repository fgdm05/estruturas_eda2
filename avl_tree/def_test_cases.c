#include "def_test_cases.h"

void test_case_rsd() {
    printf("\nRotacao simples a direita ----------\n");
    Arvore* a0 = criar();
    adicionar(a0, 3);
    adicionar(a0, 2);
    adicionar(a0, 1);
    dfs(a0->raiz);
    printf("\n\n");
}
void test_case_rse() {
    printf("\nRotacao simples a esquerda -----------\n");
    Arvore* a2 = criar();
    adicionar(a2, 1);
    adicionar(a2, 2);
    adicionar(a2, 3);
    dfs(a2->raiz);
    printf("\n\n");
}
void test_case_rdd() {
    printf("\nRotacao dupla a direita -----------\n");
    Arvore* a1 = criar();
    adicionar(a1, 3);
    adicionar(a1, 1);
    adicionar(a1, 2);
    dfs(a1->raiz);
    printf("\n\n");

}
void test_case_rde() {
    printf("\nRotacao dupla a esquerda ------------\n");
    Arvore* a = criar();
    adicionar(a, 1);
    adicionar(a, 3);
    adicionar(a, 2);
    dfs(a->raiz);
    printf("\n\n");
}

void test_case_2a() {
    Arvore* a = criar();
    adicionar(a, 20);
    adicionar(a, 4);
    adicionar(a, 26);
    adicionar(a, 3);
    adicionar(a, 9);
    adicionar(a, 15);
    dfs(a->raiz);
}

void test_case_3a() {
    Arvore* a = criar();
    adicionar(a, 20);
    adicionar(a, 4);
    adicionar(a, 26);
    adicionar(a, 3);
    adicionar(a, 9);
    adicionar(a, 21);
    adicionar(a, 30);
    adicionar(a, 2);
    adicionar(a, 7);
    adicionar(a, 11);
    adicionar(a, 15);
    dfs(a->raiz);
}

void test_case_3b() {
    Arvore* a = criar();
    adicionar(a, 4);
    adicionar(a, 26);
    adicionar(a, 20);
    adicionar(a, 3);
    adicionar(a, 9);
    adicionar(a, 21);
    adicionar(a, 30);
    adicionar(a, 2);
    adicionar(a, 7);
    adicionar(a, 11);
    adicionar(a, 8);
    dfs(a->raiz);
}

void heavyTest(int n){
    srand(time(NULL));
    Arvore *a0 = criar();
    int v[n];
    for(int i = 0; i < n; i++){
        v[i] = rand() % ((int)1e9);
        adicionar(a0,v[i]);
    }
    printf("%i\n",altura(a0->raiz));
    for(int i = 0; i < n; i++){
        int j = rand()%n;
        remover(a0,v[j]);
    }
    
    printf("%i\n",altura(a0->raiz));
    clear(a0);
    return;
}

void test_case_a() {
    printf("\nTESTE A\n");
    Arvore* a = criar();
    
    // RSE(10)
    adicionar(a, 10);
    adicionar(a, 20);
    adicionar(a, 30);

    // RSD(10)
    adicionar(a, 5);
    adicionar(a, 3);
    
    // RDD(20)
    adicionar(a, 9);
}