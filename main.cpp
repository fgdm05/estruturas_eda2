#include "avl_tree/def_test_cases.h"
#include "red_black_tree/def_test_cases.h"
#include "b_tree_cpp/def_test_cases.hpp"
#include <math.h>

void guardarDados(FILE* file, int n, int ops) {
    fprintf(file, "%d;%d\n", n, ops);
}

void somar(int* ops_m, int* ops, int series) {
    for(int j = 0; j < series; j++)
        ops_m[j] += ops[j];
}

void dividir(int* ops_m, int i_precisao, int series) {
    for(int j = 0; j < series; j++)
        ops_m[j] /= i_precisao;
}

// O caso sera calculado i_precisao vezes para obter uma media
void calcularCaso(int n, int i_precisao, int casas) {
    FILE* avl_ins = fopen("avl_ins.csv","a");
    FILE* avl_rem = fopen("avl_rem.csv","a");
    FILE* rb_ins = fopen("rb_ins.csv","a");
    FILE* rb_rem = fopen("rb_rem.csv","a");
    FILE* b_ins_1 = fopen("b_ins_1.csv", "a");
    FILE* b_ins_5 = fopen("b_ins_5.csv", "a");
    FILE* b_ins_10 = fopen("b_ins_10.csv", "a");
    int series = 7;
    int* ops_m = (int*) calloc(series, sizeof(int));

    for(int i = 0; i < i_precisao; i++) {
        int* ops = (int*) calloc(series, sizeof(int));      
        heavyTest(n, ops, ops + 1);
        heavyTest_rb(n, ops + 2, ops + 3);
        ops[4] = rep(1, n);
        ops[5] = rep(5, n);
        ops[6] = rep(10, n);
        somar(ops_m, ops, series);
        free(ops);
    }
    dividir(ops_m, i_precisao, series);
    guardarDados(avl_ins, n, ops_m[0]);
    guardarDados(avl_rem, n, ops_m[1]);
    guardarDados(rb_ins, n, ops_m[2]);
    guardarDados(rb_rem, n, ops_m[3]);
    guardarDados(b_ins_1, n, ops_m[4]);
    guardarDados(b_ins_5, n, ops_m[5]);
    guardarDados(b_ins_10, n, ops_m[6]);
    printf("Insert AVL: %d (operacoes)\n", ops_m[0]);
    printf("Remove AVL: %d (operacoes)\n", ops_m[1]);
    printf("Insert RB: %d (operacoes)\n", ops_m[2]);
    printf("Remove RB: %d (operacoes)\n", ops_m[3]);
    printf("Insert B(1): %d (operacoes)\n", ops_m[4]);
    printf("Insert B(5): %d (operacoes)\n", ops_m[5]);
    printf("Insert B(10): %d (operacoes)\n", ops_m[6]);
    fclose(avl_ins);
    fclose(avl_rem);
    fclose(rb_ins);
    fclose(rb_rem);
    fclose(b_ins_1);
    fclose(b_ins_5);
    fclose(b_ins_10);
}

int main() {
    
    int a = 1, b = (int)1e4; // intervalo [1, 1e4]
    int casos = 100;         // quantidade de casos tera
    int h = b/casos;         // espaco entre casos
    int i_precisao = 10;     // quantidade de repeticoes de cada caso
    int casas = 3;           // quantidade de casas decimais
    
    for(int i = 0; i <= casos; i++) {
        int n = a+h*i;
        printf("\n----------------------------");
        printf("\nCaso nodos = %i\n", n);
        calcularCaso(n, i_precisao, casas);
    }

}