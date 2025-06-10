#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <ctype.h> 

#include "funcoes.h"

// Ponteiros para as torres
int *A;
int *B;
int *C;

// Posição do topo de cada torre
int posA = 0;
int posB = 0;
int posC = 0;
int n; // Número de discos

// --- Funções de manipulação da Torre A ---
void pushA(int n) { A[posA++] = n; }
int popA() { return A[--posA]; }
int peekA() { return A[posA - 1]; }

// --- Funções de manipulação da Torre B ---
void pushB(int n) { B[posB++] = n; }
int popB() { return B[--posB]; }
int peekB() { return B[posB - 1]; }

// --- Funções de manipulação da Torre C ---
void pushC(int n) { C[posC++] = n; }
int popC() { return C[--posC]; }
int peekC() { return C[posC - 1]; }

// --- Funções Utilitárias ---

void show() {
    int i;
    printf("\n--- TORRES ---\n");
    printf("A: ");
    for (i = 0; i < posA; i++) { printf("%d ", A[i]); }
    printf("\nB: ");
    for (i = 0; i < posB; i++) { printf("%d ", B[i]); }
    printf("\nC: ");
    for (i = 0; i < posC; i++) { printf("%d ", C[i]); }
    printf("\n--------------\n");
}

void initialize(int quantidade) {
    n = quantidade;
    posA = posB = posC = 0;
    A = (int*)malloc(n * sizeof(int));
    B = (int*)malloc(n * sizeof(int));
    C = (int*)malloc(n * sizeof(int));
    for (int i = n; i >= 1; i--) {
        pushA(i);
    }
}

void cleanup() {
    free(A);
    free(B);
    free(C);
}

// Funções de movimento das torres

bool is_move_valid(char origem, char destino) {
    origem = toupper(origem);
    destino = toupper(destino);

    if (origem == destino) {
        printf("\n>> MOVIMENTO INVÁLIDO: A torre de origem e destino não podem ser a mesma.");
        return false;
    }
    if (origem < 'A' || origem > 'C' || destino < 'A' || destino > 'C') {
        printf("\n>> MOVIMENTO INVÁLIDO: Torre não existe. Use A, B ou C.");
        return false;
    }

    int pos_origem = (origem == 'A') ? posA : ((origem == 'B') ? posB : posC);
    if (pos_origem == 0) {
        printf("\n>> MOVIMENTO INVÁLIDO: A torre de origem '%c' está vazia.", origem);
        return false;
    }

    int pos_destino = (destino == 'A') ? posA : ((destino == 'B') ? posB : posC);
    if (pos_destino == 0) {
        return true; // Sempre pode mover para uma torre vazia
    }

    int disco_origem = (origem == 'A') ? peekA() : ((origem == 'B') ? peekB() : peekC());
    int disco_destino = (destino == 'A') ? peekA() : ((destino == 'B') ? peekB() : peekC());

    if (disco_origem > disco_destino) {
        printf("\n>> MOVIMENTO INVÁLIDO: Não é possível colocar um disco maior sobre um menor.");
        return false;
    }

    return true; // O movimento é válido
}

void execute_move(char origem, char destino) {
    origem = toupper(origem);
    destino = toupper(destino);
    int disco_movido;

    switch (origem) {
        case 'A': disco_movido = popA(); break;
        case 'B': disco_movido = popB(); break;
        case 'C': disco_movido = popC(); break;
    }

    switch (destino) {
        case 'A': pushA(disco_movido); break;
        case 'B': pushB(disco_movido); break;
        case 'C': pushC(disco_movido); break;
    }
}