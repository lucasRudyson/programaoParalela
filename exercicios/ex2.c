#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define linha 2
#define coluna 2
#define NUM_THREADS 2
double dividir = linha/NUM_THREADS;
int somatorio =0;
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
void somar(){
    int id = 0;
    // int id= *(int *)p;
    int inicio = id*dividir; 
    int fim = (id+1)*dividir;
    for(int c=inicio;c<fim;c++){
        // fazer a matriz
        printf("%d\n",c);
        for (int i=0;i<NUM_THREADS;i++){
            for (int j = 0; j < NUM_THREADS; j++)
            {
                printf("entrou1");
                somatorio += matriz[i][j];
            }
            
        }
        
    }
}

void desalocarMatriz(){
    int i;
    for (i =0; i<linha; i++){
        free(matriz[i]);
    }
}

int main()
{
    matriz = criar_matriz();
    somar();
    printf("o resultado é %d\n",somatorio);
    desalocarMatriz();
    return 0;
}

