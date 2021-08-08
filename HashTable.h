#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "HashNode.h"
#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>
#include <sstream>
#include <cstdio>

using namespace std;

enum HashTableError { OUT_OF_MEMORY, KEY_NOT_FOUND, DUPLICATE_KEY }; // extend if necessary

template <class KeyType, class ValueType>
class HashTable {typedef HashNode<string, int> compare1;
  typedef vector <HashNode<KeyType,ValueType> > Table;
  Table *table; // size of table (# of buckets) is stored in the Table data structure
  int num;   // number of entries stored in the HashTable;

public:
  HashTable();        // constructor, initializes table of size 11;
  HashTable(int);  // constructor, requires size of table as arg
  ~HashTable();       // deconstructor

  int size();      // returns size of the hash table (number of buckets)
  string toString(KeyType);
  int hash_function(KeyType);  // the table's hash function
  int doubleHash_function(KeyType); // the tables second hash funtion.
  ValueType getValue(KeyType);    // find and return data associated with key
  KeyType getKey(KeyType);
  void bubbleSort(Table, int, int);

  void insert(KeyType,ValueType); // insert data associated with key into table
  void ngramInsert(KeyType);
  void ngramDisplay(int, int);
  void erase(KeyType);            // remove key and associated data from table

  void rehash(int); // sets a new size for the hash table, rehashes the hash table 
  // extend if necessary
};

template <class KeyType, class ValueType>
int HashTable<KeyType,ValueType>::size() {
  return table->size();
}

/* Implement the 
- Constructors, Destructor
- hash_function, insert, getValue methods
- erase, and rehash methods 
*/

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable(){
  table = new Table();
  table->resize(11);
  num = 0;
}

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable(int tableSize){
  table = new Table();
  table->resize(tableSize);
  num = 0;
}

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::~HashTable(){
  table->clear();
}

template <class KeyType, class ValueType>
string HashTable<KeyType, ValueType>::toString(KeyType inKey){
  string newString;
  ostringstream converter;
  converter << inKey;
  newString = converter.str();
  return newString;
}

template <class KeyType, class ValueType>
int HashTable<KeyType, ValueType>::hash_function(KeyType hashString){
  int index = 0;
  if(typeid(hashString) == typeid(int)) {
    index = stoi(toString(hashString));
    index = index*31;
    return (index % size());
  } else {
    int x = 0;
    string keyString = toString(hashString);
    for(string::iterator it = keyString.begin(); it != keyString.end(); ++it) {
      index = index + (int(*it)*(31^x));
      x++;
    }
    return (index % size());
  }
}

template <class KeyType, class ValueType>
int HashTable<KeyType, ValueType>::doubleHash_function(KeyType hashString){
  int index = 0;
  if(typeid(hashString) == typeid(int)) {
    index = stoi(toString(hashString));
    index = index*31;
    return (1+(index % (size()-1)));
  } else {
    int x = 0;
    string keyString = toString(hashString);
    for(string::iterator it = keyString.begin(); it != keyString.end(); ++it) {
      index = index + (int(*it)*(31^x));
      x++;
    }
    return (1+(index % (size()-1)));
  }
}


template <class KeyType, class ValueType>
ValueType HashTable<KeyType, ValueType>::getValue(KeyType hashString){
  int index = hash_function(hashString);
  int offset = doubleHash_function(hashString);
  int found = 0;
  while (found == 0) {
    if (table->at(index).getKey() == hashString) {
      found = 1;
    } else {
      index = ((index + offset) % size());
    }
  }
  return table->at(index).getValue();
}

template <class KeyType, class ValueType>
KeyType HashTable<KeyType, ValueType>::getKey(KeyType hashString){
 int index = hash_function(hashString);
 return table->at(index).getKey();
}


template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::bubbleSort(Table a, int numberOfGrams, int topX){
	int aSize = a.size();
	int swapp = 1;
	while(swapp == 1){
		swapp = 0;
		for (int i = 0; i < aSize-1; i++) {
			if (a[i].getValue() < a[i+1].getValue()){				
				KeyType key1 = a[i].getKey();
				KeyType key2 = a[i+1].getKey();
				ValueType value1 = a[i].getValue();
				ValueType value2 = a[i+1].getValue();

				a[i].assign(key2, value2);
				a[i+1].assign(key1, value1);
				swapp = 1;
			}
		}

	}

	int timesCouted = 0;
	float numOfGrams = (float)numberOfGrams;
	for(int i = 0; i < aSize; i++) {
		string compareKey = a[i].getKey();
		if(compareKey == "0") {
			continue;
		} else {
			ValueType freq = a[i].getValue();
			float frequency = (float)freq;
			float percentage = (frequency/numOfGrams)*100; 
			if (timesCouted < topX) {
				printf("%.2f", percentage);
				cout << ":" << a[i].getKey() << endl;
				timesCouted = timesCouted + 1;
			}
						
		}
	}
}


template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::ngramDisplay(int numberOfGrams, int topX){
  bubbleSort(*table, numberOfGrams, topX);
}


template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::insert(KeyType hashString, ValueType insertValue){
  float totalSize = (float)size();
  float numFilled = (float)num;
  if ((numFilled)/(totalSize) > 0.5) {
    rehash(2*size());
  }
  int index = hash_function(hashString);
  int offset = doubleHash_function(hashString);
  int inserted = 0;
  while(inserted == 0) {
    if (table->at(index).getEmpty() == 1) {
      table->at(index).assign(hashString, insertValue);
      num = num + 1;
      inserted = 1;
    } else if(table->at(index).getEmpty() == 0) {
      if (table->at(index).getKey() == hashString) {
        inserted = 1;
      } else {
        index = ((index + offset) % size());
      } 
    }
  }
}

template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::ngramInsert(KeyType hashString){
  float totalSize = (float)size();
  float numFilled = (float)num;
  if ((numFilled)/(totalSize) > 0.5) {
    rehash(2*size());
  }
  int index = hash_function(hashString);
  int offset = doubleHash_function(hashString);
  int inserted = 0;
  while(inserted == 0) {
    if (table->at(index).getEmpty() == 1) {
      table->at(index).ngramAssign(hashString);
      num = num + 1;
      inserted = 1;
    } else if(table->at(index).getEmpty() == 0) {
      if (table->at(index).getKey() == hashString) {
        table->at(index).ngramValuePlus1();
        inserted = 1;
      } else {
        index = ((index + offset) % size());
      } 
    }
  }
}

template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::erase(KeyType hashString){
  int index = hash_function(hashString);
  int offset = doubleHash_function(hashString);
  while (table->at(index).getKey() != hashString) {
    index = ((index + offset) % size());
  }

  table->at(index).deleteKey();
  table->at(index).deleteValue();
  table->at(index).setEmpty(1);
  num = num - 1;
  table->at(index).setDeleted1();
  float totalSize = (float)size();
  float numFilled = (float)num;
  if ((numFilled)/(totalSize) > 0.5) {
    rehash(2*size());
  }
}

template <class KeyType, class ValueType>
void HashTable<KeyType,ValueType>::rehash(int rehashSize) {
  KeyType tempKey;
  ValueType tempValue;
  Table *rhTable;
  rhTable = new Table(rehashSize);
  Table *tempTable;
  tempTable = new Table(table->size());
  *tempTable = *table;
  *table = *rhTable;
  int tempTableSize = tempTable->size();

  for(int i = 0; i < tempTableSize; i++) {
    if(tempTable->at(i).getEmpty() == 0) {
      tempKey = tempTable->at(i).getKey();
      tempValue = tempTable->at(i).getValue();
      insert(tempKey, tempValue);
    }
  }
}


#endif