#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "queues.h"
#ifdef _WIN32
    #include <conio.h>
    #define CLEAR_SCREEN() system("cls")
#else
    #include <unistd.h>
    #include <termios.h>
    #define CLEAR_SCREEN() system("clear")
    int getch(void) {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
        return ch;
    }
#endif

int obter_comando() {
    int tecla = getch();
    
    #ifdef _WIN32
    if (tecla == 0 || tecla == 224) {
        tecla = getch();
        if (tecla == 75 || tecla == 72) return 1; // Esquerda / Cima
        if (tecla == 77 || tecla == 80) return 2; // Direita / Baixo
    }
    if (tecla == 27) return 27; // ESC
    if (tecla == 13) return 13; // ENTER
    #else
    if (tecla == 10) return 13; // ENTER no Linux
    #endif
    
    // Suporte para WASD (útil no Linux)
    if (tecla == 'a' || tecla == 'A' || tecla == 'w' || tecla == 'W') return 1; 
    if (tecla == 'd' || tecla == 'D' || tecla == 's' || tecla == 'S') return 2; 
    if (tecla == 'q' || tecla == 'Q' || tecla == 27) return 27;                 
    if (tecla == 13) return 13;

    return -1;
}

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
    int comando;

    if (j.qtd_cartas == 0) return 0; // Se não tem cartas, retorna 0 (comprar)

    do {
        CLEAR_SCREEN();
        
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
        comando = obter_comando();

        // Se for uma tecla especial (setas), getch() retorna 0 ou 224 primeiro
        if (comando == 1) {
            if(cursor > 1)cursor--;
        }
        else if(comando ==2){
            if(cursor <j.qtd_cartas) cursor++;
        }
        else if(comando == 27){
            return 0;
        }

    } while (comando != 13);
    {
        return cursor;
        
    }
    
        