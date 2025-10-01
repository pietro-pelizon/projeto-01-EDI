cmake_minimum_required(VERSION 3.31)
project(EDI_projeto1 C)

set(CMAKE_C_STANDARD 99)

add_executable(EDI_projeto1
        pilha.c
        pilha.h
        fila.c
        fila.h
        circulo.c
        circulo.h
        retangulo.c
        retangulo.h
        linha.c
        linha.h
        texto.c
        texto.h
        src/carregador.h
        src/svg.c
        src/svg.h
        carregadores.c
        carregadores.h
        disparador.c
        disparador.h
        arena.c
        arena.h
        chao.c
        chao.h
        src/formas.c
        src/formas.h
        main.c
        src/chao.c
        src/chao.h
)
