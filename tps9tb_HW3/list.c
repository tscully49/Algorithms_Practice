#include "header.h"

// Creates an adjacency list based on the number of vertices and the data in the file, and sends a pointer to the list back to main
top_node *create_adjacency_list(FILE *fp, int vertices) {
	top_node *head = create_linked_list(vertices); // creates a linked list with all vertices in the graph 
	
	parser(fp, head, vertices);  // Will parse through the file and create the whole adjacency list 
	
	return head; // return the top of the adjacency list 
}

//Creates a linked list of all vertices in the graph from 1,2,3,...,n-1,n with n being the number of vertices
top_node *create_linked_list(int n) {
	top_node *head = NULL;
	int i;
	for (i=1; i < n+1; i++) {
		head = insert(head, i);
	}
	
	return head;
}

// Creates a new node of a vertex for the linked list and inserts it at the end of the list 
top_node *insert(top_node *head, int num) {
	top_node *n = create_top_node(num);
	if (head == NULL) {
		return n;
	}
	else {
		top_node *c = head;
		while (c->next != NULL) {
			c = c->next;
		}
		c->next = n;
		return head;
	}
}

// Mallocs memory for the new node, sets the value of the node, and returns the node
top_node *create_top_node(int num) {
	top_node *n = malloc(sizeof(top_node));
	if (n == NULL) {
		printf("Node not created successfully\n");
		exit(1);
	}
		n->val=num;
		n->start=0;
		n->finish=0;
		n->color=0;
		n->right = NULL;
		n->next = NULL;
	return n;
}

// Prints the adjacency list by going down the double linked list and going to the right representing the adjacent nodes if there are any 
void print_vertices(top_node* head) {
	top_node *p = head;
	node *pr = NULL;
	while (p != NULL) {
		printf("\n[%d] -> ", p->val);
		pr = p->right;
		if (pr == NULL) {
			printf("null");
		} else {
			while (pr != NULL) {
				printf("%d -> ", pr->val);
				pr = pr->right;
			}
			printf("null");
		}
		p=p->next;
	}
	printf("\n[NULL]\n");
}

// Creats a right node for the linked list representing an adjacent node to the top_node number
node *create_Adj_node(int num) {
	node *n = malloc(sizeof(node));
	n->val = num;
	n->right = NULL;
	return n;
}

// Will go through an adjaceny list and delete all node and right nodes in the list and free all memory associated with it
void delete_list(top_node *head) {
	top_node *curr = head;
	//Delete all nodes to the right of the current node including the current node, then move to the next row 
	while (curr != NULL) {
		if (curr->right != NULL) {
			node *temp = curr->right;
			while (temp != NULL) {
				free(temp);
				temp = temp->right;
			}
		}
		free(curr);
		curr = curr->next;
	}
	
}