#ifndef FUNCOES_H
#define FUNCOES_H


// struct do nó da pilha
typedef struct Node {
    int discos;
    struct Node *prox;
} Node;

// struct da torre
typedef struct {
    Node *top;
    char nome;
} Torre;

extern Torre torreA, torreB, torreC;
extern int n;

// --- Funções Públicas ---
// As únicas 3 funções que main precisa chamar.
void inicializar_torres(int quantidade);
void iniciar_jogo(const char* nome_jogador, const char* data);
void limpar_torres();
void mostrar_torres();
int altura_torre(const Torre* torre);
int disco_no_nivel(const Torre* torre, int nivel);
int validar_movimento(Torre *origem, Torre *destino);
void executar_movimento(Torre *origem, Torre *destino);
Torre* torre_por_nome(char nome);
void push(Torre *torre, int discos);
int pop(Torre *torre);
void liberar_pilha(Torre *torre);
void imprimir_torre(const Torre* t, int nivel, int n_max);

#endif