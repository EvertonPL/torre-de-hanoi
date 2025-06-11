#ifndef FUNCOES_H
#define FUNCOES_H

// --- Definições e Variáveis Globais ---
// A struct é definida aqui para que funcoes.c e hanoi.c (se precisasse)
// "saibam" como uma Torre é composta.
typedef struct {
    int *discos;
    int pos;
    char nome;
} Torre;

extern Torre torreA, torreB, torreC;
extern int n;

// --- Funções Públicas ---
// As únicas 3 funções que main precisa chamar.
void initialize_towers(int quantidade);
void play_game();
void cleanup_towers();

#endif