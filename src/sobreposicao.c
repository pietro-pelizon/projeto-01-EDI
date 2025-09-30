#include "sobreposicao.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

#include <math.h>

bool sobrepoe_circulo_circulo(void *dados1, void *dados2);
bool sobrepoe_circulo_retangulo(circulo *c1, retangulo *r);
bool sobrepoe_circulo_linhaOUtexto(circulo *c, linha *l);
bool sobrepoe_retangulo_retangulo(retangulo *r1, retangulo *r2);

static double distancia_quadrada(double x1, double y1, double x2, double y2) {
    double deltaX = x1 - x2;
    double deltaY = y1 - y2;
    return (deltaX * deltaX) + (deltaY * deltaY);
}


bool formasSobrepoem(forma *f1, forma *f2) {
    tipoForma tipo1 = getTipoForma(f1);
    tipoForma tipo2 = getTipoForma(f2);
    void *dados1 = getFormaDados(f1);
    void *dados2 = getFormaDados(f2);

    if (tipo1 == CIRCULO && tipo2 == CIRCULO) {
        return sobrepoe_circulo_circulo((circulo*)dados1, (circulo*)dados2);
    }

    if (tipo1 == CIRCULO && tipo2 == RETANGULO) {
        return sobrepoe_circulo_retangulo((circulo*)dados1, (retangulo*)dados2);
    }

    if (tipo1 == RETANGULO && tipo2 == CIRCULO) {
        return sobrepoe_circulo_retangulo((circulo*)dados2, (retangulo*)dados1);
    }

    if (tipo1 == RETANGULO && tipo2 == RETANGULO) {
        sobrepoe_retangulo_retangulo((retangulo*)dados1, (retangulo*)dados2);
    }

    //continuo amanhã

}

bool sobrepoe_circulo_circulo(circulo *c1, circulo *c2) {
    double x1 = getXCirculo(c1);
    double y1 = getYCirculo(c1);
    double r1 = getRaioCirculo(c1);

    double x2 = getXCirculo(c2);
    double y2 = getYCirculo(c2);
    double r2 = getRaioCirculo(c2);

    double distanciaEntreCentros = distancia_quadrada(x1, y1, x2, y2);

    double somaRaiosAoQuadrado = (r1 + r2) * (r1 + r2);

    return distanciaEntreCentros <= somaRaiosAoQuadrado;

}

bool sobrepoe_circulo_retangulo(circulo *c1, retangulo *r) {
    double xCirculo = getXCirculo(c1);
    double yCirculo = getYCirculo(c1);
    double raio = getRaioCirculo(c1);

    double xRetangulo = getXretangulo(r);
    double yRetangulo = getYretangulo(r);
    double altura = getAlturaRetangulo(r);
    double largura = getLarguraRetangulo(r);

    double x_min = xRetangulo;
    double x_max = xRetangulo + largura;
    double y_min = yRetangulo - altura; // Borda de cima
    double y_max = yRetangulo;      // Borda de baixo

    double px, py;
    if (xCirculo < x_min) {
        px = x_min;
    }

    else if (xCirculo > x_max) {
        px = x_max;
    }

    else {
        px = xCirculo;
    }

    if (yCirculo < y_min) {
        py = y_min;
    }

    else if (yCirculo > y_max) {
        py = y_max;
    }

    else {
        py = yCirculo;
    }

    double distanciaAoQuadrado = distancia_quadrada(xCirculo, yCirculo, px, py);

    return distanciaAoQuadrado <= (raio * raio);

}

bool sobrepoe_circulo_linhaOUtexto(circulo *c, linha *l) {
    double cx = getXCirculo(c);
    double cy = getYCirculo(c);
    double cr = getRaioCirculo(c);

    double lx1 = getX1Linha(l);
    double lx2 = getX2Linha(l);
    double ly1 = getY1Linha(l);
    double ly2 = getY2Linha(l);

    double distP1Linha = distancia_quadrada(cx, cy, lx1, ly1);
    double distP2Linha = distancia_quadrada(cx, cy, lx2, ly2);

    double raioAoQuadrado = cr * cr;

    if (distP1Linha <= raioAoQuadrado || distP2Linha <= raioAoQuadrado) {
        return true;
    }

    double comprimentoAoQuadrado = distancia_quadrada(lx1, ly1, lx2, ly2);

    double t = (((cx - lx1) * (lx2 - lx1)) + ((cy - ly1) * (ly2 - ly1)))/ comprimentoAoQuadrado;

    if (t > 1 || t < 0) {
        return false;
    }

    if (t >= 0 && t <= 1) {
        double px = lx1  + t * (lx2 - lx1);
        double py = ly1 + t * (ly2 - ly1);
        double distanciaAoQuadradoDoCirculo = distancia_quadrada(cx, cy, px, py);

        return distanciaAoQuadradoDoCirculo <= raioAoQuadrado;
    }

    return false;
}

bool sobrepoe_retangulo_retangulo(retangulo *r1, retangulo *r2) {
    double r1x = getXretangulo(r1);
    double r1y = getYretangulo(r1);
    double r1h = getAlturaRetangulo(r1);
    double r1w = getLarguraRetangulo(r1);

    double r2x = getXretangulo(r2);
    double r2y = getYretangulo(r2);
    double r2h = getAlturaRetangulo(r2);
    double r2w = getLarguraRetangulo(r2);

    double intervaloR1x = r1x + r1w;
    double intervaloR2x = r2x + r2w;

    bool sobrepoeX = ((r1x  < intervaloR2x) && (intervaloR1x > r2x));

    double intervaloR1y = r1y - r1h;
    double intervaloR2y = r2y - r2h;

    bool sobrepoeY = ((intervaloR1y < r2y)) && ((r1y > intervaloR2y));

    return sobrepoeX && sobrepoeY;

}

