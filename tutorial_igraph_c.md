# Tutorial Igraph en C

Tutorial para utilizar la librería igraph para C. La idea es optimizar 
los programas de los modelos basados en agentes, en cuya dinámica aparezcan rewirings u otros tipos de cambios en la topología de la red, junto con la dinámica propia del modelo.

## Detalles de igraph

Igraph tiene varias declaraciones para crear tipo de datos propios, no solo grafos sino también vectores, números reales y enteros.
Muchas de las funciones reciben como argumento la dirección de memoria del grafo creado. Es importante liberar los espacios de memoria reservados, con una función especial de igraph.

#### Programas de ejemplo

**Creación de un grafo vacío de 10 nodos:**
```C
#include <igraph.h>

int main()
{
	igraph_t graph;

	/* Empty graph with 10 vertices and undirected */
	igraph_empty(&graph, 10, 0);

	igraph.destroy(&graph);
	
	return 1;
}
```

**Creación de vectores:**
```C
igraph_vector_t vector;

/* Vector de 10 componentes, lo inicializa a 0 */
igraph_vector_init(&vector, 10);

/* Dimension del vector */
igraph_vector_size(&vector);

/* Asignacion de valores */
VECTOR(vector)[0] = 10;
```

**Creación de nodos y enlaces:**
```C
igraph_t graph;

igraph_vector_t edges;

igraph_empty(&graph, 0, 0);

/* Agrego 10 nodos */
igraph_add_vertices(&graph, 10, 0);

/* Agrego un enlace entre 0 y 1 */

igraph_vector_init(&edges, 2);

VECTOR(edges)[0] = 0;
VECTOR(edges)[1] = 1;

igraph_add_edges(&graph, &edges, 0);
```

**Vecinos de un nodo:**
igraph_vector_t neighbors;

/* Guarda en neighbors los vecinos del vertice 0 */
igraph_neighbors(&graph, &neighbors, 0, IGRAPH_ALL);


