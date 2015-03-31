#include "header.h"

// This function takes in the file pointer, head of the adjacency list and the head of the reversed adjacency list and will find 
void str_components(FILE *fp, top_node *head, top_node *reverse_list, int vertices) {
	int *L; // L is an array of each vertex in order of decreasing finish time
	L = DFS_components(fp, head, vertices);

	int count = 0;
	/*while (count != vertices) {
		printf("[%d]->", L[count]);
		count++;
	}
	printf("NULL\n");*/
	
	top_node *curr = head;
	top_node *new_list = NULL;
	
	// create a new adjacency list but in the order of decreasing finish times, so you can execute a DFS on the reverse list 
	// and find all stroongly connected components 
	for(count = 0; count < vertices; count++) {
		int temp = L[count]; //the index of the reversed linked list 
		top_node* prev;
		curr = reverse_list;
		while (curr->val != temp) {
			curr=curr->next;
		}
		
		// create a new node with the value and set the right pointer equal to the pointer of the reversed adjacency list (doesn't malloc new memory for the right nodes)
		top_node *n = create_top_node(curr->val);
		n->right = curr->right;
		
		// Find the end of the list to add the node to.  Will add to the beginning of the list if the list is empty for the new list 
		if (new_list == NULL) {
			new_list = n;
		}
		else {
			top_node *current = new_list;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = n;
		}
	}
	//puts("\nreverse graph DFS");
	DFS_components(fp, new_list, vertices); // will set start and finish times for all new nodes 
	
	stack *top = NULL;
	curr = new_list;
	STR_components(new_list, top, vertices); // will print out and find all strongly connected components in the list 
	
	// Delete all memory in new list and free the memory for array L 
	delete_list(new_list);
	free(L);
}

// Will take in the file pointer, head of an adjacency list and the number of vertices and produce start and finish times for each node and 
// at the end will add all nodes to an array of decreasing finish times and return the array.  Runs the exact same way as the DFS in dfs.c 
// but won't break if a cycle is found, it will still run through and store the list 
int *DFS_components(FILE *fp, top_node *head, int vertices) {
	int *L = malloc(sizeof(int) * vertices); // get memory for array
	int *counter = malloc(sizeof(int));
	
	top_node *curr = head;
	while (curr != NULL) {
		curr->color = 0; // the number 0 represents white, 1 is grey, and black is 2
		curr = curr->next;
	}
	curr = head;
	
	// Malloc memory for the time variable so it can be changed and passed to other functions 
	int *time = malloc(sizeof(int));
	*time = 0;
	*counter = vertices-1;

	// go through each vertex in the graph if the vertex is not discovered yet
	curr = head;
	while (curr != NULL) {
		if (curr->color == 0) { // if the vertex color is white
			//printf("\nChecking %d", curr->val);
			DFS_visit_components(head, curr, &time, &L, &counter);
		}
		curr=curr->next;
	}
	
	//print_dfs(head);
	//printf("\n COUNTER = %d\n", *counter);
	
	free(time);
	free(counter);
	return L;
}

// Works the same way as the DFS_visit function
void DFS_visit_components(top_node *head, top_node *curr, int **time, int **L, int **counter) {
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
				DFS_visit_components(head, v, time, L, counter);
			}
			temp = temp->right;
		}
	}
	curr->color = 2;
	**time = (**time)+1;
	curr->finish = **time;
	(*L)[**counter] = curr->val;
	(**counter)--;
}

// Pushes a new node to the stack or creates the stack if the pointer is null 
stack *push(stack *top, int data) {
	if (top == NULL) {
		stack *n = malloc(sizeof(stack));
		n->val = data;
		n->next = NULL;
		return n;
	}
	else {
		stack *temp = malloc(sizeof(stack));
		temp->next = top;
		temp->val = data;
		top = temp;
	}
}

// Pops the top node from the stack or returns an error if the stack is empty 
stack *pop(stack *top) {
	stack *top1 = top;
	
	if(top1 == NULL) {
		printf("Trying to push from an empty stack");
		return;
	}
	else {
		printf("[%d]",top1->val);
		top1 = top1->next;
	}
	free(top);
	top = top1;
	return top;
}