#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lists/mod_lista.h"
#include "stacks/mod_pilha.h"

#define numeroDeCartasMax 52

Lista*  generate_cards(){
    Lista* cheap = lista_cria();
    
    int numberOfColors = 4;
    int numberOfNumbers = 9;

    for(int i = 1; i < numberOfColors+1; i++ ){
        for(int j = 1; j < numberOfNumbers+1; j++ ){
            // adaptando as listas para o tipo absrtato passado em aula, só espero que isso funcione
            Cards card;
            card.cor = i;
            card.simbolo = j;
            cheap = lista_insere(cheap,card);
        }

    }
    //Esta função deve gerar um baralho de 4 cores com simbolos de 1 - 10
    lista_imprime(cheap);

    printf("___________________________________________________");
    return cheap;
}
//numero = minimo + rand() \% (maximo - minimo + 1)\)
int randPos(int min,int max){
    srand(time(NULL));
    
    
    int randomPos =  min + rand()%(max - min + 1);

    return randomPos;
}
Lista* shuffleCards(Lista* cheap){
    // Isto deve iniciar o vetor auxiliar de alunos para o embaralhamento

    Lista* p;
    int i = 0;
    int posFree = numeroDeCartasMax;
    Cards vetAux[numeroDeCartasMax] = {0};
    
    for(p = cheap; p != NULL && i < numeroDeCartasMax; p = lista_prox(p)){
        int i = randPos(0,posFree);
        if(vetAux[i] != 0 ){
            vetAux[i] = lista_info(p);
        }else{
            posFree--;
        }
        
    }

    /*printf("Debugando o vetAux:\n");
    int j = 0;
    for(p = cheap; p != NULL && j < numeroDeCartasMax; p = lista_prox(p)){
        printf("cor:%d ----- simbolo: %d\n",vetAux[j].cor, vetAux[j].simbolo);
        j++;
    }*/

    // adicionando o vetor auxiliar na stack
    Pilha* stackCards = pilha_cria();
    for(int i = 0 ; i < numeroDeCartasMax;i++){
        pilha_push(stackCards,vetAux[numeroDeCartasMax]);
    }
    

    pilha_imprime(numeroDeCartasMax,stackCards);
    return 0;

}
void startGame(){
    printf("entrou na função!!");
    Lista*  cheap = generate_cards();
    shuffleCards(cheap);

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

