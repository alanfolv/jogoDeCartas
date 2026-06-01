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
    f->fim = novo;
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

void jogador_compra_carta(Jogador* j, Cards carta){
    j->mao = lista_insere(j->mao , carta);
    j->qtd_cartas++;
}

void  jogador_mostra_mao(Jogador j){
    printf("\n Mão do jogador %s (%d cartas):\n", j.nome, j.qtd_cartas):

    Lista* p = j.mao;
    int index = 1;
    while(p != NULL){
        Cards c = lista_info(p);
        printf("  [%d] ", index);

        //cores ansi para o texto no terminal, ao mostrar a mao vai mostrar o simbolo e a cor do 
        // texto referente a carta
        switch(c.cor){
            case 1: // Amarelo
                printf("\033[1;33m%d\033[0m\n", c.simbolo);
                break;
            case 2: // Verde
                printf("\033[1;32m%d\033[0m\n", c.simbolo);
                break;
            case 3: // Azul
                printf("\033[1;34m%d\033[0m\n", c.simbolo);
                break;
            case 4: // Vermelho
                printf("\033[1;31m%d\033[0m\n", c.simbolo);
                break;
            default:
                printf("%d\n", c.simbolo); 
        }

        p = lista_prox(p);
        index++
    }
    printf("\n");
}

Cards jogador_remove_carta(Jogador* j, in indice){
    Lista* p = j->mao;
    int cont = 1;
    
    while (p != NULL && cont < indice) {
        p = lista_prox(p);
        cont++;
    }
    
    if (p == NULL) {
        printf("indice invalidoo.\n");
        exit(1);
    }
    
    Cards escolhida = lista_info(p);
    j->mao = lista_remove_elemento(j->mao, escolhida);
    j->qtd_cartas--;
    return escolhida;
}