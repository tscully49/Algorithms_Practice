#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER 100

typedef struct node{
	int val;
	int start;
	int finish;
	int color;
	struct node2 *right;
	struct node *next;
} top_node;

typedef struct node2{
	int val;
	struct node2 *right;
} node;

typedef struct STACK{
	int val;
	struct STACK *next;
} stack;

top_node *create_linked_list(int n);
top_node *insert(top_node *head, int num);
top_node *create_top_node(int num);
void print_vertices(top_node *head);
top_node *create_adjacency_list(FILE *fp, int vertices);
int parser(FILE *fp, top_node *head, int vertices);
node *create_Adj_node(int num);
void delete_list(top_node *head);
void DFS(FILE *fp, top_node *head, int vertices);
void DFS_visit(top_node *head, top_node *curr, int **time, int **top_sort, int **counter);
void print_dfs(top_node *head);
int *DFS_components(FILE *fp, top_node *head, int vertices);
void DFS_visit_components(top_node *head, top_node *curr, int **time, int **L, int **counter);
int reverse_parser(FILE *fp, top_node *head, int vertices);
top_node *create_reverse_list(FILE *fp, int vertices);
void str_components(FILE *fp, top_node *head, top_node *reverse_list, int vertices);
stack *push(stack *top, int data);
stack *pop(stack *top);
void STR_components(top_node *head, stack *top, int vertices);
void STR_visit_components(top_node *head, top_node *curr, int **time, int **counter, stack **top);