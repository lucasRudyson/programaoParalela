#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define linha 4
#define coluna 4
#define NUM_THREADS 3
double dividir = linha/NUM_THREADS;
int somatorio[NUM_THREADS];
int **matriz;
int **criar_matriz(){
   int **m = (int **) malloc(sizeof(int *) * linha);
   for(int i=0;i<coluna;i++){
        m[i] = (int *)malloc(sizeof(int) * coluna);
   }
   for (int i =0;i<linha;i++){
    for (int j=0;j<coluna;j++){
        m[i][j]= i;
    }
   }
   return m;
}
// void *p
void *somar(void *p){
    int id = *(int *)p;
    printf("executando a thread %d\n ",id);
    // int id= *(int *)p;
    int inicio = id*dividir; 
    int fim = (id+1)*dividir;
    printf("%d %d\n",inicio,fim);
    for (int i=0;i<linha;i++){
        for(int j=inicio;j<fim;j++)
            somatorio[id] += matriz[i][j]; 
            printf("%d\n",somatorio[id]);
    }
}

void desalocarMatriz(){
    int i;
    for (i =0; i<linha; i++){
        free(matriz[i]);
    }
}

void imprimir(){
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            printf("%d",matriz[i][j]);
        }
        printf("\n");
    }
    
}
int main()
{
    int ids[NUM_THREADS];
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    int rc;
    int i;
    void *status;
    matriz = criar_matriz();
    imprimir();
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
     for (i = 0; i < NUM_THREADS; i++)
    {
        printf("criando thread %d\n",i);
        ids[i] = i;
        rc = pthread_create(&threads[i],&attr,somar, (void *)&ids[i]);
        if(rc){
            printf("Erro na criação da thread\n");
            return(-1);
        }
        
    }
    for(i=0; i< NUM_THREADS;i++){
            rc = pthread_join(threads[i],&status);
            if(rc){
                printf("Erro na espera %d\n", i);
                exit(-1);

            }
        }
    printf("o resultado é %d\n",somatorio[0]+somatorio[1]+somatorio[2]);
    desalocarMatriz();
    return 0;
}

