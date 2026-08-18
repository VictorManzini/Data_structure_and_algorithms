#include <stdio.h>
#include <string.h>

typedef struct{
    int id;
    char nome[50];
    float preco;
}Produto;

int main(){
    Produto produto1;
    printf("Digite o ID do produto: ");
    scanf("%d", &produto1.id);
    printf("\n");
    printf("Digite o nome do produto: ");
    while(getchar() != '\n'); //Tem que usar o while(getchar()) para limpar o buffer do scanf() anterior
    fgets(produto1.nome, sizeof(produto1.nome), stdin);
    produto1.nome[strcspn(produto1.nome, "\n")] = '\0'; //Usa o strcspn para tirar o "\n" que sobra do fgets, assim nao da erro no print
    printf("\n");
    printf("Digite o preco do produto: ");
    scanf("%f", &produto1.preco);
    printf("Produto: %s - Preco: %.2f - ID: %d \n", produto1.nome, produto1.preco, produto1.id);

    return 0;
}