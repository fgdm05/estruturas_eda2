
#include "def_arvore_b.hpp"

ArvoreB::ArvoreB(int ordem)
{
    ArvoreB::ordem = ordem;
    raiz = new No(NULL, ordem);
    ops = 0;
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
    return find(val,raiz);
}

No* ArvoreB::find(int val, No* no){
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

bool ArvoreB::count(int val, No* nd){
    auto t = find(val,nd);
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
    ops++;
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
    ops+=cv.size()-pos;
    if (cv.size() == 2 * ordem+1)
        overflow(tgt); // Splita nodo
    
}



No* ArvoreB::findErasable(No* no,int val){
    if(no->chaves.empty()) return NULL;
    auto prev = no;
    while (no->chaves.size()>ordem || no==raiz)
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


void ArvoreB::deleteInternalNode(No* tgt, int i){
    auto lf = tgt->filhos[i], rt = tgt->filhos[i+1];
    int val = tgt->chaves[i];
    if(lf->chaves.size()>ordem){
        No* f = lf;
        while(*f->filhos.rbegin()!=NULL) f = *f->filhos.rbegin(); // Predecessor
        int precc = *f->chaves.rbegin(); // Predecessor
        tgt->chaves[i] = precc;
        erase(lf,precc);
        

    }else if(rt->chaves.size()>ordem){
        No* f = rt;
        while(*f->filhos.begin()!=NULL) f = *f->filhos.begin(); // Sucessor
        int succ = *f->chaves.begin(); // Sucessor
        tgt->chaves[i]=succ;
        erase(rt,succ);
    }else{
        // Merge dos filhos
        lf->chaves.emplace_back(tgt->chaves[i]);
        lf->chaves.insert(lf->chaves.end(),rt->chaves.begin(),rt->chaves.end());
        lf->filhos.insert(lf->filhos.end(),rt->filhos.begin(),rt->filhos.end());
        for(auto nd : rt->filhos)
            if(nd!=NULL) nd->pai = lf;
        tgt->chaves.erase(tgt->chaves.begin()+i);
        tgt->filhos.erase(tgt->filhos.begin()+i+1);
        delete(rt);
        erase(raiz,val);
    }
}



void ArvoreB::erase(No* tgt,int val){
    if(!count(val,tgt)) return;
    tgt = findErasable(tgt,val);
    auto it = std::lower_bound(tgt->chaves.begin(),tgt->chaves.end(),val);
    int i = it-tgt->chaves.begin();
    if(tgt->filhos[0]==NULL){ // Implica que é uma folha 
        tgt->chaves.erase(it);
        tgt->filhos.pop_back();
        return;
    }
    // Não é uma folha, logo é um nodo interno.
    if(val==*it){
        deleteInternalNode(tgt,i);
        return;
    }
    
    // Valor não esta no nodo
    No* f = tgt->filhos[i];
    if(i-1>=0 && tgt->filhos[i-1]->chaves.size()>ordem){
        No* ls = tgt->filhos[i-1];
        while(*ls->filhos.rbegin()!=NULL) ls = *ls->filhos.rbegin();
        int precc = *ls->chaves.rbegin(); // LS necessariamente é uma folha
        f->insertKey(tgt->chaves[i]);
        tgt->chaves[i]=precc;
        erase(ls,precc);
        erase(tgt,val);
    }
    else if(i+1<tgt->filhos.size() && tgt->filhos[i+1]->chaves.size()>ordem){
        No* rs = tgt->filhos[i+1];
        while(*rs->filhos.begin()!=NULL) rs = *rs->filhos.begin();
        int succ = *rs->chaves.begin();
        f->insertKey(tgt->chaves[i]);
        tgt->chaves[i]=succ;
        erase(rs,succ);
        erase(tgt,val);
    }
    else{
        No* sib;
        if(i-1<0){
            sib = tgt->filhos[i+1];
            merge(f,sib,tgt,i);
        }
        else{ 
            sib = tgt->filhos[i-1];
            merge(sib,f,tgt,i-1);
        }
        erase(raiz,val);
    }


}

void ArvoreB::merge(No* lsib, No* f, No* tgt, int i){
    // v[i] é o primeiro valor >= a val.
    lsib->chaves.emplace_back(tgt->chaves[i]); 
    tgt->chaves.erase(tgt->chaves.begin()+i);
    tgt->filhos.erase(tgt->filhos.begin()+i);
    lsib->chaves.insert(lsib->chaves.end(),f->chaves.begin(),f->chaves.end());
    for(auto nd : f->filhos)
        if(nd!=NULL) nd->pai=lsib;
    lsib->filhos.insert(lsib->filhos.end(),f->filhos.begin(),f->filhos.end());
    tgt->filhos[i]=lsib;
    delete(f);
    if(tgt->chaves.empty()){
        lsib->pai=tgt->pai;
        if(lsib->pai==NULL) raiz = lsib;
        else{
            auto p = lsib->pai;
            int j = std::lower_bound(p->chaves.begin(),p->chaves.end(),lsib->chaves[0]) - p->chaves.begin();
            p->filhos[i]=lsib;
        } 
        delete(tgt);
    }
}

void ArvoreB::erase(int val){
    erase(raiz,val);
}

void No::print(){
    std::cout << '[';
    for(auto a : chaves) std::cout << a << ' ';
    std::cout << "]\n";
    for(auto a : filhos) if(a!=NULL) a->print();
}

void ArvoreB::print(){
    // Imprime preordem
    raiz->print();
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