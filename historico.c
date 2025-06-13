#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"
#include "historico.h"

// No Linux, para strcasecmp, pode ser necessário #include <strings.h>

Historico* inicio = NULL; // É uma boa prática inicializar ponteiros com NULL

// Função para remover o \n do final de uma string lida por fgets
void remover_quebra_de_linha(char* str) {
    str[strcspn(str, "\n")] = 0;
}

void adicionarHistorico(const char* nome_jogador, int movimentos, int discos, const char* data) {
    Historico* novo = malloc(sizeof(Historico));
    if (!novo) return;

    // Garante que o nome e data não tenham quebras de linha
    char nome_limpo[100];
    char data_limpa[11];
    strcpy(nome_limpo, nome_jogador);
    strcpy(data_limpa, data);
    remover_quebra_de_linha(nome_limpo);
    remover_quebra_de_linha(data_limpa);

    strcpy(novo->nome_jogador, nome_limpo);
    novo->movimentos = movimentos;
    novo->discos = discos;
    strcpy(novo->data, data_limpa);
    novo->prox = inicio;
    inicio = novo;
}

void carregarHistorico() {
    FILE *f = fopen("historico_hanoi.txt", "r");
    if (f == NULL) {
        return; // Arquivo ainda não existe, o que é normal na primeira vez
    }

    char nome_jogador[100];
    int movimentos, discos;
    char data[11];

    // Lê linha por linha, garantindo o formato correto
    while (fscanf(f, " %99[^\n]\n%d\n%d\n%10[^\n]\n", nome_jogador, &movimentos, &discos, data) == 4) {
        adicionarHistorico(nome_jogador, movimentos, discos, data);
    }
    fclose(f);
}

void salvarHistorico(const char* nome_jogador, int movimentos, int discos, const char* data) {
    FILE *f = fopen("historico_hanoi.txt", "a");
    if (f == NULL) {
        perror("Erro ao abrir arquivo de historico");
        return;
    }

    // Garante que não haja quebras de linha extras ao salvar
    char nome_limpo[100];
    char data_limpa[11];
    strcpy(nome_limpo, nome_jogador);
    strcpy(data_limpa, data);
    remover_quebra_de_linha(nome_limpo);
    remover_quebra_de_linha(data_limpa);

    fprintf(f, "%s\n%d\n%d\n%s\n", nome_limpo, movimentos, discos, data_limpa);
    fclose(f);
}

void mostrarHistorico() {
    if (inicio == NULL) {
        printf("Nenhum historico para mostrar.\n");
        return;
    }
    printf("\n=============================\n");
    printf("  Historico de Partidas\n");
    printf("=============================\n");
    Historico* atual = inicio;
    while (atual) {
        printf("Jogador: %-20s | Movimentos: %-4d | Discos: %-2d | Data: %s\n",
               atual->nome_jogador, atual->movimentos, atual->discos, atual->data);
        atual = atual->prox;
    }
    printf("=============================\n");
}

void buscarUsuario(const char* nome_jogador) {
    int achou = 0;
    Historico* atual = inicio;
    char nome_busca_limpo[100];
    strcpy(nome_busca_limpo, nome_jogador);
    remover_quebra_de_linha(nome_busca_limpo);

    printf("\nHistorico para o jogador '%s':\n", nome_busca_limpo);
    while(atual != NULL) {
        // strcasecmp não é padrão do C, stricmp é para Windows.
        // Uma alternativa portável é converter ambos para minúsculo/maiúsculo antes de comparar.
        if (strcasecmp(atual->nome_jogador, nome_busca_limpo) == 0) {
            printf(" -> Movimentos: %-4d | Discos: %-2d | Data: %s\n",
                   atual->movimentos, atual->discos, atual->data);
            achou = 1;
        }
        atual = atual->prox;
    }
    if (!achou){
        printf("Nenhum registro encontrado para o jogador '%s'.\n", nome_busca_limpo);
    }
}

void buscarData(const char* data) {
    int achou = 0;
    Historico* atual = inicio;
    char data_busca_limpa[11];
    strcpy(data_busca_limpa, data);
    remover_quebra_de_linha(data_busca_limpa);

    printf("\nHistorico para a data '%s':\n", data_busca_limpa);
    while (atual) {
        if (strcmp(atual->data, data_busca_limpa) == 0) {
            printf(" -> Jogador: %-20s | Movimentos: %-4d | Discos: %-2d\n",
                   atual->nome_jogador, atual->movimentos, atual->discos);
            achou = 1;
        }
        atual = atual->prox;
    }

    if (!achou) {
        printf("Nenhum registro encontrado para a data '%s'.\n", data_busca_limpa);
    }
}