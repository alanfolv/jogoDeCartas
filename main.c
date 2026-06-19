#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "queues/queues.h"
#include "lists/mod_lista.h"
#include "stacks/mod_pilha.h"
#ifdef _WIN32
    #define CLEAR_SCREEN() system("cls")
    #define PAUSE() system("pause")
#else
    #define CLEAR_SCREEN() system("clear")
    int getch(void); // Declaração para usar o getch customizado do Linux
    #define PAUSE() do { printf("\nPressione qualquer tecla para continuar..."); getch(); } while(0)
#endif

#define numeroDeCartasMax 52

Lista* generate_cards() {
    Lista* deck = lista_cria(); // "deck" é baralho em inglês
    
    int numberOfColors = 4;
    int numberOfNumbers = 10; 

    // i <= numberOfColors e j <= numberOfNumbers para pegar de 1 a 10 e 1 a 4
    for(int i = 1; i <= numberOfColors; i++) {
        for(int j = 1; j <= numberOfNumbers; j++) {
            Cards card;
            card.cor = i;
            card.simbolo = j;
            deck = lista_insere(deck, card);
        }
    }
    
    // Gera um baralho de 4 cores com simbolos de 1 - 10
    lista_imprime(deck);
    printf("___________________________________________________\n");
    return deck;
}

int randPos(int min, int max) {
    return min + rand() % (max - min + 1);
}

Lista* shuffleCards(Lista* deck) {
    Lista* p;
    int count = 0;
    Cards vetAux[numeroDeCartasMax] = {0};
    
    
    for(p = deck; p != NULL && count < numeroDeCartasMax; p = lista_prox(p)) {
        vetAux[count] = lista_info(p);
        count++; // Adicionado para andar no vetor
    }
    
    // Algoritmo de Fisher-Yates
    for (int i = count - 1; i > 0; i--) {
        int j = randPos(0, i); 
        Cards temp = vetAux[i];
        vetAux[i] = vetAux[j];
        vetAux[j] = temp;
    }
    
    
    for (int i = 0; i < count; i++) {
        printf(">>>%d --- %d\n", vetAux[i].cor, vetAux[i].simbolo);
    }

    
    // Reconstruindo a lista embaralhada:
    Lista* shuffledDeck = lista_cria();
    for(int i = 0; i < count; i++) {
        shuffledDeck = lista_insere(shuffledDeck, vetAux[i]);
    }
    
    return shuffledDeck;

    /* // OBS: Se você quiser usar a Pilha, a assinatura da função deve ser Pilha* shuffleCards(Lista* deck)
    Pilha* stackCards = pilha_cria();
    for(int i = 0 ; i < count ;i++){
        pilha_push(stackCards, vetAux[i]);
    }
    pilha_imprime(numeroDeCartasMax, stackCards);
    return stackCards;
    */
}

