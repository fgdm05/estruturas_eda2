#include "def_arvore_b.hpp"
#include <iostream>
void printVec(std::vector<int> inp){
    for(auto a : inp)
        std::cout << a << ' ';
    std::cout << std::endl;
}

int main(){
    ArvoreB arv(1);

    for(int i = 0; i < 15; i++){
        int a;
        std::cin >> a;
        arv.insert(a);
        std::cout << arv.count(a) << std::endl;
    }
    std::cout << "STOP";
}