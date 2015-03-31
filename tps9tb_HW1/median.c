#include "driver.h"

/*
	The median function will take a file pointer AND the length of the file.
	It will then create an array of size "length" and fill the array with 
	numbers from the file.  Once that is full, it performs a merge sort on the
	array and then calculates the median position in the array based on the 
	size of the array.  Depending on if the array is even or odd in length, the
	function will calculate the median accordingly.  
*/
int median_number(FILE* fp, int length) {
	int current;
	int total_num = 0;
	int array[length];
	
	char line[MAX_LINE];
	char* temp;
	
	//list *head = create_node(current);
	//list *cp = head;

// Reads each line of the file and checks to make sure that each string in the file is an integer
// Doesn't use the number in calculation of the median if the value is not a number
	while (fgets(line, sizeof line, fp)) {
		temp = strtok(line, " \t\n");
		while (temp != NULL) {
			if(sscanf(temp, "%d",  &current) == 1) {
				array[total_num] = current;
				total_num++;
			}
			else {
				printf("There was a variable THAT WAS NOT a digit\n\n");
			}
			temp = strtok(NULL, " \t\n"); 
		}
	}
	
// Prints the final linked list so that you can see the final result 
	/*cp = head;
	while (cp->next != NULL) {
		printf("%d -> ", cp->val);
		cp = cp->next;
	}
	printf("%d -> ", cp->val);
	printf("NULL\n");*/
	
// Perform a merge sort in order to sort the linked list 
	//MergeSort(&head);
	
	/*int i;
	for(i = 0; i < length ; i++) {
		printf ("[%d]%d -> ", i, array[i]);
	}
	
	*/
	
// Merge sorts through the array and sorts it in ascending order 
	mergesort(array, 0, length-1);
	
	/*for(i = 0; i < length ; i++) {
		printf ("%d -> ", array[i]);
	}*/

// Figures out if the list has an even amount of numbers or odd, and then calculates the median value and outputs it to the screen
	if ((total_num % 2) == 0) {
		int median_front = (total_num/2);
		int median_back = ((total_num/2)+1);
		
		float number = (float)((array[median_front-1])+(array[median_back-1]))/2;
		printf("Median = %.2f\n", number);
	}
	else if ((total_num % 2) == 1){
		int median = (total_num-1)/2;
		int counter = 1;
		
		float number = (float)array[median-1];
		printf("Median = %.2f\n", number);
	}
}

/*list *create_node(int val)
{
	list *n = malloc(sizeof(list));
		n->val=val;
		n->next = NULL;
	return n;
}

void MergeSort(list **headref) {
	list *head;
	head = *headref;
	list *a;
	list *b;
	
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}
	
	FrontBackSplit(head, &a, &b);
	
	MergeSort(&a);
	MergeSort(&b);
	
	*headref = SortedMerge(a,b);
}

list *SortedMerge(list *a, list *b) {
	list *result = NULL;
	
	if (a == NULL) {
		return b;
	}
	else if (b == NULL) {
		return a;
	}
	
	if (a->val <= b->val) {
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else {
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	return result;
}

void FrontBackSplit(list *source, list **frontRef, list **backRef) {
	list *fast;
	list *slow;
	if (source == NULL || source->next == NULL) {
		*frontRef = source;
		*backRef = NULL;
	}
	else {
		slow = source;
		fast = source->next;
		
		while (fast != NULL) {
			fast = fast->next;
			if(fast != NULL) {
				slow = slow->next;
				fast = fast->next;
			}
		}
	
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}*/


/*
	The merge sort used was found online from pseudo code.  I did not invent the code 
*/
void merge(int arr[], int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	
	int L[n1], R[n2];
	
	for (i = 0; i < n1 ; i++) {
		L[i] = arr[l + i];
	}
	for (j = 0; j < n2; j++) {
		R[j] =  arr[m + 1 + j];
	}
	
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergesort(int arr[], int l, int r) {
	if (l < r) {
		int m = l+(r-l)/2;
		mergesort(arr, l, m);
		mergesort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}