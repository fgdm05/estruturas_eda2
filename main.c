#include "avl_tree/def_test_cases.h"
#include "red_black_tree/def_test_cases.h"
#include <math.h>

// O caso sera calculado i_precisao vezes para obter uma media
void calcularCaso(int n, int i_precisao, int casas) {
    FILE* avl_ins = fopen("avl_ins.csv","a");
    FILE* avl_rem = fopen("avl_rem.csv","a");
    FILE* rb_ins = fopen("rb_ins.csv","a");
    FILE* rb_rem = fopen("rb_rem.csv","a");
    int ops_ins_avl_m = 0;
    int ops_rem_avl_m = 0;
    int ops_ins_rb_m = 0;
    int ops_rem_rb_m = 0;
    for(int i = 0; i < i_precisao; i++) {
        int ops_ins_avl = 0, ops_rem_avl = 0; 
        int ops_ins_rb = 0, ops_rem_rb = 0;       
        heavyTest(n, &ops_ins_avl, &ops_rem_avl);
        heavyTest_rb(n, &ops_ins_rb, &ops_rem_rb);
        ops_ins_avl_m += ops_ins_avl;
        ops_rem_avl_m += ops_rem_avl;
        ops_ins_rb_m += ops_ins_rb;
        ops_rem_rb_m += ops_rem_rb;
    }
    ops_ins_avl_m /= i_precisao;
    ops_rem_avl_m /= i_precisao;
    ops_ins_rb_m /= i_precisao;
    ops_rem_rb_m /= i_precisao;
    fprintf(avl_ins, "%d;%d\n",n,ops_ins_avl_m);
    fprintf(avl_rem, "%d;%d\n",n,ops_rem_avl_m);
    fprintf(rb_ins, "%d;%d\n",n,ops_ins_rb_m);
    fprintf(rb_rem, "%d;%d\n",n,ops_rem_rb_m);
    printf("\nAVL insert %d", ops_ins_avl_m);
    printf("\nAVL remove %d", ops_rem_avl_m);
    printf("\nRB insert %d", ops_ins_rb_m);
    printf("\nRB remove %d", ops_rem_rb_m);
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