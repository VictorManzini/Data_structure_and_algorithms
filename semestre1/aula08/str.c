#include <stdio.h>
#include <string.h>

int main(){
    char nome[20];
    printf("Digite o seu nome: ");
    //scanf("%s", &nome);
    fgets(nome, 20, stdin);
    printf("O seu nome: %s\n", nome);

    return 0;
}