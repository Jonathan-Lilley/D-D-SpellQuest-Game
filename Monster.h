// Jonathan Lilley
// CSCI 1300-203
// ide: https://ide.c9.io/jonathanlilley/csci1300
// PROJECT 3: part 4: monster class
#ifndef MONSTER_H
#define MONSTER_H
#include <iostream>
#include <string>
using namespace std;

/**
 * Monster class
 * Used for random encounters (ALWAYS HOSTILE, NOT ALWAYS COMBATIVE)
 * private:
 * 
 * public:
 * 
 */
class Monster{
    private:
        string name;
        string location; // just for flavor text purposes
        int level; // for spell level purposes
        char speed; // fast f, medium m, slow s; for casting time purposes
        char distance; // far f, medium m, close c; for range purposes
    public:
        Monster(string n, string l, int lv, char s, char d) { name = n; location = l; 
        level = lv; speed = s; distance = d; }
        string getName() { return name; }
        string getLocation() { return location; }
        int getLevel() { return level; }
        char getSpeed() { return speed; }
        char getDistance() { return distance; }
};

#endif