#include "def_arvore_b.hpp"
#include <iostream>
void printVec(std::vector<int> inp){
    for(auto a : inp)
        std::cout << a << ' ';
    std::cout << std::endl;
}

int main(){
    ArvoreB arv(2);

    for(int i = 0; i < 10; i++){
        int a;
        std::cin >> a;
        arv.insert(a);
    }
    for(int i = 0; i < 10; i++){
        int a;
        std::cin >> a;
        arv.erase(a);
        arv.print();
    }
    std::cout << "STOP";
}