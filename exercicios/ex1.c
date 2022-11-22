#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define NUM_THREADS 2
#define x 1
double f[NUM_THREADS];


void *calcular(void *vez){
    int p = *(int *)vez;
    if(p==0){
        printf("Calculando f1\n");
        f[p]= pow(sin(x),3);
    }else if(p==1){
        printf("Calculando f2\n");
        f[p]=sqrt(cos(x));
    }else{
        printf("impossivel calcular");
    }
    pthread_exit(NULL);
}

int main()
{
    int ids[NUM_THREADS];
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    int rc;
    int i;
    void *status;
    /*Cria e inicializa um atributo para a thread*/
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for (i = 0; i < NUM_THREADS; i++)
    {
        printf("criando thread %d\n",i);
        ids[i] = i;
        rc = pthread_create(&threads[i],&attr,calcular, (void *)&ids[i]);
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
    printf("Resultado da soma das funcões é %f\n",f[0]+f[1]);
    return 0;
}
