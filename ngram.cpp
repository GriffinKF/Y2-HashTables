#include "HashTable.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cstdio>

using namespace std;

typedef HashTable<string, int> HTSI;
typedef HashNode<string, int> HNSI;

int main(int argc, char* argv[]){
	
	HTSI nTable;

	ifstream file;
	string s = "";
	int numchars = 0;
	char letter;
	stringstream stream;
	int slength;
	int numberOfGrams = 0;
	string line;
 

	if (argc != 4){
		cerr << argv[0] << " requires three arguments" << endl;
		return 1;
    }

	file.open(argv[1]);
    if (!file) {
        cerr << "Could not read file" << endl; 
        return 1; 
    }


    stream << argv[2];
    stream >> numchars;

    while(file.get(letter)) {
        if(letter == '\n'){
        	continue;
        }
        s += letter;
        slength = s.length();
        if (slength == numchars){
            //cout << s << endl;
            numberOfGrams = numberOfGrams + 1;
            nTable.ngramInsert(s);
            s = s.substr(1);
        }
    }

    file.close();

    nTable.ngramDisplay(numberOfGrams, atoi(argv[3]));

    return 0;
}