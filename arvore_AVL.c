#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Arvore{
    int num, altd, alte;
    struct Arvore *dir, *esq;
}Arvore;

Arvore *rotacao_esq(Arvore *tree)
{
    Arvore *aux1, *aux2;
    aux1 = tree->dir;
    aux2 = aux1->esq;
    tree->dir = aux2;
    aux1->esq= tree;
    if(tree->dir == NULL)
        tree->altd=0;
    else if(tree->dir->alte > tree->dir->altd)
        tree->altd = tree->dir->alte+1;
    else
        tree->altd = tree->dir->altd+1;

    if(aux1->esq->alte > aux1->esq->altd)
        aux1->alte = aux1->esq->alte+1;
    else
        aux1->alte = aux1->esq->dir+1;
    return aux1;
}

Arvore *rotacao_dir(Arvore *tree)
{
    Arvore *aux1, *aux2;
    aux1 = tree->esq;
    aux2 = aux1->dir;
    tree->esq = aux2;
    aux1->dir = tree;
    if(tree->esq == NULL)
        tree->alte=0;
    else if(tree->esq->alte > tree->esq->altd)
        tree->alte = tree->esq->alte+1;
    else
        tree->alte = tree->esq->altd+1;

    if(aux1->dir->alte > aux1->dir->altd)
        aux1->altd = aux1->dir->alte+1;
    else
        aux1->altd = aux1->dir->altd+1;
    return aux1;
}

Arvore *balanceamento (Arvore *aux)
{
    int d, df;
    d= aux->altd - aux->alte;
    if(d == 2)
    {
        df= aux->dir->altd - aux->dir->alte;
        if(df >=0 )
            aux = rotacao_esq(aux);
        else
        {
            aux->dir = rotacao_dir(aux->dir);
            aux = rotacao_esq(aux);
        }
    }
    else if(d == -2)
    {
        df= aux->esq->altd - aux->esq->alte;
        if(df <= 0)
            aux=rotacao_dir(aux);
        else{
            aux->esq = rotacao_esq(aux->esq);
            aux = rotacao_dir(aux);
        }
    }
    return aux;

}

Arvore *inserir(Arvore * aux, int num)
{
    Arvore *novo;
    if(aux == NULL)
    {
        novo = (Arvore*) malloc(sizeof(Arvore));
        novo->num = num;
        novo->altd=0;
        novo->alte=0;
        novo->dir=NULL;
        novo->esq=NULL;
        aux=novo;
    }
    else if(num < aux->num)
    {
        aux->esq = inserir(aux->esq, num);
        if(aux->esq->altd > aux->esq->alte)
            aux->alte = aux->esq->altd+1;
        else
            aux->alte = aux->esq->alte +1;
        aux = balanceamento(aux);
    }
    else
    {
        aux->dir = inserir(aux->dir, num);
        if(aux->dir->altd > aux->dir->alte)
            aux->altd = aux->dir->altd +1;
        else
            aux->altd = aux->dir->alte +1;
        aux = balanceamento(aux);
    }
    return aux;
}

void mostraremOrdem(Arvore *aux)
{
    if(aux !=NULL)
    {
        mostraremOrdem(aux->esq);
        printf("%d \n", aux->num);
        mostraremOrdem(aux->dir);
    }
}

void mostrarPreOrdem(Arvore *aux)
{
    if(aux !=NULL)
    {
        printf("%d \n", aux->num);
        mostraremOrdem(aux->esq);
        mostraremOrdem(aux->dir);
    }
}

void mostrarPosOrdem(Arvore *aux)
{
    if(aux !=NULL)
    {
        mostraremOrdem(aux->esq);
        mostraremOrdem(aux->dir);
        printf("%d \n", aux->num);
    }
}

int consultar(Arvore *aux, int num, int achou)
{
    if(aux != NULL && achou == 0)
    {
        if(aux->num == num)
            achou = 1;
        else if(num < aux->num)
                achou= consultar(aux->esq, num, achou);
            else
                achou=consultar(aux->dir, num, achou);
    }
    return achou;
}

Arvore *remover(Arvore *aux, int num)
{
    Arvore *p, *p2;
    if(aux->num == num)
    {
        if(aux->esq == aux->dir)
        {//nao tem filho NULL
            free(aux);//deletando no
            return NULL;
        }
        else if (aux->esq == NULL)
        {//filho pela direita
            p=aux->dir;
            free(aux);
            return p;
        }
        else if(aux->dir ==NULL)
        {//filho pela esquerda
            p=aux->esq;
            free(aux);
            return p;
        }
        else
        {//filhos pelos dois lados
            p2=aux->dir;
            p=aux->dir;
            while(p->esq != NULL)
                p=p->esq;
            p->esq = aux->esq;
            free(aux);
            return p2;
        }
    }
    else if(aux->num < num)
        aux->dir = remover(aux->dir, num);
    else
        aux->esq =remover(aux->esq, num);
    return aux;
}

Arvore *atualizar(Arvore *aux)
{
    if(aux != NULL)
    {
        aux->esq = atualizar(aux->esq);
        if(aux->esq == NULL)
            aux->esq = 0;
        else if(aux->esq->alte > aux->esq->altd)
            aux->alte = aux->esq->alte +1;
        else
            aux->alte = aux->esq->altd +1;

        aux->dir = atualizar(aux->dir);
        if(aux->dir == NULL)
            aux->altd=0;
        else if(aux->dir->alte > aux->dir->altd)
                aux->altd = aux->dir->alte +1;
        else
            aux->altd=aux->dir->altd +1;
        aux = balanceamento(aux);
    }
    return aux;
}

//esvaziar arvore
Arvore *esvaziar(Arvore *aux)
{
    if(aux != NULL)
    {
        aux->esq = esvaziar(aux->esq);
        aux->dir = esvaziar(aux->dir);
        free(aux);
    }
    return NULL;
}

int main()
{
    Arvore *raiz=NULL;
    Arvore *aux;//ponteiro
    int op, achou, num, n=100000;
    double start, stop, elapsed;

    start = (double) clock() / CLOCKS_PER_SEC;
    for(int i=1; i <= n;i++){
        int valor = rand();
        raiz=inserir(raiz, valor);
    }
    stop = (double) clock() / CLOCKS_PER_SEC;
    elapsed = stop - start;
    printf("Tempo de insercao: %f\n", elapsed);

    if(raiz == NULL)
        printf("Arvore vazia. \n");
    else
    {
        printf("\n\nElemento a ser buscado na arvore: \n");
        scanf("%d", &num);
        achou=0;
        start = (double) clock() / CLOCKS_PER_SEC;
        achou =consultar(raiz, num, achou);
        stop = (double) clock() / CLOCKS_PER_SEC;
        elapsed = stop - start;
        printf("Tempo de busca: %f\n", elapsed);
        if(achou ==0)
            printf("Elemento nao encontrado.\n");
        else
            printf("Elemento encontrado. \n");
    }


  //  printf("\nOrdem. \n");
  //  mostraremOrdem(raiz);

  //  printf("\nPre Ordem. \n");
  //  mostrarPreOrdem(raiz);

  //  printf("\nPos Ordem. \n");
  //  mostrarPosOrdem(raiz);


    if(raiz == NULL)
        printf("Arvore vazia. \n");
    else
    {
        start = (double) clock() / CLOCKS_PER_SEC;
        esvaziar(raiz);
        stop = (double) clock() / CLOCKS_PER_SEC;
        elapsed = stop - start;
        printf("\nTempo de remocao: %f\n", elapsed);
    }

    return 0;
}
