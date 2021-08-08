#ifndef MY_HASH_NODE
#define MY_HASH_NODE

using namespace std;

template <class KeyType, class ValueType>
class HashNode {
  KeyType key;     // The hash node's key
  ValueType value; // The key's associated data4
  int hasBeenDeleted;
  int empty;

  /* extend if necessary */

public:

  HashNode();  // constructor

  KeyType getKey() { return key; }
  ValueType getValue() { return value; }
  int getDeleted() { return hasBeenDeleted; }
  int getEmpty() { return empty; }
  void assign(KeyType key, ValueType value);
  void ngramAssign(KeyType key);
  void ngramValuePlus1();
  void deleteKey();
  void deleteValue();
  void setDeleted1();
  void setEmpty(int ONEorZERO);
  // extend if necessary
};

/* 
   Implement the constructor, the assign method 
   and any methods that you may additionally need for the HashTable to work.
*/
template <class KeyType, class ValueType>
HashNode<KeyType, ValueType>::HashNode(){
  this->key = '0';
  this->value = '0';
  this->hasBeenDeleted = 0;
  this->empty = 1;
}

template <class KeyType, class ValueType>
void HashNode<KeyType, ValueType>::assign(KeyType key, ValueType value){
  this->key = key;
  this->value = value;
  this->empty = 0;
}

template <class KeyType, class ValueType>
void HashNode<KeyType, ValueType>::ngramAssign(KeyType key){
  this->key = key;
  this->value = 1;
  this->empty = 0;
}

template <class KeyType, class ValueType>
void HashNode<KeyType, ValueType>::ngramValuePlus1(){
  this->value = value + 1;
  this->empty = 0;
}

template <class KeyType, class ValueType>
void HashNode<KeyType, ValueType>::deleteKey(){
  this->key = '0';
}

template <class KeyType, class ValueType>
void HashNode<KeyType, ValueType>::deleteValue(){
  this->value = '0';
}

template <class KeyType, class ValueType>
void HashNode<KeyType, ValueType>::setDeleted1(){
  this->hasBeenDeleted = 1;
}

template <class KeyType, class ValueType>
void HashNode<KeyType, ValueType>::setEmpty(int ONEorZERO){
  this->empty = ONEorZERO;
}

#endif