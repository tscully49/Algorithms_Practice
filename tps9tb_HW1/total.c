#include "driver.h"

/*
	Total_numbers will check the file line by line and tokenize the line
	based on white space, tab, or new line.  It will then check that token
	to see if it is an integer or not.  If it is not an integer, it will not
	count the number.  If it is an integer, it will count the number towards the
	total amount of numbers in the file.  
*/
int total_numbers(FILE* fp) {
	int total = 0;
	int new_num;
	
	char line[MAX_LINE];
	char* temp;

	while (fgets(line, sizeof line, fp)) {
		temp = strtok(line, " \t\n");
		while (temp != NULL) {
			if(sscanf(temp, "%d",  &new_num) == 1) {
				total++;
			}
			else {
				printf("There was a variable THAT WAS NOT a digit\n\n");
			}
			temp = strtok(NULL, " \t\n"); 
		}
	}
	return total;
}