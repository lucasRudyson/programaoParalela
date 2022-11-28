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
    int inicio; 
    int fim;
    if (linha%NUM_THREADS==0)
    {
        inicio = id*dividir;
        fim = (id+1)*dividir;
    }else if (linha%NUM_THREADS!=0)
    {
        inicio = id*dividir;
        if (id == NUM_THREADS-1){
            fim = linha;
        }else{
            fim = (id+1)*dividir;
        }
        
    }
    
    somatorio[id] = 0;
    printf("thread %d\n",id);
    for (int i = inicio; i < fim; i++){
        for (int j = 0; j < coluna; j++){
            somatorio[id] +=matriz[i][j];
        }
        
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
    int result=0;
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
    for (int i = 0; i < NUM_THREADS; i++)
    {
        result += somatorio[i];
    }
    
    printf("o resultado é %d\n",result);
    desalocarMatriz();
    return 0;
}

