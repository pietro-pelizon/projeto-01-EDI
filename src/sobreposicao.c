#include "sobreposicao.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#define EPSILON 1e-10
#include <math.h>


/* --- ATENÇÃO ----
 Considerando que é um tópico que gera bastante confusão,
 a implementação do cálculo de sobreposição
 envolvendo retângulos utilizou da lógica
 provida nos testes enviados pelo professor.

 Segue a especificação da implementação abaixo:

    borda esquerda = x_retangulo;
    borda direita = x_retangulo + largura;
    borda superior = y_retangulo;
    borda inferior= y_retangulo + altura;

*/

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

    switch (tipo1) {
        case CIRCULO:
            switch (tipo2) {
                case CIRCULO: return sobrepoe_circulo_circulo((circulo*)dados1, (circulo*)dados2);
                case RETANGULO: return sobrepoe_circulo_retangulo((circulo*)dados1, (retangulo*)dados2);
                case LINHA: return sobrepoe_circulo_linhaOUtexto((circulo*)dados1, (linha*)dados2);
                case TEXTO: return sobrepoe_texto_circulo((texto*)dados2, (circulo*)dados1);
                default: return false;
            }

        case RETANGULO:
            switch (tipo2) {
                case CIRCULO: return sobrepoe_circulo_retangulo((circulo*)dados2, (retangulo*)dados1);
                case RETANGULO: return sobrepoe_retangulo_retangulo((retangulo*)dados1, (retangulo*)dados2);
                case LINHA: return sobrepoe_retangulo_linha((retangulo*)dados1, (linha*)dados2);
                case TEXTO: return sobrepoe_texto_retangulo((texto*)dados2, (retangulo*)dados1);
                default: return false;
            }

        case LINHA:
            switch (tipo2) {
                case CIRCULO: return sobrepoe_circulo_linhaOUtexto((circulo*)dados2, (linha*)dados1);
                case RETANGULO: return sobrepoe_retangulo_linha((retangulo*)dados2, (linha*)dados1);
                case LINHA: return sobrepoe_linha_linha((linha*)dados1, (linha*)dados2);
                case TEXTO: return sobrepoe_linha_texto((linha*)dados1, (texto*)dados2);
                default: return false;
            }

        case TEXTO:
            switch (tipo2) {
                case CIRCULO: return sobrepoe_texto_circulo((texto*)dados1, (circulo*)dados2);
                case RETANGULO: return sobrepoe_texto_retangulo((texto*)dados1, (retangulo*)dados2);
                case LINHA: return sobrepoe_linha_texto((linha*)dados2, (texto*)dados1);
                case TEXTO: return  sobrepoe_texto_texto((texto*)dados1, (texto*)dados2);
                default: return false;
            }

        default: return false;
    }
}

bool sobrepoe_texto_circulo(texto *txt, circulo *circ) {
    linha *temp_linha = criaLinha(-1, 0, 0, 0, 0, "temp", false);
    converter_texto_para_linha(txt, temp_linha);
    bool resultado = sobrepoe_circulo_linhaOUtexto(circ, temp_linha);
    destrutorLinha(temp_linha);
    return resultado;
}

bool sobrepoe_texto_retangulo(texto *txt, retangulo *ret) {
    linha *temp_linha = criaLinha(-1, 0, 0, 0, 0, "temp", false);
    converter_texto_para_linha(txt, temp_linha);
    bool resultado = sobrepoe_retangulo_linha(ret, temp_linha);
    destrutorLinha(temp_linha);
    return resultado;
}

