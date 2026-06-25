// o comportamento propriamente dito usando o FSM
#ifndef FSM_H
#define FSM_H
#include <stdio.h>
#include <stdlib.h>
#include "character.h"

// um no representa um estado do FSM, e cada no tem uma lista de arestas
// arestas que possuem condições para ir para outro estado, e cada aresta tem uma prioridade
typedef enum
{						 // enum é so uma enumeração atk =0 ,atk forte = 1 e etc
						 // aqui é so como se fosse um vetor de numeros
	STATE_ATTACK = 0,	 // atk
	STATE_STRONG_ATTACK, // atk forte
	STATE_DEFEND,		 // defender
	STATE_COUNT			 // (total) msm coisa que #define STATE_COUNT "qualquer numero", no caso aq 3
} FSMState;				 // so estado
typedef struct
{
	const Character *self;							  /* O próprio inimigo */
	const Character *player;						  /* O jogador         */
} FSMContext;										  // contexto do FSM, que contém ponteiros para o inimigo e o jogador
typedef int (*FSMConditionFn)(const FSMContext *ctx); // ponteiro de função que recebe um ponteiro para o contexto e retorna um inteiro (0 ou 1) indicando se a condição é atendida ou não
typedef struct FSMEdge
{							  // aresta do grafo,
	FSMState to;			  // aq eu troquei o tipo ja que o destino agr State é um enum, então o destino é um estado do FSM
	FSMConditionFn condition; // condição para ir para o próximo estado
	int priority;
	struct FSMEdge *next; // proxima aresta, agr como FSMEdge
} FSMEdge;				  // aresta do grafo, que representa uma transição de estado no FSM

typedef struct
{ // no do grafo, que representa um estado no FSM e contém informações sobre o estado, como seu identificador, um rótulo legível e uma lista de arestas de saída
	FSMState id;
	char label[32]; /* Nome legível ex: "ATACAR" */
	FSMEdge *edges; /* Lista de arestas saindo deste nó */
} FSMNode;

// grafo completo do FSM, que contém um array de nós (um para cada estado) e o estado atual do inimigo
typedef struct
{
	FSMNode nodes[STATE_COUNT]; /* Um nó por estado          */
	FSMState current;			/* Estado atual do inimigo   */
} FSM;

void fsm_init(FSM *fsm, FSMState initial_state); // inicializa o FSM com o estado inicial especificado, definindo o estado atual do inimigo e inicializando as arestas de cada nó como NULL

void fsm_add_edge(FSM *fsm, FSMState from, FSMState to,
				  FSMConditionFn condition, int priority); // adiciona uma aresta dirigida de um estado para outro no FSM, com uma condição e prioridade especificadas. A função cria uma nova aresta e a adiciona à lista de arestas do nó de origem.

FSMState fsm_update(FSM *fsm, const FSMContext *ctx); // avalia se as condições das arestas do estado atual são atendidas e, se sim, realiza a transição para o próximo estado. A função retorna o novo estado atual do inimigo.

const char *fsm_current_label(const FSM *fsm); // retorna o rótulo legível do estado atual do inimigo no FSM, permitindo que o programa exiba informações sobre o estado atual de forma compreensível para o jogador.

void fsm_destroy(FSM *fsm); // destroi o FSM, liberando a memória alocada para as arestas de cada nó e garantindo que não haja vazamentos de memória.

// .h é so declaraçãooooo
#endif