void startGame() {
    printf("\n==============================");
    printf("\n          JOGO COMEÇOU        ");
    printf("\n==============================");
    system("pause");
    // 1. Inicializa os Turnos e Estrutura dos Jogadores
    Fila* turnos = fila_cria();
    Jogador p1 = {0, "Voce", lista_cria(), 0};
    Jogador bot1 = {1, "Bot 1", lista_cria(), 0};
    Jogador bot2 = {2, "Bot 2", lista_cria(), 0};

    // 2. Cria e Embaralha o Baralho Principal
    Lista* baralho_base = generate_cards();
    Lista* baralho_compras = shuffleCards(baralho_base);

    // 3. Distribui 7 cartas para cada jogador (removendo do topo da lista)
    for (int i = 0; i < 7; i++) {
        if (baralho_compras != NULL) {
            jogador_compra_carta(&p1, lista_info(baralho_compras));
            baralho_compras = lista_prox(baralho_compras);
        }
        if (baralho_compras != NULL) {
            jogador_compra_carta(&bot1, lista_info(baralho_compras));
            baralho_compras = lista_prox(baralho_compras);
        }
        if (baralho_compras != NULL) {
            jogador_compra_carta(&bot2, lista_info(baralho_compras));
            baralho_compras = lista_prox(baralho_compras);
        }
    }

    // Coloca os jogadores na fila de turnos para ditar a ordem
    fila_insere(turnos, p1);
    fila_insere(turnos, bot1);
    fila_insere(turnos, bot2);

    // 4. Define a primeira carta da mesa
    Cards carta_mesa = lista_info(baralho_compras);
    baralho_compras = lista_prox(baralho_compras);

    int alguem_venceu = 0;


    // loop da partida
    while (!alguem_venceu) {
        // Retira o jogador da vez da fila
        Jogador atual = fila_retira(turnos);
        
        // Exibe o estado da mesa antes da jogada
        system("cls");
        printf("\n===================================================");
        printf("\nCARTA NA MESA: ");
        switch(carta_mesa.cor) {
            case 1: printf("\033[1;33m[ %d ]\033[0m\n", carta_mesa.simbolo); break; // Amarelo
            case 2: printf("\033[1;32m[ %d ]\033[0m\n", carta_mesa.simbolo); break; // Verde
            case 3: printf("\033[1;34m[ %d ]\033[0m\n", carta_mesa.simbolo); break; // Azul
            case 4: printf("\033[1;31m[ %d ]\033[0m\n", carta_mesa.simbolo); break; // Vermelho
        }
        printf("===================================================\n");
        printf("Vez de de jogar: %s (%d cartas)\n", atual.nome, atual.qtd_cartas);
        system("pause");

        // --- TURNO DO JOGADOR HUMANO (Interativo com Setas) ---
        if (atual.id_jogador == 0) {
            int jogada_valida = 0;

            while (!jogada_valida) {
                // Abre o menu de navegação por setas do teclado
                int opcao = jogador_seleciona_carta_setas(atual, carta_mesa);

                if (opcao == 0) {
                    // Pressionou [ESC] -> Escolheu comprar
                    if (baralho_compras != NULL) {
                        Cards nova = lista_info(baralho_compras);
                        jogador_compra_carta(&atual, nova);
                        baralho_compras = lista_prox(baralho_compras);
                        printf("\nVoce nao jogou nenhuma carta e comprou uma!\n");
                    } else {
                        printf("\nO baralho de compras acabou!\n");
                    }
                    system("pause");
                    jogada_valida = 1;
                } 
                else {
                    // Navega na lista encadeada até encontrar a carta selecionada pelo cursor
                    Lista* temp = atual.mao;
                    for (int c = 1; c < opcao; c++) {
                        temp = lista_prox(temp);
                    }
                    Cards escolhida = lista_info(temp);

                    // Valida a carta de acordo com as regras do Uno
                    if (jogador_valida_jogada(escolhida, carta_mesa)) {
                        carta_mesa = jogador_remove_carta(&atual, opcao);
                        printf("\nVoce jogou com sucesso o numero %d!\n", carta_mesa.simbolo);
                        system("pause");
                        jogada_valida = 1;
                    } else {
                        printf("\n\033[1;31mJogada invalida! A carta precisa ter a mesma cor ou simbolo da mesa.\033[0m\n");
                        system("pause");
                    }
                }
            }
        } 
        // --- turnoi dos bots ---
        else {
            system("cls");
            printf("\n===================================================");
            printf("\nCARTA NA MESA: ");
            switch(carta_mesa.cor) {
                case 1: printf("\033[1;33m[ %d ]\033[0m\n", carta_mesa.simbolo); break; 
                case 2: printf("\033[1;32m[ %d ]\033[0m\n", carta_mesa.simbolo); break; 
                case 3: printf("\033[1;34m[ %d ]\033[0m\n", carta_mesa.simbolo); break; 
                case 4: printf("\033[1;31m[ %d ]\033[0m\n", carta_mesa.simbolo); break; 
            }
            printf("===================================================\n");
            printf("Vez de jogar: %s (%d cartas)\n", atual.nome, atual.qtd_cartas);
            system("pause");
            
            int indice_bot = bot_escolhe_jogada(atual, carta_mesa);
            
            if (indice_bot != -1) {
                carta_mesa = jogador_remove_carta(&atual, indice_bot);
                printf("\n%s jogou o numero %d!\n", atual.nome, carta_mesa.simbolo);
                system("pause");
            } else {
                // Se o Bot não tiver carta válida, compra automaticamente
                if (baralho_compras != NULL) {
                    Cards nova = lista_info(baralho_compras);
                    jogador_compra_carta(&atual, nova);
                    baralho_compras = lista_prox(baralho_compras);
                    printf("\n%s nao tinha jogadas validas e comprou uma carta!\n", atual.nome);
                } else {
                    printf("\nO baralho de compras acabou!\n");
                }
                system("pause");
            }
        }

        // 5. Verifica se o jogador atual zerou a mão 
        if (checar_vitoria(atual)) {
            system("cls");
            printf("\n🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆");
            printf("\n  PARABENS! %s VENCEU O JOGO! ", atual.nome);
            printf("\n🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆\n\n");
            system("pause");
            alguem_venceu = 1;
            lista_libera(atual.mao); 
            break; 
        }

        // 6. Verifica se o jogador entrou em modo uno
        verificar_situacao_uno(&atual);
        if (atual.qtd_cartas == 1) {
            system("pause");
        }

        // 7. Passa a vez: Recoloca o jogador no fim da fila
        fila_insere(turnos, atual);
    }

    // === LIMPEZA FINAL DE MEMÓRIA DA RODADA ===
    while (!fila_vazia(turnos)) {
        Jogador sobrou = fila_retira(turnos);
        lista_libera(sobrou.mao);
    }
    fila_libera(turnos);
    lista_libera(baralho_base);
    
    printf("\nPartida encerrada. Retornando ao menu...\n");
}
    
    


void startMenu() {
    int op = 0;
    do {
        system("cls");
        printf("===============================\n");
        printf("        UNO EM C TERMINAL      \n");
        printf("===============================\n");
        printf(" Digite a opcao desejada:\n");
        printf(" 1 - Jogar\n");
        printf(" 2 - Sair\n");
        printf("> ");
        
        if (scanf("%d", &op) != 1) {
            // Limpa buffer caso o usuário digite um caractere inválido
            while (getchar() != '\n');
            continue;
        }
        
        switch(op) {
            case 1:
                startGame();
                break;
            case 2:
                printf("\nAte mais!\n");
                break;
            default:
                printf("\nDigite uma opcao valida!\n");
                system("pause");
        }
    } while(op != 2);
}

int main() {
    // Inicializa a semente de números pseudo-aleatórios com base no tempo
    srand(time(NULL));
    startMenu();
    return 0;
}