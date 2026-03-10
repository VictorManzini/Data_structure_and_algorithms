#include <stdio.h>

int main() {
    float nota;
    scanf("%f", &nota);
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

