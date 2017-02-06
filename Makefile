all:
	gcc prueba2.c -I /usr/local/include/igraph -L /usr/local/lib -ligraph -o prueba2.e
	gcc prueba.c -I /usr/local/include/igraph -L /usr/local/lib -ligraph -o prueba.e

clean:
	rm -rfv prueba.e prueba2.e medus_model.e
