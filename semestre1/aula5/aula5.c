#include <stdio.h> // Aula de decisão e repetição 31/03/2026
#include <string.h>

int main() {
    printf("--------------------------");
    printf("CALCULADORA DE MEDIA E FALTAS");
    printf("--------------------------\n");
    printf("Digite a primeira nota:\n"); 
    float nota_1, nota_2;
    scanf("%f", &nota_1);
    printf("Digite a segunda nota:\n");
    scanf("%f", &nota_2);
    float media = (nota_1 + nota_2)/2;
    
    int falta;
    printf("Digite a porcntagem de faltas (apenas numeros, ex: 25):\n");
    scanf("%d", &falta);
    printf("Média: %f\n", media);
    printf("Faltas: %d\n", falta);

if(media>=7 && falta<=25){
    printf("Aluno aprovado\n");
}else if (media<7 && falta<=25){
    printf("Aluno em recupração\n");
}else if(media >=7 && falta > 25){
    printf("Reprovaçnao por falta\n");
}else {
    printf("Aluno reprovado\n");
}

    return 0;
}