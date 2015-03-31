#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
//#include <string>

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <numbered file> " << std::endl;
	}
	
	ifstream input_file(argv[1]);
	if (!input_file.is_open()) {
		cout << "Unable to open .txt file" << endl;
		return 0-1;
	}
	
	string line;
	
	while(getline(input_file, line)) {
		
	}
	
	return 0;
}