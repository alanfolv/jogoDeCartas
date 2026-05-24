#include <stdlib.h>
#include <stdio.h>
#include "lists/mod_lista.h"



Lista*  generate_cards(){
    Lista* cheap = lista_cria();
    
    int numberOfColors = 4;
    int numberOfNumbers = 10;
    for(int i = 1; i < numberOfColors+1; i++ ){
        for(int j = 1; j < numberOfColors+1; j++ ){
            // adaptando as listas para o tipo absrtato passado em aula, só espero que isso funcione
            Cards card;
            card.cor = i;
            card.simbolo = j;
            cheap = lista_insere(cheap,card);
        }

    }
    //Esta função deve gerar um baralho de 4 cores com simbolos de 1 - 10
    return cheap;
}
void startGame(){
    printf("entrou na função!!");
}
void startMenu(){
    int op = 0;
    do{
        
        printf("digite a opção desejada\n 1- Jogar\n2-sair");
        scanf("%d",&op);
        switch(op){
            case 1:
                startGame();
                break;
            case 2:
                printf("Até mais!");
                break;
            default:
                printf("Digite uma opção válida");

         }
    }while(op!=2);
    
}
int main(){

    startMenu();

    return 0;
}

