#include <stdio.h>

int main(){ 

    int numero;
    printf("---TABUADA---\n");
    printf("Digite um número para saber a sua tabuada: ");
    scanf("%d", &numero);

    /* LOOP WHILE */
    printf("LOOP FOR\n");
    for(int i = 0; i < 11; i++){
        int resultado = i * numero;
        printf("%d x %d = %d\n", numero, i ,resultado);
    }

    /* LOOP WHILE */
    printf("LOOP WHILE\n");
    int i = 0; 
    while(i < 11){
        int resultado = i * numero; 
        printf("%d x %d = %d\n", numero, i, resultado);
        i++;
    }

    /* LOOPE DO WHILE  */
    printf("LOOP DO WHILE\n");
    i = 0;
    do{
        int resultado = numero * i;
        printf("%d x %d = %d\n", numero, i, resultado);
        i++;

    }while(i < 11);

    return 0;
}