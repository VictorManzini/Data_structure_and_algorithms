#include <stdio.h>

int main(){ 

    int numero;
    printf("---TABUADA---\n");
    printf("Digite um número para saber a sua tabuada: ");
    scanf("%d", &numero);

    for(int i = 0; i < 11; i++){
        int resultado = i * numero;
        printf("%d x %d = %d\n", numero, i ,resultado);
    }

    return 0;
}