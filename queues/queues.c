#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "queues.h"

struct no{
    Jogador jogador;
    struct no* prox;
};

struct fila{
    No* ini;
    No* fim;

};

Fila* fila_cria(void){
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

void fila_insere(Fila* f, Jogador j){
    No* novo = (No*) malloc(sizeof(No));
    novo->jogador= j;
    novo->prox = NULL;
    if(f->fim != NULL){
        f->fim->prox = novo;
    }else{
        f->ini = novo;
    }
}

Jogador fila_retira(Fila* f){
    if(fila_vazia(f)){
        printf("fila de turnos vazia.\n");
        exit(1);
    }
    No* t = f->ini;
    Jogador j = t->jogador;
    f->ini = t->prox;
    if(f->ini ==NULL){
        f->fim = NULL;
    }
    free(t);
    return j;
}
int fila_vazia(Fila* f ){
    return (f->ini == NULL);
}

void fila_libera(Fila* f){
    No* q = f->ini;
    while(q != NULL){
        No* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
}