# include <stdio.h>

int main(){
    int numero;
    printf("APLICATIVO SOMADOR \n");

    do{
        printf("Insira um número: \n");
        scanf("%d", &numero);
        int soma = numero + numero;
        printf("%d\n", soma);

    }while(numero !=0);
    return 0;
}