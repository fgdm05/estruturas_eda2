#include "def_arvore_b.hpp"
#include <iostream>
#include <time.h>
void printVec(std::vector<int> inp){
    for(auto a : inp)
        std::cout << a << ' ';
    std::cout << std::endl;
}

int rep(int ordem, int n) {
    ArvoreB arv(ordem);
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        int a = rand() % n;
        arv.insert(a);
        //std::cout << arv.count(a) << std::endl;
    }
    return arv.ops;
}


void test(int ordem, int n, char* file) {
    FILE* f = fopen(file, "a");
    int ops_m = 0;
    int i_rep = 10;
    for(int i = 0; i < i_rep; i++) {
        ops_m+=rep(ordem, n);
    }
    ops_m /= i_rep;
    fprintf(f, "%d;%d\n", n, ops_m);
    
    std::cout << "STOP";
}



int main(){
    int a = 1, b = (int)1e4;
    int it = 100;
    int h = b/it;
    for(int i = 0; i <= it; i++) {
        test(1, a+h*i, "ins_b_1.csv");
    }
    for(int i = 0; i <= it; i++) {
        test(5, a+h*i, "ins_b_5.csv");
    }
    for(int i = 0; i <= it; i++) {
        test(10, a+h*i, "ins_b_10.csv");
    }    
        
}