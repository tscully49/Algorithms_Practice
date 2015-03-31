#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 250

/*
	The header file for the program.  Contains all function prototypes, data 
	structures, and libraries used for the assignment.  
*/
typedef struct node{
	int val;
	struct node *next;
} list;

int max_number(FILE* fp);
int median_number(FILE* fp, int length);
list *create_node(int val);
int total_numbers(FILE* fp);
void MergeSort(list **headref);
list *SortedMerge(list *a, list *b);
void FrontBackSplit(list *source, list **frontRef, list ** backRef);
void merge(int arr[], int l, int m, int r);
void mergesort(int arr[], int l, int r);