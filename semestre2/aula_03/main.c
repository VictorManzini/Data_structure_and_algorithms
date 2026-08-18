#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
//Aula de struct e typedef

struct Aluno{
    int rm;
    char nome[50];
    float nota[2];
    char email[50];
    bool aprovacao;
};

int main(){
    struct Aluno aluno[10];
    // Primeiro aluno
    aluno[0].rm = 572123;
    strcpy(aluno[0].nome, "Victor"); // o jeito de manipular string com struct: strcpy
    strcpy(aluno[0].email, "vikmanzini@icloud.com");
    aluno[0].aprovacao = true;
    aluno[0].nota[0] = 9.5;
    aluno[0].nota[1] = 7.0;
    float media = (aluno[0].nota[0] + aluno[0].nota[1]) / 2;
    printf("%d\n", aluno[0].rm);
    printf("%s\n", aluno[0].nome);
    printf("%s\n", aluno[0].email);
    printf("%.2f\n", media);
    if(media >= 6 && aluno[0].aprovacao == true){
        printf("Aluno aprovado\n");
    }
    else if(media >= 4 && media < 6 && aluno[0].aprovacao == true){
        printf("Aluno em exame\n");
    }
    else{
        printf("Aluno em recuperacao\n");
    }
    return 0;
}