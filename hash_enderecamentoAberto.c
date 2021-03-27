#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 100000

struct hash{
    int chave;
    char livre;
};

int funcao_hashing(int chave){
    return chave % TAM;
}

int insereHash(int chave, struct hash tabela[])
{
    int pos = funcao_hashing(chave);
    int i=0;
    while((i < TAM) &&(tabela[(pos+i)%TAM].livre != 'L'))
        i=i+1;
    if(i < TAM)
    {
        tabela[(pos+i)%TAM].chave = chave;
        tabela[(pos+i)%TAM].livre = 'O';
    }
    else
        printf("Tabela cheia \n");
}

int Buscar(struct hash tabela[], int valor)
{
    int pos = funcao_hashing(valor);
    int i=0;
    while((i < TAM) &&(tabela[(pos+i)%TAM].livre != 'L') &&(tabela[(pos+i)%TAM].chave != valor))
        i=i+1;
    if(tabela[(pos+i)%TAM].chave == valor){
        return (pos=i)%TAM;
    }
    else
        printf("Elemento nao encontrado \n");
    return 0;
}

void mostraHash (struct hash tabela[])
{
    int i;
    for (i=0;i < TAM;i++)
    {
        if(tabela[i].livre == 'O')
        {
            printf("%d \n", tabela[i].chave);
        }
    }
}

int main()
{
    srand(time(NULL));
    struct hash tabela[TAM];
    double start, stop, elapsed;
    int num, n=99500;

    for(int i=0; i<TAM;i++){
        tabela[i].livre='L';
    }

    start = (double) clock() / CLOCKS_PER_SEC;
    for(int i=0; i < n;i++){
        int v=rand();
        insereHash(v,tabela);
    }
    stop = (double) clock() / CLOCKS_PER_SEC;
    elapsed = stop - start;
    printf("Tempo de insercao: %f\n", elapsed);

//  printf("\nElementos inseridos na tabela Hash:\n");
//  mostraHash(tabela);

    printf("\n\nElemento a ser buscado na tabela Hash: \n");
    scanf("%d", &num);
    start = (double) clock() / CLOCKS_PER_SEC;
    Buscar(tabela, num);
    stop = (double) clock() / CLOCKS_PER_SEC;
    elapsed = stop - start;
    printf("\nTempo de busca: %f\n", elapsed);

    return 0;
}
