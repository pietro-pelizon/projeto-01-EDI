//
// Created by pietr on 20/09/2025.
//

#include "circulo.h"
#define PI 3.14159265


typedef struct circulo {
    double raio;
    char corB[10];
    char corP[10];
    double ancX, ancY;
    double area;

}circulo;

double calcAreaCirculo(circulo *c) {
    c -> area = PI * ((c -> raio) * (c -> raio));
    return c -> area;

}