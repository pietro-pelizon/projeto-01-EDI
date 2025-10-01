#include <stdio.h>

int main() {
    int a = 0xA; // 10
    int b = 0x5; // 5

    int soma = a + b;      // 10 + 5 = 15 (0xF)
    int subtracao = a - b; // 10 - 5 = 5 (0x5)
    int multiplicacao = a * b; // 10 * 5 = 50 (0x32)
    int divisao = a / b;   // 10 / 5 = 2 (0x2)

    printf("Soma: %d\n", soma);
    printf("Subtração: %d\n", subtracao);
    printf("Multiplicação: %d\n", multiplicacao);
    printf("Divisão: %d\n", divisao);

    return 0;
}
