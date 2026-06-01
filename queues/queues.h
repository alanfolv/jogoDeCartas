#ifndef QUEUES_H
#define QUEUES_H
#include "../lists/mod_lista.h"
typedef struct {
    int id_jogador; //podemos utilizar 1 para o jodaor , 2 para bot , 3 para bot e assim por diante...
    char nome[20];
    Lista* mao;
    int qtd_cartas;
} Jogador;
//functions jogador
void jogador_compra_carta(Jogador* j, Cards carta);
void jogador_mostra_mao(Jogador j);
Cards jogador_remove_carta(Jogador* j, int indice);


typedef struct no No;
typedef struct fila Fila;

Fila* fila_cria(void);
void fila_insere(Fila* f, Jogador j);
Jogador fila_retira(Fila* f);
int fila_vazia(Fila* f);
void fila_libera(Fila* f);

#endif