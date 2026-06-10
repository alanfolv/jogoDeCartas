#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ordering.h"
void bubble_sort (int tamanho, int *vet){
    int i, j, aux;

    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            if (vet[j] > vet[j + 1]) {  // VERIFICAÇAO PARA COLOCAR O MAIOR ELEMENTO NO FINAL

                aux = vet[j];         // TROCA DE ELEMENTOS
                vet[j] = vet[j + 1];
                vet[j + 1] = aux;
            }
        }
    }
}
void bubble_sort_cards(Cards* vet, int tamanho) {
    int i, j;
    Cards aux;

    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            
            
            // se a cor da carta atual for maior que a da prox troca.
            // se a cor for igual, mas o numerofor maior .
            if ((vet[j].cor > vet[j + 1].cor) || 
               (vet[j].cor == vet[j + 1].cor && vet[j].simbolo > vet[j + 1].simbolo)) {
                
                
                aux = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = aux;
            }
        }
    }
}
