#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdbool.h>
extern int *A, *B, *C;
extern int posA, posB, posC;
extern int n;
void pushA(int n);
int  popA();
int  peekA();
void pushB(int n);
int  popB();
int  peekB();
void pushC(int n);
int  popC();
int  peekC();
bool is_move_valid(char origem, char destino);
void execute_move(char origem, char destino);
void show();
void initialize(int quantidade);
void cleanup();

#endif