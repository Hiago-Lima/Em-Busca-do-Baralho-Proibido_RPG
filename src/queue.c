#include <stdio.h>
#include <string.h> // pra usar memset, que é uma função que preenche um bloco de memória com um valor específico, nesse caso 0, para evitar lixo de memória
#include "queue.h"
void initqueue(Turn_Queue *q)
{
    memset(q->turns, 0, sizeof(q->turns)); // evita lixo de memória _(ptr, valor a ser definido, tamanho do bloco de memória)
    q->front = 0;
    q->size = 0;
}
void insertqueue(Turn_Queue *q, Character *c)
{
    if (q->size >= QUEUE_MAX)
        return;

    /* Encontra a posição onde este personagem deve entrar */
    int pos = q->size; /* por padrão entra no fim */
    for (int i = 0; i < q->size; i++)
    {
        int idx = (q->front + i) % QUEUE_MAX;
        if (c->spd > q->turns[idx]->spd)
        {
            pos = i; /* entra antes de quem é mais lento */
            break;
        }
    }

    /* Abre espaço deslocando os elementos a partir de `pos` */
    for (int i = q->size; i > pos; i--)
    {
        int dst = (q->front + i) % QUEUE_MAX;
        int src = (q->front + i - 1) % QUEUE_MAX;
        q->turns[dst] = q->turns[src];
    }

    q->turns[(q->front + pos) % QUEUE_MAX] = c;
    q->size++;
}

/* Retorna quem está na frente sem remover */
Character *queue_peek(const Turn_Queue *q)
{
    if (q->size == 0)
        return NULL;
    return q->turns[q->front];
}

/* Quem estava na frente agiu — vai para o fim da fila */
void queue_cycle(Turn_Queue *q)
{
    if (q->size == 0)
        return;

    /* Guarda quem estava na frente */
    Character *acted = q->turns[q->front];

    /* Avança o front (descarta quem agiu da frente) */
    q->front = (q->front + 1) % QUEUE_MAX;
    q->size--;

    /* Reinsere no fim */
    int tail = (q->front + q->size) % QUEUE_MAX;
    q->turns[tail] = acted;
    q->size++;
}
