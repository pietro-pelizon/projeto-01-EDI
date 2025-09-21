#ifndef FILA_H
#define FILA_H
#include "stdbool.h"

// A definição da struct foi movida para o arquivo.c
// para encapsular a implementação. O header só precisa
// saber que o tipo 'fila' existe.
typedef struct fila fila;
typedef struct nodeF nodeF;


fila *criaFila();

int insereFila(fila *f, void *item);

nodeF *getInicioFila(fila *f);

nodeF *getFimFila(fila *f);









#endif //FILA_H
