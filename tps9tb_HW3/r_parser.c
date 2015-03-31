#include "header.h"

// Creates a reversed adjacency list and returns a pointer to the list 
top_node *create_reverse_list(FILE *fp, int vertices) {
	top_node *head = create_linked_list(vertices); // creates a linked list with all vertices in the graph 
	
	reverse_parser(fp, head, vertices);  // Will parse through the file and create the whole adjacency list 
	
	return head; // return the top of the adj ist 
}

// Works the exact same as the first parser but reverse the order of the two numbers in each edge so that the adjacency list is reversed
int reverse_parser(FILE *fp, top_node *head, int vertices) {
	
	//int *tempPointer = NULL; // used for realloc to check it doesn't fail
	int counterNum = 0; // counter that counts the number of good inputs
	int i; 
	//int bufferCounterNum = 1; // number of times we have realloced
	//int bufferCounterChar = 1; // same as before 
	int valid = 0; // checks for good input (flag)
	int characterPos = 0; // keeps track of the position when reading character by character
	int firstPos = 0;
	char* currentInteger = malloc(sizeof(char) * BUFFER); // array used to convert to ints
	char* firstInteger = malloc(sizeof(char) * BUFFER); // 
	//char* tempCharacterPointer = NULL; //used if realloc fails 
	char charByChar;// holds the char as we parse through file char by char 
	
	int temp1 = 0;
	int temp2 = 0; // (3,1) -> (temp1,temp2) the format of how temp1 and temp2 are stored 
	int count = 0; // counter used to find the correct spot on the adjacency list to add the node
	top_node *current = NULL;
	node *find_end = NULL;
	int flag = 0; // a flag when adding a number to the adjacency list, will turn to 0 if the number already exists
	
	do {
		charByChar = fgetc(fp);
		if (charByChar == ' ' || charByChar == '\t' || charByChar == '\n') {
			currentInteger[characterPos] = '\0';
			characterPos = 0;
			/*if (counterNum >= (BUFFER * bufferCounterNum)) {
				bufferCounterNum++;
				tempPointer = realloc((\\\\*numberSequence), (bufferCounterNum * BUFFER) * sizeof(int));
				if (temporaryPointer != NULL) {
					(\\\\*numberSequence) = tempPointer;
				} else {
					free((\\\\*numberSequence));
					printf("Out of memory error\n");
					exit(0);
				}
			}*/
			
			
			valid = 1;
			firstPos = 0;
			temp1 = 0;
			temp2 = 0;
			
			for (i=0; i < strlen(currentInteger); i++) {
				if (i == 0 && currentInteger[i] != '(') {
					valid = 0;
					break;
				}
				if (i != 0 && !isdigit(currentInteger[i]) && currentInteger[i] != ',' && currentInteger[i] != ')') {
					valid = 0;
					break;
				} else {
					if (isdigit(currentInteger[i])){
						firstInteger[firstPos] = currentInteger[i];
						firstPos++;
					}
				}
				if (currentInteger[i] == ',') {
					firstInteger[firstPos] = '\0';
					//printf("TEMP 1 CHARACTER STRING IS %s\n", firstInteger);
					temp2 = (int)strtol(firstInteger, NULL, 10);
					//printf("TEMP 1 INTEGER IS %d\n", temp1);
					if (temp2 < 1 || temp2 > vertices) {
						valid = 0;
						break;
					}
					firstPos = 0;
					i++;
					while (currentInteger[i] != '\0') {
						if (i != 0 && !isdigit(currentInteger[i]) && currentInteger[i] != ')') {
							valid = 0;
							break;
						} else {
							if (isdigit(currentInteger[i])) {
								firstInteger[firstPos] = currentInteger[i];
								firstPos++;
							}
						}
						if (currentInteger[i] == ')') {
							firstInteger[firstPos] = '\0';
							//printf("TEMP 2 CHARACTER STRING IS %s\n", firstInteger);
							temp1 = (int)strtol(firstInteger, NULL, 10);
							//printf("TEMP 2 INTEGER IS %d\n", temp2);
							if (temp1 < 1 || temp1 > vertices) {
								valid = 0;
								break;
							}
							break;
						}
						i++;
					}
					break;
				}
			}
			
			if (strlen(currentInteger) < 1) {
				valid = 0;
			}
			
			if (valid) { // after a valid edge is found, add the edge to the correct adjacency list location
				//(\\\\*numberSequence)[counterNum] = (int) strtol(currentInteger, NULL, 10);
				/////////////////printf("temp1 = %d   temp2 = %d\n", temp1, temp2);
				counterNum++;
				flag = 1;
				
				current = head; // create pointer to add node
				count = 1;
				while (count != temp1) {
					current = current->next;
					count++;
				}
				// Then find the end of the right list on that node with a new pointer
				if (current->right == NULL) {
					current->right = create_Adj_node(temp2);
				} else {
					find_end = current->right;
					if (find_end->val == temp2) {
						flag = 0;
					}
					while (find_end->right != NULL) {
						find_end = find_end->right;
						if (find_end->val == temp2) {
							flag = 0;
						}
					}
					if (flag) {
						find_end->right = create_Adj_node(temp2);
					}
				}
			}
		} else {
			/*if(characterPos >= (BUFFER * bufferCounterChar)) {
				bufferCounterChar++;
				tempCharacterPointer = realloc(currentInteger, (bufferCounterChar * BUFFER) * sizeof(char));
				if (tempCharacterPointer != NULL) {
					currentInteger = tempCharacterPointer;
				} else {
					free(currentInteger);
					printf("Out of memory error\n");
					exit(0);
				}
			}*/
			
			currentInteger[characterPos] = charByChar;
			characterPos++;
		}
	} while(charByChar != EOF);
	
	free(currentInteger);
	free(firstInteger);
	//fclose(fp);
	
	if(counterNum == 0) {
		printf("Size of input is 0\n");
		exit(0);
	}
	
	//printf("The number of edges in the graph is %d\n", counterNum);
	
	return counterNum;
}