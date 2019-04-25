// Jonathan Lilley
// CSCI 1300-203
// ide: https://ide.c9.io/jonathanlilley/csci1300
// PROJECT 3: part 1: spell class
#ifndef SPELL_H
#define SPELL_H
#include <iostream>
#include <string>
using namespace std;


/**
 * Spell class: an individual spell, includes all its attributes
 * Private variabls (attributes):
 *      name
 *      level
 *      school (what type of spell, e.g. summoning something, creating defenses, etc)
 *      casting time (how long it takes to cast)
 *      range (how far it can be cast)
 *      components (what is needed, i.e. verbal elements, movements, physical components)
 *      duration (how long it lasts)
 *      description (full description of what it does)
 * Public member functions:
 *      Default constructor: sets everythign to empty string and level to -1
 *      Parameterized constructor: Sets everything to input
 *      getLevel returns level
 *      getSchool returns the school
 *      getCast returns casting time
 *      getRange returns range
 *      getDur returns duration
 *      getDesc returns description
 *      setName sets the name
 *      setLevel sets the level
 *      setSchool sets the school
 *      setCast sets the casting time
 *      setRange sets the range
 *      setComps sets the components
 *      setDur sets the duration
 *      setDesc adds to the description
 */
class Spell{
    private:
        string name;
        int level;
        string school;
        string casting_time;
        string range;
        string components;
        string duration;
        string description;
    public:
        Spell() { name = ""; level = -1; school = ""; casting_time = "";
        range = ""; components = ""; duration = ""; description = ""; }
        Spell(string, int, string, string, string, string, string, string);
        string getName() { return name; }
        int getLevel() { return level; }
        string getSchool() { return school; }
        string getCast() { return casting_time; }
        string getRange() { return range; }
        string getComps() { return components; }
        string getDur() { return duration; }
        string getDesc() { return description; }
        void printAll();
        void setName(string n) { name = n; }
        void setLevel(int lv) { level = lv; }
        void setSchool(string sc) { school = sc; }
        void setCast(string ca) { casting_time = ca; }
        void setRange(string r) { range = r; }
        void setComps(string co) { components = co; }
        void setDur(string du) { duration = du; }
        void setDesc(string de) { description += de + " "; }
};

// Parameterized constructor constructs a spell object with all the given attributes
Spell::Spell(string n, int lv, string sc, string ct, string r, string co, string du, string de){
     name = n;
     level = lv; 
     school = sc; 
     casting_time = ct;
     range = r; 
     components = co; 
     duration = du; 
     description = de; 
}

// prints all features of the spell
void Spell::printAll(){
        cout << "NAME: " << getName() << endl;
        cout << "LEVEL: " << getLevel() << endl;
        cout << "SCHOOL: " << getSchool() << endl;
        cout << "CASTING TIME: " << getCast() << endl;
        cout << "RANGE: " << getRange() << endl;
        cout << "COMPONENTS: " << getComps() << endl;
        cout << "DURATION: " << getDur() << endl;
        cout << "DESCRIPTION: " << getDesc() << endl;
        cout << endl;
}

#endif