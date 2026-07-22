<div align="center">

# Projeto 01 - Estrutura de Dados (EDI)

![Autor](https://img.shields.io/badge/Autor-Pietro%20Fernando%20Pelizon-maroon)
![C99](https://img.shields.io/badge/Language-C99-blue)
![Build](https://img.shields.io/badge/Makefile-GCC-green)
![Data Structures](https://img.shields.io/badge/ED-Queue%20%7C%20Stack-orange)

</div>

## Estrutura do Repositório

```text
.
├── docs/              # PDFs com as especificações do trabalho
├── include/           # Arquivos de cabeçalho (.h)
├── src/               # Implementações (.c), Makefile e run.sh
├── testes/            # Arquivos de entrada (.geo e .qry)
└── README.md          # Documentação do repositório
```

## Sobre o Projeto

Este projeto, denominado **TED** (no executável), é um simulador de bocha utilizando formas geométricas que implementa e manipula estruturas de dados fundamentais (Filas e Pilhas) para gerenciar essas formas geométricas num cenário (arena e chão).

O sistema lê arquivos de entrada (`.geo` e `.qry`) para configurar o ambiente e executar comandos, gerando como saída arquivos gráficos vetoriais (`.svg`) e relatórios de texto (`.txt`) detalhando as interações e colisões entre os objetos.

### Principais Funcionalidades

 * **Manipulação de Formas Geométricas:** Suporte para Círculos, Retângulos, Linhas e Texto, com gestão de atributos como coordenadas, dimensões, cores e estilos de fonte.
  * **TADs Genéricos:** Implementação de estruturas de dados genéricas (`void*`):
      * **Fila (Queue):** Utilizada para o "Chão" (armazenamento inicial) e para a "Arena" (objetos ativos).
      * **Pilha (Stack):** Utilizada nos "Carregadores" para gerir munição (LIFO).
  * **Sistema de Disparo:** Mecânica de carregadores e disparadores que movem formas do chão para a arena.
  * **Deteção de Colisões:** Algoritmos matemáticos para verificar sobreposição entre todas as formas suportadas (ex: Círculo vs Retângulo, Linha vs Texto, etc.).
  * **Regras de Combate:**
      * Se a forma A colide com B e `Área(A) < Área(B)`: A é "esmagada" (destruída) e gera pontuação.
      * Se a forma A colide com B e `Área(A) ≥ Área(B)`: A modifica as cores de B e pode ser clonada.
  * **Saída Gráfica:** Geração de arquivos `(.svg)` que representam visualmente o estado inicial e final da simulação.

## Compilação

O projeto inclui um `Makefile` para facilitar a compilação. Certifique-se de ter o `gcc` e o `make` instalados.

* Para compilar o projeto, é necessário executar:

```bash
cd src && make
```

Isto irá gerar o executável chamado **`ted`** dentro da pasta `src` e os arquivos `(*.o)` na pasta `build`.

* Para limpar os arquivos objeto (`*.o`) e o executável, execute o seguinte comando:

```bash
make clean
```

## Como Executar

 A execução do programa requer parâmetros de linha de comando para indicar os diretórios e pastas de entrada/saída.
   

**Sintaxe:**

```bash
./ted -e [dir_entrada] -f [arquivo.geo] -o [dir_saida] -q [arquivo.qry]
```

**Automação da execução:**

Pode se utilizar o script `(.sh)` provido no repositório para executar todos os testes de uma vez.

O seguinte comando deve ser executado após a compilação:

```bash
chmod +x run.sh && ./run.sh
```

Isso retira o processo de citar arquivo por arquivo corretamente. O único pré-requisito é que a pasta `testes` esteja presente na raiz do projeto, contendo todos os arquivos `(.geo)/(.qry)`.


**Parâmetros:**

  * `-e`: (Opcional) Caminho base para o diretório de entrada.
  * `-f`: (Obrigatório) Nome do arquivo de geometria (`.geo`).
  * `-o`: (Obrigatório) Caminho para o diretório onde os arquivos de saída (`.svg`, `.txt`) serão gravados.
  * `-q`: (Opcional) Nome do arquivo de consultas/comandos (`.qry`).
  * `-h, --help`: Exibe uma mensagem contendo as informações necessárias para executar o programa.

**Exemplo de uso:**

```bash
./ted -e entrada -f exp1.geo -o saida -q exp1.qry
```

## Estrutura dos arquivos de Entrada

### Arquivo `(.geo)`

Define as formas iniciais que são colocadas no "Chão".

| Comando | Parâmetros                      | Descrição                            |
|:--------|:--------------------------------|:-------------------------------------|
| `c`     | `id x y r corb corp`            | Cria um Círculo                      |
| `r`     | `id x y w h corb corp`          | Cria um Retângulo                    |
| `l`     | `id x1 y1 x2 y2 cor`            | Cria uma Linha                       |
| `t`     | `id x y corb corp ancora texto` | Cria um Texto                        |
| `ts`    | `familia peso tamanho`          | Define o estilo do texto subsequente |

### Arquivo `(.qry)`

Define os comandos da Bocha Geométrica.

| Comando | Parâmetros                        | Descrição                                          |
|:--------|:----------------------------------|:---------------------------------------------------|
| `pd`    | `id x y`                          | Posiciona um Disparador                            |
| `lc`    | `id n`                            | Carrega um Carregador com `n` formas do chão       |
| `atch`  | `id_disp id_carr_dir id_carr_esq` | Acopla carregadores a um disparador                |
| `shft`  | `id_disp lado n`                  | Move munição para a posição de disparo             |
| `dsp`   | `id_disp dx dy`                   | Dispara uma forma                                  |
| `rjd`   | `d [e/d]  dx dy ix iy`            | Dispara uma rajada de formas                       |
| `calc`  | *-*                               | Processa a Arena (colisões, pontuação e relatório) |


## Estrutura do Código (Módulos)

  * **`main.c`**: Ponto de entrada, orquestra a leitura de argumentos e o fluxo principal.
  * **`arena.c/h`**: Gerencia a fila de formas ativas e lógica de interação/colisão.
  * **`chao.c/h`**: Gerencia a fila de formas passivas (inventário).
  * **`carregadores.c/h`**: Implementa a lógica de carregamento usando pilhas.
  * **`disparador.c/h`**: Gerencia a mecânica de disparo e acoplamento de carregadores.
  * **`processaGeo.c/h` & `processaQry.c/h`**: Interpretadores dos arquivos de entrada.
  * **`sobreposicao.c/h`**: Biblioteca matemática para verificar interseções entre formas.
  * **`svg.c/h`**: Responsável por desenhar as formas no formato `(.svg)`.
  * **`formas.c/h`**: Wrapper genérico para lidar com diferentes tipos de formas (polimorfismo).

