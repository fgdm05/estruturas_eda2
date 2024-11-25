#include "avl_tree/def_test_cases.h"
#include "red_black_tree/def_test_cases.h"
#include <math.h>

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
    int series = 4;
    int* ops_m = (int*) calloc(series, sizeof(int));

    for(int i = 0; i < i_precisao; i++) {
        int* ops = (int*) calloc(series, sizeof(int));      
        heavyTest(n, ops, ops + 1);
        heavyTest_rb(n, ops + 2, ops + 3);
        somar(ops_m, ops, series);
    }
    dividir(ops_m, i_precisao, series);
    fprintf(avl_ins, "%d;%d\n",n, ops_m[0]);
    fprintf(avl_rem, "%d;%d\n",n,ops_m[1]);
    fprintf(rb_ins, "%d;%d\n",n,ops_m[2]);
    fprintf(rb_rem, "%d;%d\n",n,ops_m[3]);
    printf("\nAVL insert %d", ops_m[0]);
    printf("\nAVL remove %d", ops_m[1]);
    printf("\nRB insert %d", ops_m[2]);
    printf("\nRB remove %d", ops_m[3]);
    fclose(avl_ins);
    fclose(avl_rem);
    fclose(rb_ins);
    fclose(rb_rem);
}
// intervalo 1~1e4
int main() {
    
    int a = 1, b = (int)1e4; // intervalo [1, 1e4]
    
    int casos = 100;         // quantidade de casos tera
    int i_precisao = 10;     // quantidade de repeticoes de cada caso
    int casas = 3;           // quantidade de casas decimais
    
    int h = b/casos;
    for(int i = 0; i <= casos; i++) {
        int n = a+h*i;
        printf("\n----------------------------\nCaso nodos = %i\n", n);
        calcularCaso(n, i_precisao, casas);
    }

}