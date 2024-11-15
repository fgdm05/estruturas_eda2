#ifndef PERCORRER_LIB
#define PERCORRER_LIB
#include "def_rubro_negra.h"
void percorrerProfundidadeInOrder(Arvore* arvore, No* no, void (*callback)(int));
void percorrerProfundidadePreOrder(Arvore* arvore, No* no, void (*callback)(int));
void percorrerProfundidadePosOrder(Arvore* arvore, No* no, void (callback)(int));
#endif