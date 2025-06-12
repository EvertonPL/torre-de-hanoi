#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "funcoes.h"
#include "historico.h"

int main() {
    carregarHistorico();

    char jogar_novamente;

    do {
        // --- Início de uma nova partida ---
        system("cls");
        printf("Bem-vindo à Torre de Hanoi!\n");
        printf("Digite seu nome: ");
        char nome_jogador[100];
        fgets(nome_jogador, sizeof(nome_jogador), stdin);
        printf("Digite a data(dd/mm/aaaa): ");
        char data[11];
        fgets(data, sizeof(data), stdin);
        printf("Escolha a quantidade de discos (1 a 8): ");

        int num_discos;
        // Validação da entrada do usuário
        if (scanf("%d", &num_discos) != 1 || num_discos < 1 || num_discos > 8) {
            printf("Número inválido. Por favor, reinicie o programa e tente novamente.\n");
            return 1;
        }

        // Fase 1: Preparar o jogo
        inicializar_torres(num_discos);

        // Fase 2: Executar o jogo
        iniciar_jogo(nome_jogador, data);

        // Fase 3: Limpar a memória da partida atual
        limpar_torres();

        printf("\nDeseja mostrar o histórico das partidas? (S/N): ");
        char opcao;
        scanf(" %c", &opcao);
        while(getchar() != '\n');
        if (toupper(opcao) == 'S') {
            mostrarHistorico();
            printf("Deseja buscar histórico por usuário (U) ou data (D)? Ou qualquer tecla para continuar: ");
            char busca_tipo;
            scanf(" %c", &busca_tipo);
            while(getchar() != '\n');

            if (toupper(busca_tipo) == 'U') {
                char nome_busca[100];
                printf("Digite o nome do jogador para buscar: ");
                fgets(nome_busca, sizeof(nome_busca), stdin);
                buscarUsuario(nome_busca);
            } else if (toupper(busca_tipo) == 'D') {
                char data_busca[11];
                printf("Digite a data para buscar (dd/mm/aaaa): ");
                fgets(data_busca, sizeof(data_busca), stdin);
                buscarData(data_busca);
            }
        }

        printf("\n\nDeseja jogar novamente? (S/N): ");
        scanf(" %c", &jogar_novamente);

    } while (toupper(jogar_novamente) == 'S');

    printf("\nObrigado por jogar! Até a próxima!\n");

    return 0;
}