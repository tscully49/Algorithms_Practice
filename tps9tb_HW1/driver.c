/*
 * Thomas Scully
 * 1/26/15
 * CS 3050
 * Homework 1
*/

#include "driver.h"

/*
	Main will open the file from the command line and check that the correct 
	number of command line arguments are used.  It will then check to see which 
	variable is defined after being compiled.  If MAXIMUM is defined, it will count 
	the amount of numbers in the file and find the maximum through a function. 
	If MEDIAN is defined, it will count the amount of numbers and call a function 
	to find the median 
*/
int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <numbered file> \n", argv[0]);
		return 0-1;
	}
	
	FILE* fp = fopen(argv[1], "r");
	
	if (fp == NULL) {
		printf("Unable to open .txt file\n");
		return 0-1;
	}
	
	#ifdef MAXIMUM
	printf("There are %d numbers in this file\n", total_numbers(fp));
	rewind(fp);
	printf("The maximum number in the list is %d\n", max_number(fp));
	fclose(fp);
	#endif
	
	#ifdef MEDIAN
	int number = total_numbers(fp);
	printf("There are %d numbers in this file\n", number);
	rewind(fp);
	median_number(fp, number);
	fclose(fp);
	#endif

	return 0;
}