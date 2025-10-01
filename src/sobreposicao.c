#include "sobreposicao.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

#include <math.h>

bool sobrepoe_circulo_circulo(circulo *c1, circulo *c2);
bool sobrepoe_circulo_retangulo(circulo *c1, retangulo *r);
bool sobrepoe_circulo_linhaOUtexto(circulo *c, linha *l);
bool sobrepoe_retangulo_retangulo(retangulo *r1, retangulo *r2);
bool sobrepoe_linha_linha(linha *l1, linha *l2);
bool sobrepoe_linha_texto(linha *l, texto *t);
bool sobrepoe_retangulo_linha(retangulo *r, linha *l);
void converter_texto_para_linha(texto *t, linha *l_out);

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
    if (tipo1 == CIRCULO && tipo2 == LINHA) {
        return sobrepoe_circulo_linhaOUtexto((circulo*)dados1, (linha*)dados2);
    }
    if (tipo1 == CIRCULO && tipo2 == TEXTO) {
        linha temp_linha;
        converter_texto_para_linha((texto*)dados2, &temp_linha);
        return sobrepoe_circulo_linhaOUtexto((circulo*)dados1, &temp_linha);
    }


    if (tipo1 == RETANGULO && tipo2 == CIRCULO) {
        return sobrepoe_circulo_retangulo((circulo*)dados2, (retangulo*)dados1);
    }
    if (tipo1 == RETANGULO && tipo2 == RETANGULO) {
        return sobrepoe_retangulo_retangulo((retangulo*)dados1, (retangulo*)dados2);
    }
    if (tipo1 == RETANGULO && tipo2 == LINHA) {
        return sobrepoe_retangulo_linha((retangulo*)dados1, (linha*)dados2);
    }
    if (tipo1 == RETANGULO && tipo2 == TEXTO) {
        linha temp_linha;
        converter_texto_para_linha((texto*)dados2, &temp_linha);
        return sobrepoe_retangulo_linha((retangulo*)dados1, &temp_linha);
    }

    if (tipo1 == LINHA && tipo2 == CIRCULO) {
        return sobrepoe_circulo_linhaOUtexto((circulo*)dados2, (linha*)dados1);
    }
    if (tipo1 == LINHA && tipo2 == RETANGULO) {
        return sobrepoe_retangulo_linha((retangulo*)dados2, (linha*)dados1);
    }
    if (tipo1 == LINHA && tipo2 == LINHA) {
        return sobrepoe_linha_linha((linha*)dados1, (linha*)dados2);
    }
    if (tipo1 == LINHA && tipo2 == TEXTO) {
        return sobrepoe_linha_texto((linha*)dados1, (texto*)dados2);
    }

    if (tipo1 == TEXTO && tipo2 == CIRCULO) {
        linha temp_linha;
        converter_texto_para_linha((texto*)dados1, &temp_linha);
        return sobrepoe_circulo_linhaOUtexto((circulo*)dados2, &temp_linha);
    }
    if (tipo1 == TEXTO && tipo2 == RETANGULO) {
        linha temp_linha;
        converter_texto_para_linha((texto*)dados1, &temp_linha);
        return sobrepoe_retangulo_linha((retangulo*)dados2, &temp_linha);
    }
    if (tipo1 == TEXTO && tipo2 == LINHA) {
        return sobrepoe_linha_texto((linha*)dados2, (texto*)dados1);
    }
    if (tipo1 == TEXTO && tipo2 == TEXTO) {
        linha temp1, temp2;
        converter_texto_para_linha((texto*)dados1, &temp1);
        converter_texto_para_linha((texto*)dados2, &temp2);
        return sobrepoe_linha_linha(&temp1, &temp2);
    }

    return false;
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
    double y_max = yRetangulo;

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

static bool ponto_dentro_retangulo(retangulo *r, double px, double py) {
    double rx_min = getXretangulo(r);
    double rx_max = getXretangulo(r) + getLarguraRetangulo(r);

    double ry_min = getYretangulo(r) - getAlturaRetangulo(r); // Topo
    double ry_max = getYretangulo(r);      // Base

    bool dentroX = (px >= rx_min) && (px <= rx_max);
    bool dentroY = (py >= ry_min) && (py <= ry_max);

    return dentroX && dentroY;
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

int orientacao(double px, double py, double qx, double qy, double rx, double ry) {
    double val = (qy - py) * (rx - qx) - (qx - px) * (ry - qy);
    if (fabs(val) < 1e-10) return 0;
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

    linha *linha_do_texto = criaLinha(-1, tx1, ty1, tx2, ty2, "temporario");

    bool resultado = sobrepoe_linha_linha(l, linha_do_texto);

    destrutorLinha(&linha_do_texto);

    return resultado;
}



bool sobrepoe_retangulo_linha(retangulo *r, linha *l) {

    double lx1 = getX1Linha(l);
    double ly1 = getY1Linha(l);
    double lx2 = getX2Linha(l);
    double ly2 = getY2Linha(l);

    if (ponto_dentro_retangulo(r, lx1, ly1) || ponto_dentro_retangulo(r, lx2, ly2)) {
        return true;
    }

    double rx = getXretangulo(r);
    double ry = getYretangulo(r);
    double rw = getLarguraRetangulo(r);
    double rh = getAlturaRetangulo(r);

    double cse_x = rx,      cse_y = ry - rh; // Canto Superior Esquerdo
    double csd_x = rx + rw, csd_y = ry - rh; // Canto Superior Direito
    double cie_x = rx,      cie_y = ry;      // Canto Inferior Esquerdo
    double cid_x = rx + rw, cid_y = ry;      // Canto Inferior Direito

    bool resultado = false;

    linha *borda_cima = criaLinha(-1, cse_x, cse_y, csd_x, csd_y, "temp");
    if (sobrepoe_linha_linha(l, borda_cima)) {
        resultado = true;
    }
    destrutorLinha(&borda_cima);
    if (resultado) return true;


    linha *borda_direita = criaLinha(-1, csd_x, csd_y, cid_x, cid_y, "temp");
    if (sobrepoe_linha_linha(l, borda_direita)) {
        resultado = true;
    }

    destrutorLinha(&borda_direita);
    if (resultado) return true;

    linha *borda_baixo = criaLinha(-1, cid_x, cid_y, cie_x, cie_y, "temp");
    if (sobrepoe_linha_linha(l, borda_baixo)) {
        resultado = true;
    }
    destrutorLinha(&borda_baixo);
    if (resultado) return true;

    linha *borda_esquerda = criaLinha(-1, cie_x, cie_y, cse_x, cse_y, "temp");
    if (sobrepoe_linha_linha(l, borda_esquerda)) {
        resultado = true;
    }

    destrutorLinha(&borda_esquerda);
    if (resultado) return true;

    return false;
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