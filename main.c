#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lists/mod_lista.h"
#include "stacks/mod_pilha.h"

#define numeroDeCartasMax 52

Lista* generate_cards() {
    Lista* deck = lista_cria(); // "deck" é baralho em inglês
    
    int numberOfColors = 4;
    int numberOfNumbers = 10; // Corrigido para 10 de acordo com seu comentário

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
    
    // CORREÇÃO: Faltava incrementar o 'count' dentro do loop!
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
    
    // CORREÇÃO: Imprimir apenas até 'count' (o total real de cartas)
    for (int i = 0; i < count; i++) {
        printf(">>>%d --- %d\n", vetAux[i].cor, vetAux[i].simbolo);
    }

    // CORREÇÃO: A função exigia retorno do tipo Lista*. 
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
    printf("Entrou na função!!\n\n");
    Lista* deck = generate_cards();
    
    // Agora capturamos o retorno da lista embaralhada
    Lista* shuffledDeck = shuffleCards(deck); 
}

void startMenu() {
    int op = 0;
    do {
        printf("\nDigite a opção desejada:\n1 - Jogar\n2 - Sair\n> ");
        scanf("%d", &op);
        
        switch(op) {
            case 1:
                startGame();
                break;
            case 2:
                printf("Até mais!\n");
                break;
            default:
                printf("Digite uma opção válida!\n");
         }
    } while(op != 2);
}

int main() {
    srand(time(NULL));
    startMenu();
    return 0;
}