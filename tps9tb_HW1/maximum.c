#include "driver.h"

/* 
	Max number will read each line of the file and tokenize it based on 
	white space, tabs, and new lines.  Then it checks to make sure that
	the string is an integer.  If it is an integer, then it checks that 
	number against the current maximum to see if it is in fact the biggest
	number.  At the end, it returns the biggest number found in the list
*/
int max_number(FILE* fp) {
	int max_num;
	int new_num;
	
	char line[MAX_LINE];
	char* temp;
	
	//Checks to make sure every value analysed is an integer.  If not an integer, it will be skipped
	while (fgets(line, sizeof line, fp)) { // read a line from the file
		temp = strtok(line, " \t\n"); // tokenizes the line 
		while (temp != NULL) {
			if(sscanf(temp, "%d",  &new_num) == 1) { // check to see if temp is a digit
				if(new_num > max_num) {
					max_num = new_num; 
				}
			}
			else {
				printf("There was a variable THAT WAS NOT a digit\n\n");
			}
			temp = strtok(NULL, " \t\n"); 
		}
	}
	
	return max_num;
}
