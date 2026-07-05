// Histórico de ações
#ifndef STACK_H
#define STACK_H
#define STACK_MAX 128     // quantidade máxima de ações na pilha
#define STACK_MSG_LEN 256 // tamanho máximo da mensagem de cada ação
typedef struct
{
    char entries[STACK_MAX][STACK_MSG_LEN]; // pilha de mensagens
    int top;                                // índice do topo da pilha
} ActionStack;
;
void stack_init(ActionStack *s);                  // inicializa a pilha, setando o topo para 0
void stack_push(ActionStack *s, const char *msg); // adiciona uma mensagem à pilha,
int stack_pop(ActionStack *s, char *out);         // remove a mensagem do topo da pilha//retorna 1 se removeu
int stack_is_empty(const ActionStack *s);         // verifica se a pilha está vazia, retorna 1 se estiver vazia, 0 caso contrário
#endif                                            // STACK_H