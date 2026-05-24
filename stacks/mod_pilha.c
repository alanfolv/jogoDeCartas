#include <stdio.h>
#include <stdlib.h>
#include "mod_pilha.h"

struct pilha{

    int n; // NUMERO DE ELEMENTOS NA PILHA
    int dim; // DIMENSÃO CORRENTO DO VETOR
    float *vet; // VETOR COM OS ELEMENTOS DA PILHA

};

Pilha* pilha_cria(){

    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->dim = 2; // DIMENSAO INICIAL
    p->n = 0; // INICIALIZAÇAO COM ZERO
    p->vet = (float*)malloc( (p->dim)*sizeof(float));
    return p;
}

void pilha_push (Pilha* p, float elem){

    // SE A PILHA ESTA CHEIA
    if (p->n == p->dim){
    p->dim *= 2; // DOBRA A DIMENSAO DA PILHA
    p->vet = (float*)realloc(p->vet, (p->dim)*sizeof(float) );
    }
    p->vet[p->n] = elem; // INSERE O ELEMENTO NA PROXIMA POSIÇAO LIVRE
    p->n++; // INCREMENTA A QUANTIDADE DE ELEMENTOS NA PILHA
}

float pilha_pop (Pilha* p){
    float elem;
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