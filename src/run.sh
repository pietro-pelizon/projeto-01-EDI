#!/bin/bash

EXEC="./ted"
BASE="../testes"
SAIDA="../saida"

declare -A TESTES

TESTES["t-0retg-cres"]="d1-seq-raj dsp-cruz-alt"
TESTES["t-0retg-decres"]="d1-seq-raj disp-cruz"
TESTES["t-0rets-circs-cres"]="d1-seq-raj"
TESTES["t-1retg-cres-2"]="dspcentro-2 dspcentro-2-chaco"
TESTES["t-2figs-alet"]="d2-1x1-norte d2-1x1-oeste d2-3x3-lll d2-3x3-nol d2-3x3-norte-longe d2-3x3-norte-prox d2-3x3-oeste-longe d2-3x3-oeste-prox d2-norte-10x7-chaco d2-oeste-10x7-chaco"

for GEO_NOME in "${!TESTES[@]}"; do
    echo "=============================="
    echo " Geo: $GEO_NOME"
    echo "=============================="

    GEO_PATH="$BASE/$GEO_NOME.geo"
    if [ ! -f "$GEO_PATH" ]; then
        echo "  [SKIP] $GEO_NOME.geo não encontrado"
        continue
    fi

    OUT="$SAIDA/$GEO_NOME"
    mkdir -p "$OUT"

    for QRY in ${TESTES[$GEO_NOME]}; do
        QRY_PATH="$BASE/$GEO_NOME/$QRY.qry"
        if [ ! -f "$QRY_PATH" ]; then
            echo "  [SKIP] $QRY.qry não encontrado"
            continue
        fi
        echo -n "  Rodando $QRY... "
        $EXEC -e "$BASE" -f "$GEO_NOME.geo" -o "$OUT" -v "$GEO_NOME-v.via" -q "$GEO_NOME/$QRY.qry" 2>/dev/null
        RET=$?
        if [ $RET -eq 0 ]; then
            echo "[OK]"
        else
            echo "FALHOU (exit code $RET)"
        fi
    done
    echo ""
done

echo "Testes concluídos. Saídas em $SAIDA/"