bool sobrepoe_texto_texto(texto *txt1, texto *txt2) {
    linha *temp1 = criaLinha(-1, 0, 0, 0, 0, "temp", false);
    linha *temp2 = criaLinha(-1, 0, 0, 0, 0, "temp", false);
    converter_texto_para_linha(txt1, temp1);
    converter_texto_para_linha(txt2, temp2);
    bool resultado = sobrepoe_linha_linha(temp1, temp2);
    destrutorLinha(temp1);
    destrutorLinha(temp2);
    return resultado;
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
    double y_min = yRetangulo;
    double y_max = yRetangulo + altura;

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
    if (comprimentoAoQuadrado == 0.0) {
        return distP1Linha <= raioAoQuadrado;
    }

    double t = ((cx - lx1) * (lx2 - lx1) + (cy - ly1) * (ly2 - ly1)) / comprimentoAoQuadrado;

    t = fmax(0.0, fmin(1.0, t));

    double px = lx1 + t * (lx2 - lx1);
    double py = ly1 + t * (ly2 - ly1);
    double distanciaAoQuadradoDoCirculo = distancia_quadrada(cx, cy, px, py);

    return distanciaAoQuadradoDoCirculo <= raioAoQuadrado;
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

    double r1_x_min = r1x;
    double r1_x_max = r1x + r1w;
    double r2_x_min = r2x;
    double r2_x_max = r2x + r2w;

    bool sobrepoeX = (r1_x_min < r2_x_max) && (r1_x_max > r2_x_min);

    double r1_y_min = r1y;
    double r1_y_max = r1y + r1h;
    double r2_y_min = r2y;
    double r2_y_max = r2y + r2h;

    bool sobrepoeY = (r1_y_min < r2_y_max) && (r1_y_max > r2_y_min);

    return sobrepoeX && sobrepoeY;
}

int orientacao(double px, double py, double qx, double qy, double rx, double ry) {
    double val = (qx - px) * (ry - py) - (qy - py) * (rx - px);
    if (fabs(val) < EPSILON) return 0;
    return (val > 0) ? 1 : 2;
}

bool pontoEstaNoSegmento(double px, double py, double qx, double qy, double rx, double ry) {
    return (qx <= fmax(px, rx) && qx >= fmin(px, rx) && qy <= fmax(py, ry) && qy >= fmin(py, ry));
}

bool sobrepoe_linha_linha(linha *l1, linha *l2) {
    double l1x1 = getX1Linha(l1);
    double l1y1 = getY1Linha(l1);
    double l1x2 = getX2Linha(l1);
    double l1y2 = getY2Linha(l1);

    double l2x1 = getX1Linha(l2);
    double l2y1 = getY1Linha(l2);
    double l2x2 = getX2Linha(l2);
    double l2y2 = getY2Linha(l2);


    int o1 = orientacao(l1x1, l1y1, l1x2, l1y2, l2x1, l2y1);
    int o2 = orientacao(l1x1, l1y1, l1x2, l1y2, l2x2, l2y2);
    int o3 = orientacao(l2x1, l2y1, l2x2, l2y2, l1x1, l1y1);
    int o4 = orientacao(l2x1, l2y1, l2x2, l2y2, l1x2, l1y2);

    if (o1 != o2 && o3 != o4) {
        return true;
    }

    if (o1 == 0 && pontoEstaNoSegmento(l1x1, l1y1, l2x1, l2y1, l1x2, l1y2)) return true;
    if (o2 == 0 && pontoEstaNoSegmento(l1x1, l1y1, l2x2, l2y2, l1x2, l1y2)) return true;
    if (o3 == 0 && pontoEstaNoSegmento(l2x1, l2y1, l1x1, l1y1, l2x2, l2y2)) return true;
    if (o4 == 0 && pontoEstaNoSegmento(l2x1, l2y1, l1x2, l1y2, l2x2, l2y2)) return true;

    return false;
}

