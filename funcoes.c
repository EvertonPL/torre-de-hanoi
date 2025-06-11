#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "funcoes.h"

// --- DEFINIÇÃO DAS VARIÁVEIS GLOBAIS ---
Torre torreA, torreB, torreC;
int n;

// --- PROTÓTIPOS DE FUNÇÕES ESTÁTICAS (PRIVADAS AO ARQUIVO) ---
static void show_towers();
static bool is_move_valid(Torre *origem, Torre *destino);
static void execute_move(Torre *origem, Torre *destino);
static Torre* get_tower_by_name(char nome);

// --- IMPLEMENTAÇÃO DAS FUNÇÕES PÚBLICAS (Declaradas no .h) ---

void initialize_towers(int quantidade) {
    n = quantidade;
    torreA = (Torre){.nome = 'A', .pos = 0, .discos = malloc(n * sizeof(int))};
    torreB = (Torre){.nome = 'B', .pos = 0, .discos = malloc(n * sizeof(int))};
    torreC = (Torre){.nome = 'C', .pos = 0, .discos = malloc(n * sizeof(int))};

    for (int i = n; i >= 1; i--) {
        torreA.discos[torreA.pos++] = i;
    }
}

void cleanup_towers() {
    free(torreA.discos);
    free(torreB.discos);
    free(torreC.discos);
}

// função que inicia o jogo
void play_game() {
    int move_count = 0;

    // Loop principal do jogo, termina quando a torre C está cheia
    while (torreC.pos < n) {
        show_towers();
        char nome_origem, nome_destino;

        printf("Mover de qual torre para qual torre? (ex: A C): ");
        if (scanf(" %c %c", &nome_origem, &nome_destino) != 2) {
            printf("\n>> Entrada inválida! Use o formato 'Letra Letra'. <<\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }

        Torre *p_origem = get_tower_by_name(toupper(nome_origem));
        Torre *p_destino = get_tower_by_name(toupper(nome_destino));

        if (is_move_valid(p_origem, p_destino)) {
            execute_move(p_origem, p_destino);
            move_count++;
        } else {
            printf(" Tente novamente.\n");
        }
    }

    // Mensagem de vitória
    printf("\n*********************************************\n");
    show_towers();
    printf("PARABENS! Voce resolveu a Torre de Hanoi! \n");
    printf("Voce completou em %d movimentos.\n", move_count);
    int min_moves = pow(2, n) - 1;
    printf("O numero minimo de movimentos possivel era %d.\n", min_moves);
    printf("*********************************************\n");
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES ESTÁTICAS (PRIVADAS) ---

static void print_tower_level(const Torre* t, int level, int n_max) {
    int tower_width = 2 * n_max - 1;
    if (level < t->pos) {
        int disk_size = t->discos[level];
        int hashes = 2 * disk_size - 1;
        int spaces = (tower_width - hashes) / 2;
        for (int s = 0; s < spaces; s++) { printf(" "); }
        for (int h = 0; h < hashes; h++) { printf("#"); }
        for (int s = 0; s < spaces; s++) { printf(" "); }
    } else {
        for (int s = 0; s < n_max - 1; s++) { printf(" "); }
        printf("|");
        for (int s = 0; s < n_max - 1; s++) { printf(" "); }
    }
}

static void show_towers() {
    printf("\n");
    for (int i = n - 1; i >= 0; i--) {
        print_tower_level(&torreA, i, n);
        printf("   ");
        print_tower_level(&torreB, i, n);
        printf("   ");
        print_tower_level(&torreC, i, n);
        printf("\n");
    }
    int tower_width = 2 * n - 1;
    for (int t = 0; t < 3; t++) {
        for (int w = 0; w < tower_width; w++) { printf("="); }
        if (t < 2) { printf("   "); }
    }
    printf("\n");
    for (int t = 0; t < 3; t++) {
        for (int s = 0; s < n - 1; s++) { printf(" "); }
        printf("%c", 'A' + t);
        for (int s = 0; s < n - 1; s++) { printf(" "); }
        if (t < 2) { printf("   "); }
    }
    printf("\n\n");
}

static Torre* get_tower_by_name(char nome) {
    switch (nome) {
        case 'A': return &torreA;
        case 'B': return &torreB;
        case 'C': return &torreC;
        default: return NULL;
    }
}

static bool is_move_valid(Torre *origem, Torre *destino) {
    if (!origem || !destino) {
        printf("\n>> MOVIMENTO INVÁLIDO: Torre não existe. Use A, B ou C.");
        return false;
    }
    if (origem == destino) {
        printf("\n>> MOVIMENTO INVÁLIDO: As torres de origem e destino devem ser diferentes.");
        return false;
    }
    if (origem->pos == 0) {
        printf("\n>> MOVIMENTO INVÁLIDO: A torre de origem '%c' está vazia.", origem->nome);
        return false;
    }
    if (destino->pos > 0 && (origem->discos[origem->pos-1] > destino->discos[destino->pos-1])) {
        printf("\n>> MOVIMENTO INVÁLIDO: Não é possível colocar um disco maior sobre um menor.");
        return false;
    }
    return true;
}

static void execute_move(Torre *origem, Torre *destino) {
    destino->discos[destino->pos++] = origem->discos[--origem->pos];
}