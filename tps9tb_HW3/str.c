#include "header.h"

// Works the same as a normal DFS but implements a stack where as each node is turned gray, it is added to a stack.  As the DFS turns them all black and has to find a 
// new node to start searching, it will pop all of the nodes in the stack and print them out (representing the strongly connected component).  After the strongly connected
// component is printed out, it prints a new line to seperate each strongly connected component
void STR_components(top_node *head, stack *top, int vertices) {
	int *counter = malloc(sizeof(int));
	
	top_node *curr = head;
	while (curr != NULL) {
		curr->color = 0; // the number 0 represents white, 1 is grey, and black is 2
		curr = curr->next;
	}
	curr = head;
	
	int *time = malloc(sizeof(int));
	*time = 0;
	*counter = 0;

	// go through each vertex in the graph if the vertex is not discovered yet
	curr = head;
	puts("Strongly Connected components:");
	while (curr != NULL) {
		if (curr->color == 0) { // if the vertex color is white
			top = NULL;
			*counter = 0;
			//printf("\nChecking %d", curr->val);
			STR_visit_components(head, curr, &time, &counter, &top);
		}
		
		// Checks to make sure the stack has nodes based on the counter, and will pop all nodes and print out the values of each node
		if (*counter != 0) { 
			top = pop(top);
			(*counter)--;
			while (*counter != 0){
				printf("->");
				top = pop(top);
				(*counter)--;
			}
			puts("\n");
		}
		curr=curr->next;
	}
	
	//printf("\n COUNTER = %d\n", *counter);
	
	free(time);
	free(counter);
}

// Works the same as the other two DFS visits but will push a node to the stack every time the function is called since 
// the node is part of a strongly connected component 
void STR_visit_components(top_node *head, top_node *curr, int **time, int **counter, stack **top) {
	// Pushes the node to the stack and adds to the strongly connected component
	*top = push(*top, curr->val);
	(**counter)++;
	
	top_node *v = head;
	int i = 0;
	**time = (**time)+1;
	curr->start = **time;
	curr->color = 1; // sets color to gray 
	if (curr->right != NULL) {
		node *temp = curr->right;
		while (temp != NULL) {
			v = head;
			//printf("head node is %d", v->val);
			//printf("\n temp node is [%d]", temp->val);
			while(v->val != temp->val) {
				v = v->next;
			}
			//printf("\n%d", v->val);
			if (v->color == 0) {
				STR_visit_components(head, v, time, counter, top);
			}
			temp = temp->right;
		}
	}
	curr->color = 2;
	**time = (**time)+1;
	curr->finish = **time;
}