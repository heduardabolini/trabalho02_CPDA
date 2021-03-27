#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Arvore{
    int num;
    struct Arvore *esq, *dir;
};

struct Pilha{
    struct Arvore *num;
    struct Pilha *prox;
};

int buscar(struct Arvore *raiz, int num)
{
    if(raiz == NULL)
    {
        printf("Arvore vazia.\n");
    }
    else{
        int achou =0;
        struct Arvore* aux;
        aux=raiz;
        while (aux!= NULL && achou ==0)
        {
            if(aux->num == num)
            {
                printf("Elemento encotrado. \n");
                achou=1;
                return 1;
            }
            else if(num < aux->num)
                aux=aux->esq;
                else aux=aux->dir;
        }
        if(achou == 0 )
            printf("Elemento nao encontrado. \n");
        return 0;
    }
}

void imprimirOrdem(struct Arvore *raiz, struct Pilha *topo)
{
    if(raiz == NULL)
        printf("Arvore vazia. \n");
    else{
        printf("Em ordem. \n");
        struct Arvore *aux;
        struct Pilha *auxPilha;
        aux=raiz;
        topo= NULL;
        do{
            while (aux!= NULL)
            {
                struct Pilha* novo;
                novo = (struct Pilha*) malloc(sizeof(struct Pilha));
                auxPilha = novo;
                auxPilha->num = aux;
                auxPilha->prox = topo;
                topo = auxPilha;
                aux = aux->esq;
            }
            if(topo != NULL)
            {
                auxPilha= topo;
                printf("%d \n", auxPilha->num->num);
                aux = topo->num->dir;
                topo = topo->prox;
            }
        }while(topo !=NULL || aux != NULL);
    }
}

void imprimirPreOrdem(struct Arvore *raiz, struct Pilha *topo)
{
    if(raiz == NULL)
        printf("Arvore vazia. \n");
    else{
            printf("Pre-ordem. \n");
            struct Arvore *aux;
            struct Pilha *auxPilha;
            aux=raiz;
            topo= NULL;
            do{
                while (aux!= NULL)
                {
                    struct Pilha* novo;
                    novo = (struct Pilha*) malloc(sizeof(struct Pilha));
                    auxPilha = novo;
                    printf("%d \n", aux->num);
                    auxPilha->num = aux;
                    auxPilha->prox = topo;
                    topo = auxPilha;
                    aux = aux->esq;
                }
                if(topo != NULL)
                {
                    auxPilha= topo;
                    topo = topo->prox;
                    aux = auxPilha->num->dir;
            }
        }while(topo != NULL || aux != NULL);
    }
}

void imprimirPosOrdem(struct Arvore *raiz)
{
    if(raiz != NULL){
        imprimirPosOrdem(raiz->esq);
        imprimirPosOrdem(raiz->dir);
        printf("%d\n", raiz->num);
    }
}

int main()
{
    struct Arvore *raiz = NULL; //ponteiro raiz
    struct Pilha *topo;//ponteiro topo pilha
    int op, num=100000, n=0;
    double start, stop, elapsed;

    start = (double) clock() / CLOCKS_PER_SEC;
    for(int i=1; i <= num;i++){
        int valor = rand();

        struct Arvore* novo;
        novo = (struct Arvore*) malloc(sizeof(struct Arvore));
        novo->dir= NULL;
        novo->esq= NULL;
        novo->num = valor;
        if(raiz == NULL){
            raiz = novo;
        }else{
            int achou=0;
            struct Arvore* aux;
            aux=raiz;
            while(achou == 0){
                if(novo->num < aux->num){
                    if(aux->esq == NULL){
                        aux->esq = novo;
                        achou = 1;
                    }else aux=aux->esq;
                }else if(novo->num >= aux->num){
                    if(aux->dir ==NULL){
                        aux->dir = novo;
                        achou = 1;
                    }
                    else aux=aux->dir;
                }
            }
        }
    }
    stop = (double) clock() / CLOCKS_PER_SEC;
    elapsed = stop - start;
    printf("Tempo de insercao: %f\n", elapsed);

//    printf("\nPre Ordem:\n");
//    imprimirPreOrdem(raiz, topo);

//    printf("\nPre Ordem:\n");
//    imprimirPreOrdem(raiz, topo);

//    printf("\nOrdem:\n");
//    imprimirOrdem(raiz, topo);

//    printf("\nPos Ordem:\n");
//    imprimirPosOrdem(raiz);

    printf("\n\nElemento a ser buscado na arvore: \n");
    scanf("%d", &n);
    start = (double) clock() / CLOCKS_PER_SEC;
    buscar(raiz, n);
    stop = (double) clock() / CLOCKS_PER_SEC;
    elapsed = stop - start;
    printf("\nTempo de busca: %f\n", elapsed);

    start = (double) clock() / CLOCKS_PER_SEC;
        if(raiz == NULL)
            printf("Arvore esta vazia. \n");
        else{
                struct Arvore *aux;
                struct Pilha *auxPilha;
                aux=raiz;
                topo= NULL;
            do{
                while(aux != NULL){
                    struct Pilha* novo;
                    novo = (struct Pilha*) malloc(sizeof(struct Pilha));
                    auxPilha = novo;

                    auxPilha->num = aux;
                    auxPilha->prox = topo;
                    topo = auxPilha;
                    aux = aux->esq;
                }
                if(topo != NULL){
                    auxPilha = topo;
                    topo = topo->prox;
                    aux = auxPilha->num->dir;
                }
            }while(topo != NULL || aux != NULL);
                auxPilha = topo;
            while(auxPilha != NULL){

                topo= topo->prox;
                free(topo->num);
                free(auxPilha);
                auxPilha=topo;
            }
            raiz=NULL;
            printf("\n\nArvore esvaziada! \n");
        }
        stop = (double) clock() / CLOCKS_PER_SEC;
        elapsed = stop - start;
        printf("Tempo total em segundos para esvaziar arvore: %f\n", elapsed);

    return 0;
}
