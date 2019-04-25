// Jonathan Lilley
// CSCI 1300-203
// ide: https://ide.c9.io/jonathanlilley/csci1300
// PROJECT 3: part 5: all helper functions and chunks of the game
#include <iostream>
#include <fstream>
#include "Spell.h"
#include "SList.h"
#include "Player.h"
#include "Monster.h"
using namespace std;

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// general functions ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

string CATCHER; // This global variable does nothing but catch input for pauses

/**
 * Checks to see if a substring is in a string
 */
bool checkForSubstring(string substring, string s){
    int j = 0;
    int k;
    for(int i=0; i<s.length(); i++){
        if(s[i] == substring[j]){
            j++;
            k = i+1;
            while(j<substring.length() && s[k] == substring[j]){
                j++;
                k++;
            }
            if(j == substring.length()){
                return true;
            }
        }
    }
    return false;
}

/**
 * Checks each character in a string to see if it's an integer
 */
bool isIntString(string s){
    for(int i=0; i<s.length(); i++){
        if(s[i]-'0' > 9 || s[i]-'0' < 0){
            return false;
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
////////////////////////////// game functions //////////////////////////////////
/******************************************************************************/
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// list read in fns ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * Reads in list of spells; takes in filename and SList object
 * Opens file
 * loops through each line in the file
 *      If the first letter of the line is a number if the line is empty, skip it
 *      Iterate through the letters of the line until reach '(', then set j to 
 *      ...one before that
 *      set line to the substring of the beginning of the string to j (one before '(')
 *      Increment numSpells (number of spells recorded)
 *      Check for collisions (if the first element of the corresponding hash is not empty)
 *      ...if there's a collision, incrememnt collisions counter
 *      Enter the spell into the list
 * Output the number of collisions as a check
 */
SList readInList(string filename, SList list){
    ifstream spellList;
    spellList.open(filename);
    string line = "";
    int j = 0;
    int numSpells = 0;
    int collisions = 0;
    while(getline(spellList, line)){
        if(line.empty() || (line[0] - '0' > 0 && line[0] - '0' < 10)) continue;
        list.addToList(line, numSpells);
        numSpells++;
        if(list.lookup(line) != -1){
            collisions++;
        }
        list.enter(line);
    }
    //cout << "collisions: " << collisions << endl; // for testing purposes
    return list;
}

/**
 * Reads in individual spells and records them in an array of spells;
 * ...takes in filename, SList object, and array of Spell objects
 * Opens file
 * Reads lines in file
 *      If the line is empty, continue (skip it)
 *      Checks if line has a hash and is a valid spell name
 *          Finds index and hash index for spell, and sets j to 0 (name)
 *      Sets all the attributes of the spell, one line at a time, based on value of j:
 *          j == 0: set name
 *          j == 1: set level and school
 *          j == 2: set casting time
 *          j == 3: set range
 *          j == 4: set spell components
 *          j == 5: set duration
 *          j == 6: fill out description
 */
void readInSpells(string filename, SList list, Spell spells[][COLLISIONMAX]){
    ifstream spellsFile;
    spellsFile.open(filename);
    int i = 0;
    int k = 0;
    int j = 0;
    string line;
    while(getline(spellsFile, line)){
        if(line.empty()) continue;
        if(list.lookup(line) != -1){ //Checks if line is a valid hash
            if(list.getName(line) == line){ //Checks if line is found in the
                                            //...spell list/is a valid spell
                j = 0;
                i = list.findHash(line);
                k = list.lookup(line);
            }
        }
        if(j == 0){
            spells[i][k].setName(line);
        }
        else if(j == 1){
            spells[i][k].setLevel(line[0] - '0');
            spells[i][k].setSchool(line.substr(10, line.length()));
        }
        else if(j == 2){
            spells[i][k].setCast(line.substr(14,line.length()));
        }
        else if(j == 3){
            spells[i][k].setRange(line.substr(7, line.length()));
        }
        else if(j == 4){
            spells[i][k].setComps(line.substr(12, line.length()));
        }
        else if(j == 5){
            spells[i][k].setDur(line.substr(10, line.length()));
        }
        else if(j >= 6){
            spells[i][k].setDesc(line);
        }
        j++;
    }
    cout << endl;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// spellbuy functions //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * Spell selection menu (buying is to see if the player is doing point buy or
 * initial spell choice)
 * This does not contain a main loop itself; rather, this menu function
 * is put inside a loop
 * First for loop collects up the spells of the player's level
 * Second prints them out
 * Then, it takes in a string choice
 *      if choice is not a string of integers, tells the player to enter a number
 *      otherwise, turns choice into c, an integer
 *      then checks if c is 0; if so, exits
 *      then checks if c is invalid option; if so, exits
 *      then checks if c is is a spell choice; if so, adds the spell the player
 *      object; if buying, subtracts 1 point
 *      then checks if c is a information choice; if so, prints out the spell's
 *      information
 * finally, returns player object
 */
Player spellSelect(Player player, SList list, Spell spells[][COLLISIONMAX], bool buying){
    string choice;
    int c;
    string spellOptions[list.getNumSpells()];
    cout << "Please choose from the list below. (To choose a spell, enter its number; please only choose a spell once) " << endl;
    cout << "(To read the spell's aspects, enter 100 plus the spell's number on the list; to exit, enter 0) " << endl;
    cin >> CATCHER;
    int j = 0;
    int i;
    for(int n=0; n<list.getNumSpells(); n++){
        i = list.findHash(list.printListIndex(n));
        int k = list.lookup(list.printListIndex(n));
        if(spells[i][k].getLevel() <= player.getLevel()){
            spellOptions[j] = spells[i][k].getName();
            j++;
        }
    }
    j--;
    for(i=0; i<j; i++){
        cout << i+1 << ". " << spellOptions[i] << endl;
    }
    cin >> choice;
    if(!isIntString(choice)){
        cout << "Please enter a number" << endl;
        return player;
    }
    c = stoi(choice);
    if(c == 0){
        cout << "You did not choose a spell" << endl;
    }
    else if((c<1 || c>j+1) && (c<101 || c>j+101)){
        cout << "Please enter a valid option" << endl;
    }
    else if(c>=1 && c<=j+1){
        player.addSpell(spellOptions[c-1]);
        cout << "You chose " << spellOptions[c-1] << endl;
        if(buying){
            player.subtractPoints(1);
        }
    }
    else if(c>=101 && c<=j+101){
        string s = spellOptions[c-101];
        i = list.findHash(s);
        j = list.lookup(s);
        spells[i][j].printAll();
    }
    return player;
}


/**
 * Spell buy main function
 * Loops through the spell buy menu until either the player has no more points or
 * the player enters 0 to exit
 */
Player spellBuy(Player player, SList list, Spell spells[][COLLISIONMAX]){
    string choice;
    cout << "Welcome to the spell shop. Enter 0 to quit, or any number to continue." << endl;
    cout << "You have " << player.getPoints() << " points." << endl;
    while(player.getPoints()>0){
        cin >> choice;
        if(choice == "0"){
            break;
        }
        player = spellSelect(player, list, spells, true);
    }
    if(player.getPoints() == 0){
        cout << "You are out of points" << endl;
    }
    return player;
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////// intro fns ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * First intro section -- returns a player object with input name
 */
Player intro_getName(){
    string playerName;
    cout << "Welcome to SpellQuest! This is a text-based game of magic and" 
    << " adventure.";
    cout << "Whenever you see a pause, press any character key, then enter!";
    cin >> CATCHER;
    cout << "What is your name?" << endl;
    cin >> playerName;
    Player player = Player(playerName);
    cout << "What a fantastic name!";
    cin >> CATCHER;
    return player;
}

/**
 * Second intro section -- returns an int maxLv with maximum level to be played to
 */
int intro_getLevel(){
    cout << "Now, what level would you like to play to? "
    << "(choose a number between 2 and 9)" << endl;
    string maxLv;
    int maxLvint;
    bool chosen = false;
    while(!chosen){
        cin >> maxLv;
        if(!isIntString(maxLv)){
            cout << "Please enter a number" << endl;
            continue;
        }
        maxLvint = stoi(maxLv);
        if(maxLvint > 9 || maxLvint < 2){
            cout << "Please enter a number between 2 and 9" << endl;
        }
        else{
            chosen = true;
        }
    }
    return maxLvint;
}

/**
 * Third intro -- description of quest
 */
void quest_intro(){
    cout << "Great! Shall we begin then?" << endl;
    cout << "Welcome to the land of <landname>. This land used to be a "
    << "prosperous kingdom full of farmers, artisans, and alchemists. But one day...";
    cin >> CATCHER;
    cout << "A horrible monster appeared. The beast invaded the land, followed "
    << "by great shadows and demons who laid waste to the towns and villages of"
    << " the great kingdom.";
    cin >> CATCHER;
    cout << "However, legend says that one day a great hero will come to the land"
    << " from afar to rid the kingdom of the great monster. Who could this great "
    << "hero be...?" << endl;
    cin >> CATCHER;
    cout << "During your travels, you come across a land smothered in darkness, "
    << "filled with beasts and demons of every kind imaginable.";
    cin >> CATCHER;
    cout << "The people, who look like they may once have been hospitable, have been turned into "
    << "ghastly apparitions who want nothing to do with you.";
    cin >> CATCHER;
    cout << "Only a few are left who are friendly and kind to you. How will you "
    << "save this land, with your limited power?" << endl;
    cin >> CATCHER;
}


/**
 * Intro 3; first 3 spell choice menu
 * Allows the player to check out what the spells do and pick 3
 * Adds them to the player's spell list
 * returns the player object with the new spell list
 */
Player intro_spellSelect(Player player, SList list, Spell spells[][COLLISIONMAX]){
    cout << "Before you begin your quest, you must choose three spells to begin with." << endl;
    int spellsChosen = 0;
    string choice;
    while(spellsChosen < 3){
        player = spellSelect(player, list, spells, false);
        spellsChosen = player.getNumSpellsKnown();
    }
    cout << "Well chosen!" << endl;
    return player;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////// RE functions ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * Monster initialiation for random encounters; takes in an encounter level
 * Initializes variables to catch all of the values needed to initialize a monster object
 * Uses a switch block to determine all of the monster object values
 *      if 1, does peaceful citizen; town location; slow speed; close dist
 *      if 2, does goblin; forest location; fast speed; close distance
 *      if 3, giant beast; forest location; medium speed; far dist
 *      if 4, rioter; town location, fast speed, medium dist
 *      if 5, dragon; cave location; medium speed; far dist
 * Set monster object, then returns it
 */
Monster initMob(int encounterLv){
    int randomized = (rand() % 5) + 1;
    string name;
    string location;
    char speed;
    char distance;
    switch(randomized){
        case 1:
            name = "Peaceful citizen";
            location = "Town";
            speed = 's';
            distance = 'c';
            break;
        case 2:
            name = "Goblin";
            location = "Forest";
            speed = 'f';
            distance = 'c';
            break;
        case 3:
            name = "Giant beast";
            location = "Forest";
            speed = 'm';
            distance = 'f';
            break;
        case 4:
            name = "Rioter";
            location = "Town";
            speed = 'f';
            distance = 'm';
            break;
        case 5:
            name = "Dragon";
            location = "Cave";
            speed = 'm';
            distance = 'f';
            break;
    }
    Monster mob(name, location, encounterLv, speed, distance);
    return mob;
}

/**
 * Takes in a monster and prints out all the features of the monster
 */
void assess(Monster mob){
    cout << "It looks as strong as you! Maybe a spell of your level would do the trick." << endl;
    cout << "It looks ";
    switch(mob.getSpeed()){
        case 'f':
            cout << "very fast! Use a quick spell, bonus action or action!" << endl;
            break;
        case 'm':
            cout << "somewhat fast. Use a spell of one minute or less." << endl;
            break;
        case 's':
            cout << "very slow. Any spell will do." << endl;
            break;
    }
    cout << "It is ";
    switch(mob.getDistance()){
        case 'f':
            cout << "far away. Use a long range spell, 60 feet or more!" << endl;
            break;
        case 'm':
            cout << "10 feet away. Use a spell of range 10 feet or more to get it." << endl;
            break;
        case 'c':
            cout << "very close! Any spell range will do!" << endl;
            break;
    }
}

/**
 * Choose spell in combat
 * Allows the player to read the description of the spell
 * Also allows the player to choose a spell
 * Also allows the player to choose 0 to cancel
 * Returns the chosen spell
 */
string chooseSpell(Player player, SList list, Spell spells[][COLLISIONMAX]){
    string chosenSpell;
    string choice;
    int c;
    while(chosenSpell.empty()){
        cout << "What spell will you choose? To view a spells effects, enter the spell number + 100" << endl;
        player.printKnownSpells();
        cin >> choice;
        if(!isIntString(choice)){
            cout << "Please enter a number" << endl;
            continue;
        }
        c = stoi(choice);
        if(c == 0){
            cout << "You don't choose a spell" << endl;
            return chosenSpell;
        }
        else if((c<1 || c>player.getNumSpellsKnown()+1) && (c<101 || c>player.getNumSpellsKnown()+101)){
            cout << "Please enter a valid number" << endl;
        }
        else if(c>=101 && c<=player.getNumSpellsKnown()+101){
            string spell = player.getSpellIndex(c-101);
            int i = list.findHash(spell);
            int k = list.lookup(spell);
            spells[i][k].printAll();
        }
        else if(c>=1 && c<=player.getNumSpellsKnown()+1){
            chosenSpell = player.getSpellIndex(c-1);
        }
    }
    return chosenSpell;
}

/**
 * Checks if a spell works by passing a monster and spell choice and comparing
 * the spell's attributes and the monster's characteristics
 * fail = return false, success = return true
 * compares levels; if more than one lower, fail
 * compares distance;
 *      case f: if self, touch, 5 feet, 10 feet, or 30 feet, fail
 *      case m: if self, touch, or 5 feet, fail
 *      implicit case c: never fail
 * compares speed;
 *      case f: if not action (or bonus action), fail
 *      case m: if not action or 1 minute, fail
 *      implicit case s: never fail
 * success
 */
bool checkSpellWorks(string sc, Monster mob, SList list, Spell spells[][COLLISIONMAX]){
    int i = list.findHash(sc);
    int k = list.lookup(sc);
    Spell s = spells[i][k];
    string dist = s.getRange();
    string speed = s.getCast();
    if(!(s.getLevel() >= mob.getLevel()-1)){
        return false;
    }
    switch(mob.getDistance()){
        case 'f':
            if(checkForSubstring("Self", dist) || checkForSubstring("Touch", dist) || checkForSubstring("5 feet", dist) 
            || checkForSubstring("10 feet", dist) || checkForSubstring("30 feet", dist)){
                return false;
            }
            break;
        case 'm':
            if(checkForSubstring("Self", dist) || checkForSubstring("Touch", dist) || checkForSubstring("5 feet", dist)){
                return false;
            }
            break;
    }
    switch(mob.getSpeed()){
        case 'f':
            if(!checkForSubstring("action", speed)){
                return false;
            }
            break;
        case 'm':
            if(!(checkForSubstring("action", speed) || checkForSubstring("1 minute", speed))){
                return false;
            }
            break;
    }
    return true;
}

/**
 * Encounter option menu
 * Runs through the options, then takes in player input
 * If input is 1, assesses the monster
 * If input is 2, chooses a spell
 *      if the spell is adequate to beat the monster, prints out success and returns true
 * If input is 3, runs
 *      if no spells are adequate, the player runs away and succeeds
 *      if the player runs away but could have beat the monster, its a failure
 */
bool encounterOptions(Player player, Monster mob, SList list, Spell spells[][COLLISIONMAX]){
    string choice; // catches choice variable
    int c; // int version of choice
    string sc; // spell choice
    bool validChoice = false;
    bool works = false;
    while(!validChoice){
        cout << "What will you do? " << endl;
        cout << "Your options are: " << endl;
        cout << "1. Assess | 2. Cast a spell | 3. Run away" << endl;
        cout << "(Cast a spell that fits the monster best. If none do, run away!)" << endl;
        cin >> choice;
        if(!isIntString(choice)){
            cout << "Please enter a number" << endl;
            continue;
        }
        c = stoi(choice);
        switch(c){
            case 1:
                assess(mob);
                break;
            case 2:
                while(!works){
                    sc = chooseSpell(player, list, spells);
                    if(sc.empty()){
                        break;
                    }
                    int i = list.findHash(sc);
                    int k = list.lookup(sc);
                    works = checkSpellWorks(sc, mob, list, spells);
                    if(works){
                        cout << "You succeed!" << endl;
                        return true;
                    }
                    cout << "It didn't work! You failed!" << endl;
                    return false;
                }
                break;
            case 3:
                for(int j=0; j<player.getNumSpellsKnown(); j++){
                    sc = player.getSpellIndex(j);
                    int i = list.findHash(sc);
                    int k = list.lookup(sc);
                    works = checkSpellWorks(sc, mob, list, spells);
                    if(works){
                        cout << "You could have used a spell! You failed!" << endl;
                        return false;
                    }
                }
                cout << "Nothing would have worked, so you got away safely! Success!" << endl;
                return true;
            if(sc.empty()){
                break;
            }
        }
    }
}

/**
 * Random encounter
 * Initializes a monster, then introduces it
 * checks if the player succeeds an encounter with encounterOptions
 * If the player fails, subtract hp equal to the players level time 10
 * Otherwise, add 100 XP
 * return the update player object
 */
Player randomEncounter(Player player, int encounterLv, SList list, Spell spells[][COLLISIONMAX]){
    Monster mob = initMob(encounterLv);
    cout << "On your journey, you enter a " << mob.getLocation() << ", and ..." << endl;
    cin >> CATCHER;
    cout << "A " << mob.getName() << " appears!" << endl;
    bool outcome = encounterOptions(player, mob, list, spells);
    if(!outcome){
        int dmg;
        cout << "You take a hit and take " << player.getLevel()*5 << " damage!" << endl;
        player.subtractHP(player.getLevel()*5);
    }
    else{
        player.addXP(100);
        player.addPoints(player.getLevel()); // add points for spells
    }
    cout << endl;
    return player;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// final battle ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Final battle like a random encounter, but special flavor text and autofail if loss
Player finalBattle(Player player, SList list, Spell spells[][COLLISIONMAX]){
    Monster mob("Big Bad Evil Guy", "Dungeon", player.getLevel(), 'f', 'f');
    cout << "You enter the castle and explore the dungeon. It's a dark, dank, twisting maze of" << endl;
    cout << "hallways and passages connecting large rooms." << endl;
    cout << "After hours of searching, you come across a great shadowy beast!" << endl;
    bool outcome = encounterOptions(player, mob, list, spells);
    if(!outcome){
        player.subtractHP(99999); // autofail if you don't beat the boss
    }
    cout << endl;
    return player;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// other functions /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * Checks if player levels up
 * If XP = level * 300: level up
 *      add a level
 *      add hp
 * return the player object
 */
Player checkLevelUp(Player player){ 
    if(player.getXP() >= player.getLevel() * 300){ 
        player.addLevel(); 
        player.addHP((rand() % 15) + 1); 
    } 
    return player;
}

// Checks if player wishes to try again
bool tryAgain(){
    string choice;
    while(true){
        cout << "Try again? (Y/N)" << endl;
        cin >> choice;
        if(choice == "Y" || choice == "y"){
            cout << "Good luck!" << endl;
            return true;
        }
        if(choice == "N" || choice == "n"){
            return false;
        }
        else{
            cout << "Please enter Y/N" << endl;
        }
    }
}

// Checks if player HP is 0
bool checkFail(Player player){
    if(player.getHP() <= 0){
        return true;
    }
    return false;
}

// Prints out failure sequence
void failureSequence(){
    cout << "You died!" << endl;
    cout << "The kingdom fell under darkness, for all eternity, until a new hero arises..." << endl;
}

// Prints out success sequence
void successSequence(){
    cout << "You succeeded in your quest!" << endl;
    cout << "The king thanks you greatly and the citizens throw a great festival for you!" << endl;
    cout << "But after the party is over, on you must go, to other quests; other kingdoms to save..." << endl;
}