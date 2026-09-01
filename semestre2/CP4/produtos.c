#include <stdio.h> 
#include <string.h>

typedef struct{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct{
    int id;
    char nome[50];
    float preco;
    int quantidade;
    Data validade;
}Produto;

int main() {
    Produto produto;
    float valorTotal;
 
    printf("Digite o ID do produto: ");
    scanf("%d", &produto.id);
    printf("\n");
 
    while(getchar() != '\n');
    printf("Digite o nome do produto: ");
    fgets(produto.nome, sizeof(produto.nome), stdin);
    produto.nome[strcspn(produto.nome, "\n")] = '\0'; 
    printf("\n");

    printf("Data de validade\n");
    printf("Digite o dia da data de validade do produto: ");
    scanf("%d", &produto.validade.dia);
    printf("\n");
    printf("Digite o mes de validade: ");
    scanf("%d", &produto.validade.mes);
    printf("\n");
    printf("Digite o ano de validade: ");
    scanf("%d", &produto.validade.ano);
    printf("\n");
 
    printf("Digite o preco do produto: ");
    scanf("%f", &produto.preco);
 
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &produto.quantidade);
 
    valorTotal = produto.preco * produto.quantidade;
 
    printf("\n--- Dados do Produto ---\n");
    printf("ID: %d\n", produto.id);
    printf("Nome: %s\n", produto.nome);
    printf("Data de validade do produto: %d/%d/%d\n", produto.validade.dia, produto.validade.mes, produto.validade.ano);
    printf("Preco: R$ %.2f\n", produto.preco);
    printf("Quantidade: %d\n", produto.quantidade);
    printf("Valor total em estoque: R$ %.2f\n", valorTotal);
 
    return 0;
}