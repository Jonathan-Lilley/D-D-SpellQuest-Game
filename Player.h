// Jonathan Lilley
// CSCI 1300-203
// ide: https://ide.c9.io/jonathanlilley/csci1300
// PROJECT 3: part 3: player class
#include <iostream>
#include <string>
using namespace std;

/**
 * Player class
 * private variables:
 *      points
 *      level
 *      XP (for tracking levels)
 *      numSpellsKnown for tracking the number of spells known
 *      knownSpells array of spells known
 * public member functions:
 *      Default (set everything to 0/empty) and parameterized (sets name and 
 *      ...everything to 0) constructors
 *      getPoints returns points
 *      getXP returns XP
 *      getLevel returns the level
 *      getNumSpellsKnown returns number of spells known
 *      checkLevelUp checks if the player should level up, and if so, does so
 *      ...(condition: XP > 300*level)
 *      printKnownSpells prints known spells
 *      checkForSpell checks for an input spell
 *      addPoints adds input number of points
 *      subtractPoints subtracts input number of points
 *      addXP adds an input XP
 *      addSpell inserts a spell to knownSpells and increments numSpellsKnown
 */
class Player{
    private:
        string playername;
        int HP;
        int points;
        int level;
        int XP;
        int numSpellsKnown;
        string knownSpells[50];
    public:
        Player() { playername = ""; HP = 30; points = 0; level = 1; XP = 0; numSpellsKnown = 0; }
        Player(string n) { playername = n; HP = 30; points = 0; level = 1; XP = 0; numSpellsKnown = 0; }
        string getName() { return playername; }
        int getHP() { return HP; }
        int getPoints() { return points; }
        int getXP() { return XP; }
        int getLevel() { return level; }
        int getNumSpellsKnown() { return numSpellsKnown; }
        void printKnownSpells();
        string getSpellIndex(int i) { return knownSpells[i]; }
        void addLevel() { level++; }
        void addHP(int health) { HP += health; }
        void subtractHP(int dmg) { HP -= dmg; }
        void addPoints(int p) { points += p; }
        void subtractPoints(int p) { points -= p; }
        void addXP(int morexp) { XP += morexp; }
        bool addSpell(string spell);
};

//Prints each spell in a loop
void Player::printKnownSpells(){
    for(int i=0; i<numSpellsKnown; i++){
        cout << i+1 << ". " << knownSpells[i] << endl;
    }
}

//Iteratively checks for first empty slot in spell dictionary and fills it with input spell
bool Player::addSpell(string spell){
    if(numSpellsKnown >= 50){
        cout << "Can't learn any more spells" << endl;
        return false;
    }
    knownSpells[numSpellsKnown++] = spell;
    return true;
}