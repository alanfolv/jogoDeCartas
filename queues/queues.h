#ifndef QUEUES_H
#define QUEUES_H

typedef struct {
    int id_jogador;
    char nome[20];
} Jogador;

typedef struct no No;
typedef struct fila Fila;

Fila* fila_cria(void);
void fila_insere(Fila* f, Jogador j);
Jogador fila_retira(Fila* f);
int fila_vazia(Fila* f);
void fila_libera(Fila* f);

#endif