#ifndef MOD_LISTA_H
#define MOD_LISTA_H

typedef struct lista Lista;

Lista* lista_cria();

Lista* lista_insere(Lista* l, int elem);

void lista_imprime(Lista* l);

int lista_vazia(Lista* l );

Lista* lista_busca(Lista* l, int elem);

void lista_libera(Lista* l );

#endif