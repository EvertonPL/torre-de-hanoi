#include <stdio.h>
#include <math.h>
#include "funcoes.h"

int main() {
    printf("Escolha a quantidade de discos (1 a 8): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 8) {
        printf("Número inválido. O programa será encerrado.\n");
        return 1;
    }

    initialize(n);
    int move_count = 0;

    // Loop principal do jogo, continua enquanto a torre C não estiver completa
    while (posC < n) {
        show();
        char origem, destino;

        printf("Mover de qual torre para qual torre? (ex: A C): ");
        if (scanf(" %c %c", &origem, &destino) != 2) {
            printf("\n>> Entrada inválida! Use o formato 'Letra Letra'. <<\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }

        // A validação e a execução são delegadas às funções de funcoes.c
        if (is_move_valid(origem, destino)) {
            execute_move(origem, destino);
            move_count++;
        } else {
            // A função is_move_valid já imprime a razão do erro.
            printf(" Tente novamente.\n");
        }
    }

    // Mensagem de vitória
    printf("\n*********************************************\n");
    show();
    printf("PARABENS! Voce resolveu a Torre de Hanoi! \n");
    printf("Voce completou em %d movimentos.\n", move_count);
    int min_moves = pow(2, n) - 1;
    printf("O numero minimo de movimentos possivel era %d.\n", min_moves);
    printf("*********************************************\n");

    cleanup();
    printf("\nPressione Enter para sair...");
    while (getchar() != '\n');
    getchar();

    return 0;
}