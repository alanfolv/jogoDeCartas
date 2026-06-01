#ifndef MOD_LISTA_H
#define MOD_LISTA_H


typedef struct{
    int cor;
    int simbolo;
    //1 - Amarelo 
    //2 - Verde
    //3 - Azul
    //4 - Vermelho
    // O simbolo varia de 1 até 9 e os caracteres especiais 
}Cards;
typedef struct lista Lista;

Cards lista_info(Lista* l);

Lista* lista_prox(Lista* l);

Lista* lista_cria();

Lista* lista_insere(Lista* l, Cards card);

void lista_imprime(Lista* l);

int lista_vazia(Lista* l );

Lista* lista_busca(Lista* l, Cards elem);

void lista_libera(Lista* l );

Lista* lista_remove_elemento(Lista*l, Cards elem);

#endif