#include <stdio.h>

int main() {
    printf("Digite seu nome e a sua nota: ");
    
    char nome[50];
    scanf("%s", nome); 
    float nota;
    scanf("%f", &nota);
    printf("Aluno: %s\n", nome);
    printf("Nota: %.1f\n", nota);

    if (nota >= 7.0) {
        printf("Aprovado\n");
    }else if (nota >= 5.0) {
        printf("recuperação\n");
    } else {
        printf("Reprovado\n");
    }
    
    return 0;
}

