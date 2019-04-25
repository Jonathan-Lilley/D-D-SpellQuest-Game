// Jonathan Lilley
// CSCI 1300-203
// ide: https://ide.c9.io/jonathanlilley/csci1300
// PROJECT 3: part 0: hash function
#include <iostream>
#define MAX 1000 // size of hash table
using namespace std;

// Hash function -- returns index based on string; designed for minimal collisions
int hashFn(string key){
    int index = 1409;
    for(int i=0; i<key.length(); i++){
        index = index*1033 + key[i]*1483 + key[i]/31;
    }
    index = index & MAX-1;
    if(index < 0){
        return -index;
    }
    return index;
}