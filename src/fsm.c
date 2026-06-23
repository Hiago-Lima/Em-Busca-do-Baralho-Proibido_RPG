#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fsm.h"

void fsm_init(FSM *fsm, FSMState initial_state)
{
    const char *labels[STATE_COUNT] = {// state_count = 3
                                       "ATACAR", "ATAQUE FORTE", "DEFENDER"};

    for (int i = 0; i < STATE_COUNT; i++) // ate 3
    {
        fsm->nodes[i].id = (FSMState)i;              // cast transforma o int i em FSMState, que é um enum
        fsm->nodes[i].edges = NULL;                  // sem aresta
        strncpy(fsm->nodes[i].label, labels[i], 31); // copia o label do estado para o nó, com limite de 31 caracteres o nome
    }

    fsm->current = initial_state; // define o estado atual do inimigo como o estado inicial especificado
}

void fsm_add_edge(FSM *fsm, FSMState from, FSMState to, FSMConditionFn condition, int priority)
{
    FSMEdge *edge = (FSMEdge *)malloc(sizeof(FSMEdge)); // aloca memória para a nova aresta
    edge->to = to;                                      // define o estado de destino da aresta
    edge->condition = condition;                        // define a condição para a transição
    edge->priority = priority;                          // define a prioridade da aresta
    edge->next = NULL;

    FSMEdge **cur = &fsm->nodes[from].edges; // ponteiro para o ponteiro da primeira aresta do nó de origem
    while (*cur && (*cur)->priority >= priority)
        cur = &(*cur)->next;

    edge->next = *cur;
    *cur = edge; // insere a nova aresta na lista de arestas do nó de origem, mantendo a ordem de prioridade
}
FSMState fsm_update(FSM *fsm, const FSMContext *ctx)
{
    FSMNode *node = &fsm->nodes[fsm->current];

    for (FSMEdge *e = node->edges; e != NULL; e = e->next)
    {
        if (e->condition(ctx))
        {
            fsm->current = e->to; // atualiza o estado atual do inimigo para o estado de destino da aresta
            return fsm->current;
        }
    }

    return fsm->current; // se nenhuma condição for atendida, mantém o estado atual do inimigo
}

const char *fsm_current_label(const FSM *fsm)
{
    return fsm->nodes[fsm->current].label; // retorna o rótulo legível do estado atual do inimigo no FSM
}

void fsm_destroy(FSM *fsm)
{
    for (int i = 0; i < STATE_COUNT; i++)
    {
        FSMEdge *e = fsm->nodes[i].edges;
        while (e)
        {
            FSMEdge *next = e->next;
            free(e);
            e = next;
        }
        fsm->nodes[i].edges = NULL;
    }
}
