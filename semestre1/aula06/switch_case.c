// Aula 06 switch case e if, else if e else.
#include <stdio.h>
#include <string.h>

void menu(){
    printf("---MENU DO ALUNO---\n");
    printf("Selecione a opcao abaixo que gostaria:\n");
    printf("1 - Calcular media do aluno;\n");
    printf("2 - Verificar presenca do aluno - Aprovado ou Reprovado;\n");
}

float media_aluno(float nota1, float nota2){
   return (nota1 + nota2) / 2;
}

int main(){
    int opcao, presenca;
    float nota_1, nota_2, media;
    menu();
    printf("Escolha a opcao desejada:\n");

    scanf("%d", &opcao);
    switch(opcao){

        case 1:
        printf("---CALCULADORA MEDIA---\n"); // Media do aluno 
        printf("Digite a sua primeira nota:\n");
        scanf("%f", &nota_1);
        printf("Digite sua segunda nota\n");
        scanf("%f", &nota_2);
        media = media_aluno(nota_1, nota_2);
        printf("A media do aluno: %.2f\n", media);
        //break;

        case 2:
        printf("--- VERIFICADOR DE PRESENCA ---\n"); // Presença do aluno 
        printf("Digite a frequencia do aluno(0 - 100):\n");
        scanf("%d", &presenca);
        if(presenca >= 75 && presenca < 101 && media > 6) {
            printf("Aprovado!\n");
        }
        else if (presenca >= 75 && media < 6){
            printf("Aluno reprovado por media\n");
        }
        else if(presenca < 75 && media > 6){
            printf("Aluno reprovado por presenca\n");
        }
        else if(presenca < 75 && presenca >=0){
            printf("Aluno reprovado\n");
        }
        else{
            printf("Valor de presenca invalida\n");
        }
        printf("Media do aluno: %.2f\n", media);
        printf("Presenca do aluno: %.1d\n", presenca);
        break;

        default:
        printf("Opcao invalida\n");
    }


    return 0;
}