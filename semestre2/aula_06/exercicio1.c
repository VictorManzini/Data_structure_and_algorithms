// Aula 06 Recursividade
#include <stdio.h>

void contador_regressivo(int n){
    // Caso base
    if(n == 0) {printf("FIM!\n"); return;}

    // Caso recursivo
    // printf("%d\n", n);   // Cuidado onde coloca o print na recursividade
    contador_regressivo(n - 1);
    printf("%d\n", n);
} // Se o print for antes da recursao, funcao eh regressiva 54321; se o print for depois, a funcao eh progressiva 12345.

int somatorio(int n){
    // Caso Base 
    if(n == 0){
        return 0;
    }

    // Caso Recursivo
    int soma = n + somatorio(n - 1);
    printf("%d\n", soma);
    return soma;
}

int main(){
    //contador_regressivo(5);
    int soma = somatorio(10);
    printf("A soma do valor X ---> %d\n", soma);
    return 0;
}