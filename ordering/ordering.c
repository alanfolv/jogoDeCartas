#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
main(){
    int i, tamanho;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);
    int *vet = (int*)malloc(tamanho * sizeof(int));
    printf("Digite os elementos do vetor: ");
    for(i=0; i<tamanho; i++){
        scanf("%d", &vet[i]);
    }
    bubble_sort(tamanho, vet);
    printf("Vetor ordenado: ");
    for(i=0; i<tamanho; i++){
        printf("%d ", vet[i]);
    }
    free(vet);
}