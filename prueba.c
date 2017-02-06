#include <igraph.h>

int main()
{
	/* Declaracion de variables */
	igraph_t graph;
	igraph_vector_t edges;

	/* Inicializo el grafo en 0 */
	igraph_empty(&graph, 10, 0);

	igraph_vector_init(&edges, 2);

	

	igraph_add_edges(&graph, &edges, 

	printf("%d\n", graph.n);
	igraph_destroy(&graph);

	return 1;
}
