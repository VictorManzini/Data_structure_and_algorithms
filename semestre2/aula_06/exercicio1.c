// Aula 06 Recursividade
#include <stdio.h>

void contador_regressivo(int n){
    // Caso base
    if(n == 0) {printf("FIM!\n"); return;}

    // Caso recursivo
    // printf("%d\n", n);   // Cuidado onde coloca o print na recursividade
    contador_regressivo(n - 1);
    printf("%d\n", n);
}

int main(){
    contador_regressivo(5);

    return 0;
}