#ifndef MOD_LISTA_H
#define MOD_LISTA_H

typedef struct lista Lista;
typedef struct{
    int cor;
    int simbolo;
    //1 - Amarelo 
    //2 - Verde
    //3 - Azul
    //4 - Vermelho
    // O simbolo varia de 1 até 9 e os caracteres especiais 
}Cards;


Lista* lista_cria();

Lista* lista_insere(Lista* l, Cards card);

void lista_imprime(Lista* l);

int lista_vazia(Lista* l );

Lista* lista_busca(Lista* l, int elem);

void lista_libera(Lista* l );

#endif