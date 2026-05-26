#ifndef MOD_PILHA_H
#define MOD_PILHA_H
#include "../lists/mod_lista.h"

typedef struct pilha Pilha;
void pilha_imprime(int size,Pilha* stackCards);
Pilha* pilha_cria ();
void pilha_push (Pilha* p, Cards v); // as funções push e pop inserem e retiram
Cards pilha_pop (Pilha* p);
int pilha_vazia (Pilha* p); // a função vazia informa se a pilha está ou não vazia
// a função libera destrói a pilha, liberando toda a memória usada pela estrutura
void pilha_libera (Pilha* p);

#endif