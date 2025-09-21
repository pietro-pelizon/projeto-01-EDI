//
// Created by pietr on 20/09/2025.
//

#include "circulo.h"
#define PI = 3,1415


typedef struct circulo {
    double diametro;
    double r = diametro/2;
    char corb;
    char corp;
    double ancX, ancY;
    double area;

}circulo;

circulo calcArea(circulo *c, double r) {
    double x = PI;;
    circulo area = x *(r*r);

    return area;

}