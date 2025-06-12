#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "funcoes.h"

// --- DEFINIÇÃO DAS VARIÁVEIS GLOBAIS ---
Torre torreA, torreB, torreC;
int n;

// --- PROTÓTItop DE FUNÇÕES ESTÁTICAS (PRIVADAS AO ARQUIVO) ---
void mostrar_torres();
int altura_torre(const Torre* torre);
int disco_no_nivel(const Torre* torre, int nivel);
int validar_movimento(Torre *origem, Torre *destino);
void executar_movimento(Torre *origem, Torre *destino);
Torre* torre_por_nome(char nome);
void push(Torre *torre, int discos);
int pop(Torre *torre);
void liberar_pilha(Torre *torre);
void imprimir_torre(const Torre* t, int level, int n_max);


// --- IMPLEMENTAÇÃO DAS FUNÇÕES PÚBLICAS (Declaradas no .h) ---

void inicializar_torres(int quantidade) {
    n = quantidade;
    torreA.top = NULL; torreA.nome = 'A';
    torreB.top = NULL; torreB.nome = 'B';
    torreC.top = NULL; torreC.nome = 'C';

    for (int i = n; i >= 1; i--) {
        push(&torreA, i);
    }
}

void limpar_torres() {
    liberar_pilha(&torreA);
    liberar_pilha(&torreB);
    liberar_pilha(&torreC);
}

// função que inicia o jogo
void iniciar_jogo() {
    int movimentos = 0;

    // Loop principal do jogo, termina quando a torre C está cheia
    while (altura_torre(&torreC) < n) {
        mostrar_torres();
        char nome_origem, nome_destino;

        printf("Mover de qual torre para qual torre? (ex: A C): ");
        if (scanf(" %c %c", &nome_origem, &nome_destino) != 2) {
            printf("\n>> Entrada inválida! Use o formato 'Letra Letra'. <<\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }

        Torre *p_origem = torre_por_nome(toupper(nome_origem));
        Torre *p_destino = torre_por_nome(toupper(nome_destino));

        if (validar_movimento(p_origem, p_destino)) {
            executar_movimento(p_origem, p_destino);
            movimentos++;
        } else {
            printf(" Tente novamente.\n");
        }
    }

    // Mensagem de vitória
    printf("\n*********************************************\n");
    mostrar_torres();
    printf("PARABENS! Voce resolveu a Torre de Hanoi! \n");
    printf("Voce completou em %d movimentos.\n", movimentos);
    int min_moves = pow(2, n) - 1;
    printf("O numero minimo de movimentos topsivel era %d.\n", min_moves);
    printf("*********************************************\n");
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES ESTÁTICAS (PRIVADAS) ---

void push(Torre *torre, int discos) {
    Node *novo = malloc(sizeof(Node));
    novo->discos = discos;
    novo->prox = torre->top;
    torre->top = novo;
}

int pop(Torre *torre) {
    if(torre->top) {
    Node *top_atual = torre->top;
    int valor = top_atual->discos;
    torre->top = top_atual->prox;
    free(top_atual);
    return valor;
    }
}

void liberar_pilha(Torre *torre) {
    Node *atual = torre->top;
    while (atual) {
        Node *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    torre->top = NULL;
}

void imprimir_torre(const Torre* t, int nivel, int n_max) {
    int largura_torre = 2 * n_max - 1;
    int disco = disco_no_nivel(t, nivel);
    if (disco > 0) {
        int hashtag = 2 * disco - 1;
        int espaco = (largura_torre - hashtag) / 2;
        for (int s = 0; s < espaco; s++) { printf(" "); }
        for (int h = 0; h < hashtag; h++) { printf("#"); }
        for (int s = 0; s < espaco; s++) { printf(" "); }
    } else {
        for (int s = 0; s < n_max - 1; s++) { printf(" "); }
        printf("|");
        for (int s = 0; s < n_max - 1; s++) { printf(" "); }
    }
}

void mostrar_torres() {
    printf("\n");
    for (int i = n - 1; i >= 0; i--) {
        imprimir_torre(&torreA, i, n);
        printf("   ");
        imprimir_torre(&torreB, i, n);
        printf("   ");
        imprimir_torre(&torreC, i, n);
        printf("\n");
    }
    int largura_torre = 2 * n - 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < largura_torre; j++) { printf("="); }
        if (i < 2) { printf("   "); }
    }
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n - 1; j++) { printf(" "); }
        printf("%c", 'A' + i);
        for (int i = 0; i < n - 1; i++) { printf(" "); }
        if (i < 2) { printf("   "); }
    }
    printf("\n\n");
}

Torre* torre_por_nome(char nome) {
    switch (nome) {
        case 'A': return &torreA;
        case 'B': return &torreB;
        case 'C': return &torreC;
        default: return NULL;
    }
}

int validar_movimento(Torre *origem, Torre *destino) {
    if (!origem || !destino) {
        printf("\n>> MOVIMENTO INVÁLIDO: Torre não existe. Use A, B ou C.");
        return 0;
    }
    if (origem == destino) {
        printf("\n>> MOVIMENTO INVÁLIDO: As torres de origem e destino devem ser diferentes.");
        return 0;
    }
    if (origem->top == NULL) {
        printf("\n>> MOVIMENTO INVÁLIDO: A torre de origem '%c' está vazia.", origem->nome);
        return 0;
    }
    if (destino->top != NULL && origem->top->discos > destino->top->discos) {
        printf("\n>> MOVIMENTO INVÁLIDO: Não é topsível colocar um discos maior sobre um menor.");
        return 0;
    }
    return 1;
}

void executar_movimento(Torre *origem, Torre *destino) {
    int discos = pop(origem);
    push(destino, discos);
}

int altura_torre(const Torre* torre) {
    int altura = 0;
    Node *atual = torre->top;
    while (atual) {
        altura++;
        atual = atual->prox;
    }
    return altura;
}

int disco_no_nivel(const Torre* torre, int nivel) {
    int altura = altura_torre(torre);
    int index = altura - nivel - 1;
    Node *atual = torre->top;
    int i = 0;
    while (atual) {
        if (i == index) 
            return atual->discos;
        atual = atual->prox;
        i++;
    }
    return 0;
}