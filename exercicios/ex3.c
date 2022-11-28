#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



void validar(){
    int num;
    int resultado=0;
    for (int i = 2; i <= num / 2; i++) {
        if (num % i == 0) {
        resultado++;
        break;
    }

    if (resultado == 0)
        printf("%d é um número primo\n", num);
    else
        printf("%d não é um número primo\n", num);
    

 }
}