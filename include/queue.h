//Ordem dos turnos, usando uma fila circular
//Quem for rápido ataca primeiro, depois os outros, e assim por diante
//Poderia fazer sem utilizar a fila circular, mas como a ideia é praticar o conceito vamos utilizar ela msm
#ifndef QUEUE_H
#define QUEUE_H
#include "character.h"
typedef struct Queue{
    Character *turns[2];
    int front;
    int size;
}Turn_Queue;
void initQueue(Turn_Queue *q); //inicializa a fila
void insertQueue(Turn_Queue *q, Character *c); //insere um personagem na fila
Character* turnQueue(Turn_Queue *q); //retorna o personagem que está na frente, não remove ele da fila
void cycleQueue(Turn_Queue *q); //faz a fila circular, ou seja, o personagem que estava na frente vai para o final da fila
#endif