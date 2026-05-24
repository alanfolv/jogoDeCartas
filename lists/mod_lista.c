#include <stdio.h>
#include <stdlib.h>
#include "mod_lista.h"



struct lista{
    Cards info;
    struct lista* prox;
};

Lista* lista_cria(){
    return NULL;
}

Lista* lista_insere(Lista* l,Cards card){
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    if(novo == NULL){
        printf("\n Memória não Alocada");
        exit(1);
    }
    novo->info = card;
    novo->prox = l;
    return novo;
}
void lista_imprime(Lista* l){
    Lista* p;
    for(p = l; p != NULL; p = p->prox){
        printf("info: %d\n",p->info);
    }
}
Lista* lista_busca(Lista* l, Cards elem){
    Lista* p;
    for (p = l; p != NULL; p = p->prox){
        if(p->info.cor == elem.cor && p->info.simbolo == elem.simbolo){
            return p;
        }
    }
    return NULL;
}
void lista_libera(Lista* l){
    Lista* p = l;
    while(p != NULL){
        Lista* t = p->prox;
        free(p);
        p = t;
    }
}