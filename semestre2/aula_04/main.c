#include <stdio.h>
#include <string.h>

int main(){
    int valor = 10;
    int *ptr = NULL; // ptr eh um ponteiro para int (guarda o endereco, nao o valor)

    ptr = &valor; // ptr aponta para valor

    printf("Valor original: %d\n", valor);
    printf("Endereco de valor: %p\n", (void*)&valor); // exibe o endereco de valor 
    printf("Endereco armazenado por ptr: %p\n", (void*)ptr); // exibe o endereco da variavel apontada por ptr
    printf("Valor acessado por ptr: %d\n", *ptr); // *prt eh o valor que esta na variavel que ptr esta apontando

    *ptr = 50; // altera o valor de int valor de 10 para 50
    printf("Valor depois da alteracao: %d\n", *ptr); // printa o valor que foi alterado por *ptr
    //printf("%d\n", valor);

    return 0;
}