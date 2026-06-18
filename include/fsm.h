//o comportamento propriamente dito usando o FSM
//o comportamento propriamente dito usando o FSM
#ifndef FSM_H
#define FSM_H
#define MAXNODES 3//definição dos nós para usar o gráfo direcionado, a partir da matriz de adjacência

typedef struct {
		int vertice_number;
		int matriz[MAXNODES][MAXNODES];
}adjacency_matrix;

void initialize_graph(adjacency_matrix *graph, int number_vertice){
    graph->vertice_number = number_vertice;

    for (int i = 0; i < number_vertice; i++){
        for (int j = 0; j < number_vertice; j++){
            graph->matriz[i][j] = 0;
        }
    }
}

#endif            
