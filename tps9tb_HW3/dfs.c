#include "header.h"

// Runs a depth first search on the adjacency list passed through.  Will check to make sure that there are no cycles in the directed graph, and if there are, the 
// program will be terminated and no topological sort will be printed out.  If no cycles are found, the function will end by printing out a topological sort 
// of the graph.  When representing colors of the node, I used integers with the name "color" with the number 0 representing white, 1 representing gray, and 
// 2 representing black while executing the DFS.  After a node is turned black, it is added to the top_sort array and the whole array is printed out after the DFS has hit
// all nodes in the directed graph.  "top_sort" is represented as the topological sort of the graph
void DFS(FILE *fp, top_node *head, int vertices) {
	int *top_sort = malloc(sizeof(int) * vertices); // get memory for array and for the counter variable 
	int *counter = malloc(sizeof(int));
	
	top_node *curr = head;
	while (curr != NULL) {
		curr->color = 0; // the number 0 represents white, 1 is grey, and black is 2
		curr = curr->next;
	}

	int *time = malloc(sizeof(int)); // store memory for the variable so it can be changed and passed to other functions 
	*time = 0;
	*counter = vertices-1;

	// go through each vertex in the graph if the vertex is not discovered yet
	curr = head;
	while (curr != NULL) { // go through the whole adjacency list from top to bottom 
		if (curr->color == 0) { // if the vertex color is white, visit it and check its children
			DFS_visit(head, curr, &time, &top_sort, &counter);
		}
		if (curr->color == 1) { // if the next node is gray then there is a cycle and the program should display a message and then terminate
			printf("The graph has a cycle!!!");
			exit(1);
		}
		curr=curr->next;
	}
	puts(" ");
	
	// Prints out the topological sort of the directed graph in the event that there is no cycle present after completing the DFS
	int temp;
	*counter = 0;
	puts("Topological Sort: ");
	while (*counter != vertices) {
		printf("[%d]->", top_sort[*counter]);
		(*counter)++;
	}
	printf("NULL");
	// Frees all memory used in this function that aren't used in main or passed back 
	free(time);
	free(counter);
	free(top_sort);
}

// This function visits a white node, turns it gray and then checks to see if it has any children that havent been discovered yet.  If so, it will recursively visit all children until 
// there are none left, in which case it will turn that node black and start going back up, checking each node for more children to head down and discover.  If a gray node is found then 
// there is a cycle and the program will terminate and display an error message since no topological sort can be completed 
void DFS_visit(top_node *head, top_node *curr, int **time, int **top_sort, int **counter) {
	top_node *v = head;
	int i = 0;
	**time = (**time)+1;
	curr->start = **time; 
	curr->color = 1; // sets color to gray 
	if (curr->right != NULL) {
		node *temp = curr->right;
		while (temp != NULL) {
			v = head;
			// Find the corresponding node in the double list based on the value of the adjacent node 
			for (i = 0; i < (temp->val)-1 ; i++) {
				v = v->next;
			}
			if (v->color == 0) { // checks to see if the node visited is white (undiscovered)
				DFS_visit(head, v, time, top_sort, counter);
			}
			if (v->color == 1) { // checks to see if the node visited is gray (discovered but not closed)
				printf("The graph has a cycle!!!\n");
				exit(1);
			}
			temp = temp->right;
		}
	}
	curr->color = 2; // turns a node black and increments time and decrements counter
	**time = (**time)+1;
	curr->finish = **time;
	(*top_sort)[**counter] = curr->val;
	(**counter)--;
}

// This function prints off every node as well as the start and finish times associated with the node after the DFS completes execution, which gives you 
// a representation of what the DFS graph would look like if it were a graph.  Was more so used for checking that my code was running correctly, and isn't 
// used in the final implementation of my code
void print_dfs(top_node *head) {
	top_node *p = head;
	while (p != NULL) {
		printf("[%d] start = %d ||| finish = %d\n", p->val, p->start, p->finish);
		p=p->next;
	}
	puts(" ");
}