#include <stdio.h>

int main(){
    int quantidade_notas;
    printf("Digite a quantidade de notas que gostaria de atribuir: ");
    scanf("%d", &quantidade_notas);

    float notas[quantidade_notas]; // nota 1, nota 2, nota 3.
    //notas[0] = 10;
    //notas[1] = 8;
    //notas[2] = 6;
    float soma = 0;
    for(int i = 0; i < quantidade_notas; i++){
        printf("Digite a nota %d:", i +1);
        scanf("%f", &notas[i]);
        soma += notas[i];
    }

    for(int i = 0; i < quantidade_notas; i++){
        printf("Nota: %d Atribuida: %.2f\n", i + 1, notas[i]);
    }

    float media = soma/quantidade_notas;
    printf("A media do aluno: %.2f\n", media);
    return 0;
}