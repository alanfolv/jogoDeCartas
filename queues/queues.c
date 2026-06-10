#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "queues.h"
#include<conio.h>
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
    printf("\n Mão do jogador %s (%d cartas):\n", j.nome, j.qtd_cartas);

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
        index++;
    }
    printf("\n");
}

Cards jogador_remove_carta(Jogador* j, int indice){
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

int jogador_valida_jogada(Cards carta_escolhida, Cards carta_mesa) {
    if (carta_escolhida.cor == carta_mesa.cor || carta_escolhida.simbolo == carta_mesa.simbolo) {
        return 1; //jogada valida
    }
    return 0; // jogada invalida
}

int bot_escolhe_jogada(Jogador j, Cards carta_mesa) {
    Lista* p = j.mao;
    int index = 1;
    
    while (p != NULL) {
        Cards c = lista_info(p);
        if (jogador_valida_jogada(c, carta_mesa)) {
            return index; // Retorna o index da carta que ele vai jogar
        }
        p = lista_prox(p);
        index++;
    }
    return -1; // Bot não tem carta na mao , precisa comprar
}

void verificar_situacao_uno(Jogador* j) {
    if (j->qtd_cartas == 1) {
        printf("\n\033[1;35m📣 [%s] GRITOU: UNOS!!!\033[0m\n", j->nome);
    }
}

int checar_vitoria(Jogador j) {
    return (j.qtd_cartas == 0);
}

int jogador_seleciona_carta_setas(Jogador j, Cards carta_mesa) {
    int cursor = 1; // Começa selecionando a primeira carta
    int tecla;

    if (j.qtd_cartas == 0) return 0; // Se não tem cartas, retorna 0 (comprar)

    do {
        // Limpa o terminal para redesenhar a mão atualizada
        // windows "cls", no linux "clear"
        system("cls"); 
        printf("\n===================================================");
        printf("\nCARTA NA MESA: ");
        switch(carta_mesa.cor) {
            case 1: printf("\033[1;33m[ %d ]\033[0m\n", carta_mesa.simbolo); break; // Amarelo
            case 2: printf("\033[1;32m[ %d ]\033[0m\n", carta_mesa.simbolo); break; // Verde
            case 3: printf("\033[1;34m[ %d ]\033[0m\n", carta_mesa.simbolo); break; // Azul
            case 4: printf("\033[1;31m[ %d ]\033[0m\n", carta_mesa.simbolo); break; // Vermelho
        }
        
        printf("\nMao de %s (%d cartas) - Use [Esquerda/Direita] e [Enter] para jogar:\n", j.nome, j.qtd_cartas);
        printf("Selecione o indicador com '->'  ou aperte [ESC] para voltar/comprar.\n\n");

        Lista* p = j.mao;
        int index = 1;
        
        while (p != NULL) {
            Cards c = lista_info(p);
            
            // Se o índice atual for onde o cursor está, desenha uma seta apontando
            if (index == cursor) {
                printf(" -> [%d] ", index);
            } else {
                printf("    [%d] ", index);
            }

            // Mantém a sua lógica do número colorido
            switch(c.cor) {
                case 1: printf("\033[1;33m%d\033[0m\n", c.simbolo); break; // Amarelo
                case 2: printf("\033[1;32m%d\033[0m\n", c.simbolo); break; // Verde
                case 3: printf("\033[1;34m%d\033[0m\n", c.simbolo); break; // Azul
                case 4: printf("\033[1;31m%d\033[0m\n", c.simbolo); break; // Vermelho
                default: printf("%d\n", c.simbolo);
            }
            
            p = lista_prox(p);
            index++;
        }

        // Captura a tecla pressionada
        tecla = getch();

        // Se for uma tecla especial (setas), getch() retorna 0 ou 224 primeiro
        if (tecla == 0 || tecla == 224) {
            tecla = getch(); // Pega o código real da tecla
            
            if (tecla == 75) { // Seta para a ESQUERDA ou CIMA (dependendo do terminal)
                if (cursor > 1) cursor--;
            } 
            else if (tecla == 77) { // Seta para a DIREITA ou BAIXO
                if (cursor < j.qtd_cartas) cursor++;
            }
        }
        else if (tecla == 27) { // 27 é o código do botão [ESC]
            return 0; // Usuário desistiu ou quer comprar
        }

    } while (tecla != 13); // 13 é o código do botão [ENTER]

    return cursor; // Retorna o índice da carta confirmada
}