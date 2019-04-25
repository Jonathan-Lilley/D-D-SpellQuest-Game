// Jonathan Lilley
// CSCI 1300-203
// ide: https://ide.c9.io/jonathanlilley/csci1300
// PROJECT 3: part 2: spell list class
#ifndef SLIST_H
#define SLIST_H
#include <iostream>
#include <string>
#include <fstream>
#include "hash.h"
#define COLLISIONMAX 15 // maximum collisions expected
using namespace std;

/**
 * Spell list class: contains a list of spells in a hash table
 * Private variables:
 *      level[COLLISIONMAX] contains the level of each spell in a slot (with collisions)
 *      names includes all the names of the spells as a hash table;
 *          COLLISIONMAX deals with collisions
 * Public member functions:
 *      default and parameterized constructors
 *      setLv sets the level of a given spell -- not used?
 *      enter enters a spell into the list
 *      findHash looks up the hash of a spell
 *      lookup looks up the index in the hash table of the spell (used to account for collisions)
 *      getName gets the name of the name of a spell from... its name.
 *          getName is just used for testing things.
 */
class SList{
    private:
        int level[COLLISIONMAX];
        string names[MAX][COLLISIONMAX];
        const static int NUMSPELLS = 113;
        string nameslist[NUMSPELLS];
    public:
        SList();
        SList(string, int);
        void setLv(int);
        void enter(string);
        void addToList(string name, int index) { nameslist[index] = name; }
        int findHash(string name) { return hashFn(name); }
        int lookup(string);
        string getName(string name) { return names[findHash(name)][lookup(name)]; }
        void printList(int);
        int getNumSpells() { return NUMSPELLS; }
        string printListIndex(int i) { return nameslist[i]; }
};

/**
 * Default constructor; sets level to 0 at first available index in hash table position
 */
SList::SList(void){
    for(int i=0; i<COLLISIONMAX; i++){
        level[i] = 0;
    }
}

/**
 * Parameterized constructor
 * Finds the first empty slot in a hash and sets that slot to the spell name
 * Does the same for the level given
 */
SList::SList(string name, int lv){
    int i = 0;
    while(!names[hashFn(name)][i].empty() && i < COLLISIONMAX){
        i++;
    }
    names[hashFn(name)][i] = name;
    level[i] = lv;
}

/**
 * Sets level of spell -- fix this
 */
void SList::setLv(int lv){
    int j = 0;
    while(level[j] > 0){
        j++;
    }
    level[j] = lv;
}

/**
 * Enters a new spell into the first available slot in its corresponding hash
 */
void SList::enter(string name){
    int i = 0;
    while(!names[hashFn(name)][i].empty()){
        i++;
    }
    names[hashFn(name)][i] = name;
}

/**
 * Finds index of spell within hash of given spell
 */
int SList::lookup(string name){
    for(int i=0; i<COLLISIONMAX; i++){
        if(names[findHash(name)][i] == name){
            return i;
        }
    }
    return -1;
}

// Prints all spells up to input index in nameslist
void SList::printList(int index){
    for(int i=0; i<index; i++){
        cout << i+1 << ". " << nameslist[i] << endl;
    }
}

#endif