#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]) {
    ifstream file;
    string s = "";
    int numchars = 0;
    char letter;
    stringstream stream;

    if (argc != 3){
        cerr << argv[0] << " requires two arguments" << endl;
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
        if (s.length() == numchars){
            cout << s << endl;
            s = s.substr(1);
        }
    }

    file.close();

    return 0;
}