bool sobrepoe_linha_texto(linha *l, texto *t) {
    double xt_ancora = getXTexto(t);
    double yt_ancora = getYTexto(t);
    char ancora_texto = getATexto(t);
    int tamanho_texto = getTamanhoTexto(t);

    double comprimento_texto = 10.0 * tamanho_texto;

    double tx1, ty1, tx2, ty2;

    switch (ancora_texto) {
        case 'i': {
            tx1 = xt_ancora;
            ty1 = yt_ancora;
            tx2 = xt_ancora + comprimento_texto;
            ty2 = yt_ancora;
            break;
        }

        case 'm': {
            tx1 = xt_ancora - comprimento_texto / 2.0;
            ty1 = yt_ancora;
            tx2 = xt_ancora + comprimento_texto / 2.0;
            ty2 = yt_ancora;
            break;
        }

        case 'f': {
            tx1 = xt_ancora - comprimento_texto;
            ty1 = yt_ancora;
            tx2 = xt_ancora;
            ty2 = yt_ancora;
            break;
        }

        default:
            return false;
    }

    linha *linha_do_texto = criaLinha(-1, tx1, ty1, tx2, ty2, "temporario", false);

    bool resultado = sobrepoe_linha_linha(l, linha_do_texto);

    destrutorLinha(linha_do_texto);

    return resultado;
}


bool sobrepoe_retangulo_linha(retangulo *r, linha *l) {
    double lx1 = getX1Linha(l);
    double ly1 = getY1Linha(l);
    double lx2 = getX2Linha(l);
    double ly2 = getY2Linha(l);

    double rx = getXretangulo(r);
    double ry = getYretangulo(r);
    double rw = getLarguraRetangulo(r);
    double rh = getAlturaRetangulo(r);

    double x_min = rx;
    double x_max = rx + rw;
    double y_min = ry;
    double y_max = ry + rh;

    bool p1_dentro = (lx1 >= x_min - EPSILON && lx1 <= x_max + EPSILON &&
                      ly1 >= y_min - EPSILON && ly1 <= y_max + EPSILON);
    bool p2_dentro = (lx2 >= x_min - EPSILON && lx2 <= x_max + EPSILON &&
                      ly2 >= y_min - EPSILON && ly2 <= y_max + EPSILON);

    if (p1_dentro || p2_dentro) {
        return true;
    }


    linha *borda_cima = criaLinha(-1, x_min, y_min, x_max, y_min, "temp", false);
    linha *borda_direita = criaLinha(-1, x_max, y_min, x_max, y_max, "temp", false);
    linha *borda_baixo = criaLinha(-1, x_max, y_max, x_min, y_max, "temp", false);
    linha *borda_esquerda = criaLinha(-1, x_min, y_max, x_min, y_min, "temp", false);

    bool resultado = (sobrepoe_linha_linha(l, borda_cima) ||
                     sobrepoe_linha_linha(l, borda_direita) ||
                     sobrepoe_linha_linha(l, borda_baixo) ||
                     sobrepoe_linha_linha(l, borda_esquerda));

    destrutorLinha(borda_cima);
    destrutorLinha(borda_direita);
    destrutorLinha(borda_baixo);
    destrutorLinha(borda_esquerda);

    return resultado;
}

void converter_texto_para_linha(texto *t, linha *l_out) {
    double xt_ancora = getXTexto(t);
    double yt_ancora = getYTexto(t);
    char ancora_texto = getATexto(t);
    int num_chars = getTamanhoTexto(t);

    double comprimento = 10.0 * num_chars;
    double tx1, ty1, tx2, ty2;

    ty1 = yt_ancora;
    ty2 = yt_ancora;


    switch (ancora_texto) {
        case 'i':
            tx1 = xt_ancora;
            tx2 = xt_ancora + comprimento;
            break;
        case 'm':
            tx1 = xt_ancora - (comprimento / 2.0);
            tx2 = xt_ancora + (comprimento / 2.0);
            break;
        case 'f':
            tx1 = xt_ancora - comprimento;
            tx2 = xt_ancora;
            break;

        default:

            tx1 = xt_ancora;
            tx2 = xt_ancora;
            break;
    }

    setX1Linha(l_out, tx1);
    setY1Linha(l_out, ty1);
    setX2Linha(l_out, tx2);
    setY2Linha(l_out, ty2);
}
