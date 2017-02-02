#include <igraph.h>

int main()
{
	/* Declaracion de variables */
	igraph_t graph;
	igraph_vector_t edges;
	igraph_real_t avg_path;

	/* Inicializo el grafo en 0 */
	igraph_empty(&graph, 0, 0);

	/* Agrego 2 nodos al grafo */
	igraph_add_vertices(&graph, 2, 0);

	/* Agrego un enlace entre 0 y 1 */
	igraph_vector_init(&edges, 2);
	VECTOR(edges)[0] = 0;
	VECTOR(edges)[1] = 1;

	igraph_add_edges(&graph, &edges, 0);	

	/* Calcula el average path length de la lattice */
	igraph_average_path_length(&graph, &avg_path, IGRAPH_UNDIRECTED, 1);
	printf("Average path length (lattice): %f\n", (double)avg_path);

	igraph_destroy(&graph);
	igraph_vector_destroy(&edges);	

	return 1;
}
