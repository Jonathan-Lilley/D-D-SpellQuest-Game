// Jonathan Lilley
// CSCI 1300-203
// ide: https://ide.c9.io/jonathanlilley/csci1300
// PROJECT 3: part 6: main class
#include <iostream>
#include <string>
#include "HelperFns.h"
using namespace std;


// Main game function; each piece is commented individually
void game(){
    srand(time(0));
    // All major variables organized up here
    SList list; // spell list object
    Spell spells[MAX][COLLISIONMAX];
    Player player;
    int maxLv;
    bool failure = false;
    
    // Read in files of spells
    string listfilename = "spellList.txt"; // spell list file
    string spellfilename = "spells.txt";
    list = readInList(listfilename, list); // reads in spells
    readInSpells(spellfilename, list, spells);
    
    // Intro sequence
    player = intro_getName();
    maxLv = intro_getLevel();
    cout << endl;
    //quest_intro();
    player = intro_spellSelect(player, list, spells);
    
    // Random encounters sequence
    int prevLv = 1;
    int successes = 0;
    for(int i=1; i<maxLv; i++){
        prevLv = player.getLevel();
        while(player.getLevel() == prevLv && player.getHP()>0){
            cout << "Your level is: " << player.getLevel() << endl;
            cout << "Your XP is: " << player.getXP() << endl;
            cout << "Your HP is: " << player.getHP() << endl;
            player = randomEncounter(player, i+1, list, spells);
            failure = checkFail(player); // checks for failure
            // if failure, does failure sequence and exits the function with false
            if(failure){
                failureSequence();
                return;
            }
            player = checkLevelUp(player); // checks for levelup
            if(player.getPoints()>0){
                player = spellBuy(player, list, spells); // point buy for spells
            }
        }
    }
    
    // Final battle sequence
    player = finalBattle(player, list, spells);
    failure = checkFail(player); // checks for failure
    // if failure, does failure sequence and exits the function with false
    if(failure){
        failureSequence();
        return;
    }
    // Quest success! Exits with true
    successSequence();
    return;
}

int main(){
    bool play = true;
    /** 
    * Play the game while the player hasn't chosen to quit
    * play is true if the playerdecided to try again
    */
    while(play){
        game(); // play game
        play = tryAgain(); // Check if player wishes to play again
    }
    cout << "Thank you for playing!" << endl;
    return 0;
}