#include "header.h"

int main(int argc, char** argv) {
	
	if(argc != 2){
		printf("usage: <maximum> <inputfilename>\n");
		exit(0);
	}
	
	FILE *fp = fopen(argv[1], "r");
	
	if(fp == NULL){
		printf("File error.\n");
		return(0);	
	}
	
	int vertices;
	fscanf(fp, "%d", &vertices); // reads the number of vertices in graph from file 
	if (vertices <= 0) { // if it is empty, end program 
		return 0;
	}

	// Prints out the adjacency list and a topological sort if there are no cycles, otherwise posts an error 
	#ifdef DDAG
	top_node *a_list = create_adjacency_list(fp, vertices);
	print_vertices(a_list);
	puts(" ");
	DFS(fp, a_list, vertices);
	delete_list(a_list);
	#endif
	
	// prints out a topological sort if there are no cycles 
	#ifdef DAG
	top_node *a_list = create_adjacency_list(fp, vertices);
	DFS(fp, a_list, vertices);
	delete_list(a_list);
	#endif
	
	// prints out the adjacency list and the reverse list as well as all strongly connected components 
	#ifdef DCOMPONENTS
	top_node *a_list = create_adjacency_list(fp, vertices);
	rewind(fp);
	printf("\nThe first Adjacency list:");
	print_vertices(a_list);
	top_node *reverse_list = create_reverse_list(fp, vertices);
	printf("\nThe reversed graph Adjacency list:");
	print_vertices(reverse_list);
	puts(" ");
	str_components(fp, a_list, reverse_list, vertices);
	delete_list(reverse_list);
	delete_list(a_list);
	#endif
	
	// prints out all strongly connected components 
	#ifdef COMPONENTS
	top_node *a_list = create_adjacency_list(fp, vertices);
	rewind(fp);
	top_node *reverse_list = create_reverse_list(fp, vertices);
	str_components(fp, a_list, reverse_list, vertices);
	delete_list(reverse_list);
	delete_list(a_list);
	#endif
	
	printf("\n");
	fclose(fp);
}