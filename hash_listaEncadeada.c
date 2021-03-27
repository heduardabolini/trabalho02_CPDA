#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 99500

struct hash{
    int chave;
    struct hash *proximo;
};

int funcao_hash(int chave){
    return chave % TAM;
}

int insereHash(int chave, struct hash *vet[])
{
    int pos = funcao_hash(chave);
    struct hash* novo;
    novo = (struct hash*) malloc(sizeof(struct hash));
    novo->proximo=vet[pos];
    novo->chave = chave;
    vet[pos]=novo;
    return 1;
}

void mostraHash (struct hash* tabela[])
{
    struct hash* aux;
    int i;
    for (i=0;i < TAM;i++)
    {
        aux = tabela[i];
        while (aux != NULL)
        {
            printf("Posicao: %d Valor: %d \n", i, aux->chave);
            aux=aux->proximo;
        }
    }
}

struct hash *buscar(struct hash* tabela[], int valor)
{
    int pos = funcao_hash(valor);
    struct hash* aux;
    aux = tabela[pos];
    while (aux != NULL)
    {
        if(aux->chave == valor)
        {
            printf("Elemento: %d Posicao: %d \n", aux->chave, pos);
            return aux;
        }
        else
            aux=aux->proximo;
    }
    printf("Nao encontrado \n");
    return aux;

}

int main()
{
    srand(time(NULL));
    struct hash *vet[TAM];
    double start, stop, elapsed;
    int num, n=100000;

    start = (double) clock() / CLOCKS_PER_SEC;
    for(int i=0; i < n;i++){
        int v=rand();
        insereHash(v,vet);
    }
    stop = (double) clock() / CLOCKS_PER_SEC;
    elapsed = stop - start;
    printf("Tempo de insercao: %f\n", elapsed);

//  printf("\nElementos inseridos na tabela Hash:s\n");
//  mostraHash(vet);

    printf("\n\nElemento a ser buscado na tabela Hash: \n");
    scanf("%d", &num);
    start = (double) clock() / CLOCKS_PER_SEC;
    buscar(vet, num);
    stop = (double) clock() / CLOCKS_PER_SEC;
    elapsed = stop - start;
    printf("Tempo de busca: %f\n", elapsed);

    return 0;
}
