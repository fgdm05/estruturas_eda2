
#include "def_arvore_b.hpp"

ArvoreB::ArvoreB(int ordem)
{
    ArvoreB::ordem = ordem;
    raiz = new No(NULL, ordem);
}

No::No(No *p, int ordem)
{
    pai = p;
    total = 0;
    chaves.reserve(2 * ordem + 1);
    filhos.reserve(2 * ordem + 2);
}

No *ArvoreB::find(int val)
{
    No *no = raiz;
    if(no->chaves.empty()) return no;
    auto prev = no;
    while (no != NULL)
    {
        auto &cv = no->chaves;
        int i = std::lower_bound(cv.begin(), cv.end(), val) - cv.begin();
        if (i < cv.size() && cv[i] == val)
            return no;
        prev = no;
        no = no->filhos[i];
    }
    return prev;
}

bool ArvoreB::count(int val){
    auto t = find(val);
    return std::binary_search(t->chaves.begin(),t->chaves.end(),val);
}

void No::insertKey(int val)
{
    auto it = std::lower_bound(chaves.begin(), chaves.end(), val);
    int i = it - chaves.begin();
    if (filhos.empty())
        filhos.push_back(NULL);
    else
        filhos[i] = NULL;
    filhos.insert(filhos.begin() + i, NULL);
    chaves.insert(it, val);
}

void No::insertNode(No *no)
{ // Substitui intervalo por no binario
    auto it = std::upper_bound(chaves.begin(), chaves.end(), no->chaves[0]);
    int i = it - chaves.begin(); // Intervalo de chaves
    no->filhos[0]->pai = this;
    no->filhos[1]->pai = this;
    filhos[i] = no->filhos[1];
    filhos.insert(filhos.begin() + i, no->filhos[0]);
    chaves.insert(it, no->chaves[0]);
    free(no);
}

void ArvoreB::overflow(No *tgt)
{
    auto& cv = tgt->chaves;
    auto p = tgt->pai;
    int upVal = cv[cv.size() / 2];
    No *up = new No(NULL, ordem);
    No *leftChild = new No(up, ordem), *rightChild = new No(up, ordem);
    
    up->insertKey(upVal);
    up->filhos[0] = leftChild;
    up->filhos[1] = rightChild;
    auto fv = tgt->filhos;
    
    leftChild->chaves.assign(cv.begin(),cv.begin()+cv.size()/2);
    rightChild->chaves.assign(cv.begin()+cv.size()/2+1,cv.end());
    
    leftChild->filhos.assign(fv.begin(),fv.begin()+(fv.size()+1)/2);
    rightChild->filhos.assign(fv.begin()+(fv.size()+1)/2,fv.end());

    for(auto nd : leftChild->filhos)
        if(nd!=NULL) nd->pai = leftChild;
    for(auto nd : rightChild->filhos)
        if(nd!=NULL) nd->pai = rightChild;
    

    if (p == NULL) raiz = up;
    else p->insertNode(up);
    if(p!=NULL && p->chaves.size()==2*ordem+1)
        overflow(p);
}

void ArvoreB::insert(int val)
{
    auto tgt = find(val);
    auto &cv = tgt->chaves;
    int pos = std::lower_bound(cv.begin(), cv.end(), val) - cv.begin();
    if (pos < cv.size() && val == cv[pos])
        return; // Valor já existe
    (*tgt).insertKey(val);
    
    if (cv.size() == 2 * ordem+1)
        overflow(tgt); // Splita nodo
    
}



void ArvoreB::erase(int val){

}

// No::~No(){
//     for(auto t : filhos)
//         if(t!=NULL) t->~No();
//     free(this);
// }

// ArvoreB::~ArvoreB(){
//     raiz->~No();
//     free(this);   
// }