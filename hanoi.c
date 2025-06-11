#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "funcoes.h"

int main() {
    char jogar_novamente;

    do {
        // --- Início de uma nova partida ---
        system("cls");
        printf("Bem-vindo à Torre de Hanoi!\n");
        printf("Escolha a quantidade de discos (1 a 8): ");

        int num_discos;
        // Validação da entrada do usuário
        if (scanf("%d", &num_discos) != 1 || num_discos < 1 || num_discos > 8) {
            printf("Número inválido. Por favor, reinicie o programa e tente novamente.\n");
            return 1;
        }

        // Fase 1: Preparar o jogo
        initialize_towers(num_discos);

        // Fase 2: Executar o jogo
        play_game();

        // Fase 3: Limpar a memória da partida atual
        cleanup_towers();

        printf("\n\nDeseja jogar novamente? (S/N): ");
        scanf(" %c", &jogar_novamente);

    } while (toupper(jogar_novamente) == 'S');

    printf("\nObrigado por jogar! Até a próxima!\n");

    return 0;
}