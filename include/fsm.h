//o comportamento propriamente dito usando o FSM
#ifndef FSM_H
#define FSM_H
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int destination;
	struct node * next;
}node;

typedef struct adjacency_list{
	node * head;
}adjacency_list;

typedef struct graph{
	int number_vertice;
	adjacency_list * vector_adjacency_list;
}graph;

node * creating_node(int destination){
    node * new_node = (node*)malloc(sizeof(node));
    new_node->destination = destination;
    new_node->next = NULL;
	
	return new_node;
}

graph * creating_graph(int number_vertice){
	graph * new_graph = (graph *)malloc(sizeof(graph));
	new_graph->number_vertice = number_vertice;

	new_graph->vector_adjacency_list = (adjacency_list *)malloc(number_vertice * sizeof(adjacency_list));

	for(int i = 0; i < number_vertice; i++){
		new_graph->vector_adjacency_list[i].head = NULL;
	}

	return new_graph;
}

//dale
#endif            
