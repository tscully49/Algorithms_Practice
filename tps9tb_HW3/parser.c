#include "header.h"

int parser(FILE *fp, top_node *head, int vertices) {
	
	int counterNum = 0; // counter that counts the number of good inputs
	int i; 
	int valid = 0; // checks for good input (flag)
	int characterPos = 0; // keeps track of the position when reading character by character
	int firstPos = 0;
	char* currentInteger = malloc(sizeof(char) * BUFFER); // array used to convert to ints
	char* firstInteger = malloc(sizeof(char) * BUFFER); // 
	char charByChar;// holds the char as we parse through file char by char 
	
	int temp1 = 0;
	int temp2 = 0; // (3,1) -> (temp1,temp2) the format of how temp1 and temp2 are stored 
	int count = 0; // counter used to find the correct spot on the adjacency list to add the node
	top_node *current = NULL;
	node *find_end = NULL;
	int flag = 0; // a flag when adding a number to the adjacency list, will turn to 0 if the number already exists
	
	do {
		charByChar = fgetc(fp);
		if (charByChar == ' ' || charByChar == '\t' || charByChar == '\n') { // checks for a space, tab, or new line in order to start checking to see if the input is valid 
			currentInteger[characterPos] = '\0';
			characterPos = 0;
			
			valid = 1;
			firstPos = 0;
			temp1 = 0;
			temp2 = 0;
			
			// Parses through the the sub string of the input to see if it is a valid input.  It will check to make sure the input starts with a ( and then contains a number followed by
			// a , and a second number, ending with a ).  If the parser finds that any of these conditions are not true, it sets the valid flag equal to 0 and the substring is not added 
			// to the adjacency list.  If the substring is valid, it will add the second number to the adjacency list at the vertex which is equal to the first number.  
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
					temp1 = (int)strtol(firstInteger, NULL, 10);
					//printf("TEMP 1 INTEGER IS %d\n", temp1);
					if (temp1 < 1 || temp1 > vertices) {
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
							temp2 = (int)strtol(firstInteger, NULL, 10);
							//printf("TEMP 2 INTEGER IS %d\n", temp2);
							if (temp2 < 1 || temp2 > vertices) {
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
			
			// checks to make sure the substring isn't empty
			if (strlen(currentInteger) < 1) {
				valid = 0;
			}
			
			if (valid) { // after a valid edge is found, add the edge to the correct adjacency list location
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
		} else { // if the value isn't a tab, space, or new line keep parsing through the input 
			currentInteger[characterPos] = charByChar;
			characterPos++;
		}
	} while(charByChar != EOF);
	
	// Free all memory
	free(currentInteger);
	free(firstInteger);
	
	// if there are no valid inputs in the file 
	if(counterNum == 0) {
		printf("Size of input is 0\n");
		exit(0);
	}
	
	return counterNum;
}