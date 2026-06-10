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
int bot_escolhe_jogada(Jogador j, Cards carta_mesa);
int jogador_valida_jogada(Cards carta_escolhida, Cards carta_mesa);
void verificar_situacao_uno(Jogador* j);
int checar_vitoria(Jogador j);
int jogador_seleciona_carta_setas(Jogador j, Cards carta_mesa);

typedef struct no No;
typedef struct fila Fila;

Fila* fila_cria(void);
void fila_insere(Fila* f, Jogador j);
Jogador fila_retira(Fila* f);
int fila_vazia(Fila* f);
void fila_libera(Fila* f);

#endif