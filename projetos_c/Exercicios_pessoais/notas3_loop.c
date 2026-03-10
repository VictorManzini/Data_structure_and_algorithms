    #include <stdio.h>
    #include <string.h>

    int main() {
        char nome[50];
        float nota;

        do {
        printf("Digite seu nome e a sua nota ou sair para encerrar o programa: ");
        
        scanf("%s", nome);
            if (strcmp(nome, "sair") == 0){
                printf("\n Encerrando o programa... \n \n"); 
                break; 
            }     
        printf("Aluno: %s\n", nome);
        scanf("%f", &nota); 
        printf("Nota: %.1f\n", nota);

            if (nota >=7.0) {
                printf("Aprovado\n");
            } else if (nota >=5.0) {
                printf("Recuperação\n");
            } else {
                printf("Reprovado\n");
            }
        } while (strcmp(nome, "sair") != 0);
            

        return 0;
    }