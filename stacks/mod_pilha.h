#ifndef MOD_PILHA_H
#define MOD_PILHA_H

typedef struct pilha Pilha;
Pilha* pilha_cria (void );
void pilha_push (Pilha* p, float v); // as funções push e pop inserem e retiram
float pilha_pop (Pilha* p);
int pilha_vazia (Pilha* p); // a função vazia informa se a pilha está ou não vazia
// a função libera destrói a pilha, liberando toda a memória usada pela estrutura
void pilha_libera (Pilha* p);

#endif