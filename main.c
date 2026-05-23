#include <stdlib.h>
#include <stdio.h>
#include "lists/mod_lista.h"
int main(){

    Lista* l = lista_cria();
    l = lista_insere(l,23);
    l = lista_insere(l,45);
    l = lista_insere(l,8);
    lista_imprime(l);
    Lista* achou = lista_busca(l,45);
    if(achou!=NULL){
        printf("\n O Valor foi Encontrado na lista");
    }else{
        printf("\n O valor não encontrado na lista ");
    }
    lista_libera(l);



    return 0;
}

