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

long long potencia(int base, int exp){ // long ocupa 4 bytes na memoria | long long ocupa 8 bytes na memoria
    // Caso Base
    if(exp == 0){
        return 1;
    }
    // Caso Recursivo
    return base * potencia(base, exp -1);
}

int somaVetor(int v[], int n){
    // Caso Base
    if(n == 0){
        return 0;
    }
    // Caso Recursivo
    return v[n - 1] + somaVetor(v, n - 1);
}

int maiorElemento(int v[], int n){
    if(n == 1){
        return v[0];
    }

    int anterior = maiorElemento(v, n - 1);

    if(v[n - 1] > anterior){
        return v[n - 1];
    }
    return anterior;
}

int main(){
    //contador_regressivo(5);
    //int soma = somatorio(10);
    //printf("A soma do valor X ---> %d\n", soma);

    //printf("O resultado da potencia ---> %lld.\n", potencia(2, 5));

    int v[] = {10, 20, 30, 40, 50}; // vetor 
    int n = sizeof(v) / sizeof(v[0]); // tamanho do vetor
    //printf("A soma do vetor v[] ---> %d\n", somaVetor(v, n));

    printf("O maior elemento do vetor ---> %d\n", maiorElemento(v, n));
    return 0;
}