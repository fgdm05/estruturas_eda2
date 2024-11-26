#include "def_arvore_b.hpp"
#include <time.h>
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