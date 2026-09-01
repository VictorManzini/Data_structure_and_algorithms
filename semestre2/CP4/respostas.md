1.1: O número de vezes que o for foi executado é o n-1, já que i começa em 1. 

1.2: O nunúmero de vezes que a comparaçnao i < n foi realizada é n vezes

1.3: O número de vezes em que a operação i++ é realiada é n - 1. 

1.4: 
soma = 0    1 vez
i = 1       1 vez
i < n       n vezes
i++         n - 1 vezes 
soma += vetor[i] n - 1 vezes
return soma  1 vez

1.5: 
int soma(int vetor[], int n){
    int soma = 0;                    // c1 -> executa 1 vez
    int c1=1, c2=1, c3=0, c4=0, c5=0, c6=1; // contadores (c1,c2,c6 fixos em 1)

    for(int i = 1; i < n; i++){      // c2: i=1 (1x) | c3: i<n (n vezes)
        c3++;
        soma += vetor[i];            // c4: n-1 vezes
        c4++;
        c5++;                        // c5: i++ (n-1 vezes)
    }
    c3++; // conta a última comparação falsa que encerra o loop

    printf("c1=%d c2=%d c3=%d c4=%d c5=%d c6=%d\n", c1, c2, c3, c4, c5, c6);
    // T(n) = c1 + c2 + c3 + c4 + c5 + c6

    return soma;                     // c6 -> executa 1 vez
}

1.6:
A função acima tem compexidade linear O(n). 

1.7: 
Porque O(n-1) e O(n) são a mesma ordem assintótica.


6.2: 
Com o struct aninhado nós podemos adicionar mais informações sem perder a organização. No código é muito perceptível 
isso, vemos que data de validade tem mais de um campo, ele tem dia, mes e ano, se colocassemos dia, mes e ano diretamente no struct do produto, o acesso na hora de manipular a data de validade ficaria confuso e desorganizado. 
O struct aninhado facilita na hora de manipular e acessar os dados. 