#include <stdio.h> // Bibliotecas .h --> Header/ Cabeçalho

// teste2.c é um teste pessoal com loop básico que eu fiz

// Declarações de Variáveis (Globais), funções e Estruturas

// Lógica de Programação

int main(void){
    printf("Bem-vindos ao 1CCP ");

    int status;
    int continuar =1; // Control variable 

    while (continuar) {
        printf ("Digite um número (0 ou1), ou 2 para sair: ");
        scanf("%d", &status); 

        if (status == 0) {
            printf("Você é um aluno do 1CCP🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳\n");
        } else if (status ==1) {
            printf("Você é um intruso❌❌❌❌❌❌❌❌❌❌❌❌❌\n");
        } else if (status == 2) { 
            printf("Saindo...\n");
            continuar = 0; // Exit the loop
        } else {
            printf ("Opção inválida!\n");
        }
        printf("\n");
    }
    return 0;    
        
}


