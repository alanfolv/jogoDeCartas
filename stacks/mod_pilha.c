#include <stdio.h>
#include <stdlib.h>
#include "mod_pilha.h"
#include "../lists/mod_lista.h"



struct pilha{

    int n; // NUMERO DE ELEMENTOS NA PILHA
    int dim; // DIMENSÃO CORRENTO DO VETOR
    Cards *vet; // VETOR COM OS ELEMENTOS DA PILHA

};

Pilha* pilha_cria(){

    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->dim = 2; // DIMENSAO INICIAL
    p->n = 0; // INICIALIZAÇAO COM ZERO
    p->vet = (Cards*)malloc( (p->dim)*sizeof(Cards));
    return p;
}

void pilha_imprime(int size,Pilha* stackCards){
    for(int i = 0; i < size; i++){
        
        printf("Carta %d\nCor:%d\nNumero:%d\n",i,stackCards->vet[i].cor, stackCards->vet[i].simbolo);
        
    }
}

void pilha_push (Pilha* p, Cards elem){

    // SE A PILHA ESTA CHEIA
    if (p->n == p->dim){
    p->dim *= 2; // DOBRA A DIMENSAO DA PILHA
    p->vet = (Cards*)realloc(p->vet, (p->dim)*sizeof(Cards) );
    }
    p->vet[p->n] = elem; // INSERE O ELEMENTO NA PROXIMA POSIÇAO LIVRE
    p->n++; // INCREMENTA A QUANTIDADE DE ELEMENTOS NA PILHA
}

Cards pilha_pop (Pilha* p){
    Cards elem;
    if (pilha_vazia(p)) {
    printf("Pilha vazia.\n");
    exit(1);
    }
    elem = p->vet [p->n-1]; // RETIRA O ELEMENTO DO TOPO
    p->n--; // DECREMENTA A QUANTIDADE DE ELEMENTOS DA PILHA
    return elem;
}

int pilha_vazia (Pilha* p) {
    return (p->n == 0);
}

void pilha_libera (Pilha* p) {
    free(p->vet); // LIBERA O VETOR DE ELEMENTOS
    free(p); // LIBERA A ESTRUTURA PILHA
}