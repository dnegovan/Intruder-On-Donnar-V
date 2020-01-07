/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: The Game class contains the data members and methods that
control the flow of the game.  create a Game object, and call the startMenu
to ask the player how to start the game (see below).  Then call the play method
to trigger the play loop.
------------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>

#include "dansLibrary.hpp"
#include "Game.hpp"
#include "Bridge.hpp"
#include "Corridor.hpp"
#include "CaptainsQuarters.hpp"
#include "Lounge.hpp"
#include "Lab.hpp"
#include "CrewQuarters.hpp"
#include "Engineering.hpp"
#include "formatting.hpp"
#include "items.hpp"

//countdown start points
const int TIME_START = 18;
const int TIME_HINT = 14;
const int TIME_TIL_SPREAD = 4;

//converts time int to "minutes" for display
const int TIME_FACTOR = 10;


/*-----------------------------------------------------------------------------
constructor
------------------------------------------------------------------------------*/
Game::Game()
{
    //initialize time
    timeLeft = TIME_START;
    timeTilHint = TIME_HINT;
    deadline =   "                    TIME UNTIL INCUBATION";
    objective1 = "-Talk to the crew to discover the imposter";
	objective2 = "-Gather ingredients and produce Neutralization Compound";
	objective3 = "-Neutralize the parasite";

    //allocate rooms
    bridge = new Bridge;
    corridor = new Corridor;
    captainsQ = new CaptainsQuarters;
    lounge = new Lounge;
    lab = new Lab;
    crewQ = new CrewQuarters;
    engineering = new Engineering;

    //set player position
    currentSpace = corridor;

    //build map
    bridge->up = nullptr;
    bridge->right = nullptr;
    bridge->down = corridor;
    bridge->left = nullptr;
    corridor->up = bridge;
    corridor->right = lounge;
    corridor->down = lab;
    corridor->left = captainsQ;
    captainsQ->up = nullptr;
    captainsQ->right = corridor;
    captainsQ->down = nullptr;
    captainsQ->left = nullptr;
    lounge->up = nullptr;
    lounge->right = nullptr;
    lounge->down = crewQ;
    lounge->left = corridor;
    lab->up = corridor;
    lab->right = nullptr;
    lab->down = engineering;
    lab->left = nullptr;
    crewQ->up = lounge;
    crewQ->right = nullptr;
    crewQ->down = nullptr;
    crewQ->left = nullptr;
    engineering->up = lab;
    engineering->right = nullptr;
    engineering->down = nullptr;
    engineering->left = nullptr;

}

/*-----------------------------------------------------------------------------
destructor
------------------------------------------------------------------------------*/
Game::~Game()
{
    //free memory
    delete bridge;
    delete corridor;
    delete captainsQ;
    delete lounge;
    delete lab;
    delete crewQ;
    delete engineering;
}



/*-----------------------------------------------------------------------------
plays the game loop until an endgame state is reached
provided int (1, 2, or 3) dictates whether to show prologue, skip it, or quit,
respectively
------------------------------------------------------------------------------*/
void Game::play(int start)
{
    std::string temp;

    switch (start)
    {
        case 1:
            printPrologue();
            break;
        case 2:
            break;
        case 3:
            return;
    }

    printTitle();
    int input = 0;

    while (input != 1)
    {
        std::cout << "\nEnter 1 to continue:\n";
        input = getInteger();
    }
    std::cout << std::endl << std::endl;

    //print intro - instructions
    printFile("intro.txt", RESET, 0);

    std::cout << "\nHint: This game is played using dynamic numbered menus, so "
              << "keep \none hand over the number keys and one hand over the "
              << "enter key.\n"
              << "\nPress enter to begin\n";
    getline(std::cin, temp);

    //initial status
    printShip();

    //gameplay loop
    while (markNelson.state == UNFINISHED)
    {
        if (currentSpace->actionMenu(markNelson))  //returns false if game over
        {
    		printShip();
    		if (move())  //only true if player decides to move
            {
                //time winds down as player moves
    			if(decrementTime())  //false if game over
                {
                    //show updated map/status
                    printShip();
                }
            }
        }
    }

    printEnding();
}

/*-----------------------------------------------------------------------------
menu that lets user choose to view prologue or not, or to quit
only displayed if it's not the first playthrough, checks file
------------------------------------------------------------------------------*/
int Game::startMenu()
{
    int input = 0;
    std::cout << "\n";

    while (input < 1 || input > 3)
    {
        std::cout << "1. Begin New Game With Prologue\n"
                  << "2. Begin New Game Without Prologue\n"
                  << "3. Quit" << std::endl;

        input = getInteger();
    }

    return input;
}





/*------------------      PRIVATE HELPER FUNCTIONS        --------------------*/



/*-----------------------------------------------------------------------------
prints the prologue, setup to the story.  read from prologue txt file
------------------------------------------------------------------------------*/
void Game::printPrologue()
{

    std::cout << NARRATOR_COLOR << std::endl
              << "As you approach the terminal, you notice an alert, "
                 "blinking furiously.\n\n";
    wait(MED);

    std::cout << DIALOGUE_COLOR << "That wasn’t there when we left...\n\n";
    wait(MED);

    std::cout << NARRATOR_COLOR
              <<"Alone in the corridor, you enter your login credentials.\n\n";
    wait(MED);

    printFile("prologueA.txt", PROLOGUE_COLOR, MED);
    std::cout << std::endl;
    printFile("prologueB.txt", NARRATOR_COLOR, MED);
    wait(MED);

    std::cout << RESET;
}


/*-----------------------------------------------------------------------------
prints the cool title card
------------------------------------------------------------------------------*/
void Game::printTitle()
{
    std::ifstream stream("titleCard.txt", std::ios::in);
    std::string contents;

    std::cout << CYAN;
    while (getline(stream, contents))
    {
        std::cout << contents << std::endl;
    }
    std::cout << "\n\n" << RESET;
    stream.close();
}


/*-----------------------------------------------------------------------------
Shows user available move options, updates currentSpace with their choice and
returns true if they move, returns false if they cancel move
------------------------------------------------------------------------------*/
bool Game::move()
{
    int input = 0;
    int menuNum;
    int up, down, left, right;

    while (input < 1 || input > menuNum)
    {
        menuNum = 1;

        //need to store menu number for each direction then use in switch case
        up = 0, down = 0, left = 0, right = 0;

        std::cout << std::endl;
        //list option that are available
        if (currentSpace->up)  //false if nullptr
        {
            up = menuNum;
            std::cout << menuNum << ". To "
                      << currentSpace->up->getRoomName() << std::endl;
            menuNum++;
        }
        if (currentSpace->right)
        {
            right = menuNum;
            std::cout << menuNum << ". To "
                      << currentSpace->right->getRoomName() << std::endl;
            menuNum++;
        }
        if (currentSpace->down)
        {
            down = menuNum;
            std::cout << menuNum << ". To "
                      << currentSpace->down->getRoomName() << std::endl;
            menuNum++;
        }
        if (currentSpace->left)
        {
            left = menuNum;
            std::cout << menuNum << ". To "
                      << currentSpace->left->getRoomName() << std::endl;
            menuNum++;
        }

        std::cout << menuNum << ". Cancel" << std::endl;

        input = getInteger();
    }

    if (input == up)
    {
            currentSpace = currentSpace->up;
            return true;
    }
    else if (input == down)
    {
            currentSpace = currentSpace->down;
            return true;
    }
    else if (input == left)
    {
            currentSpace = currentSpace->left;
            return true;
    }
    else if (input == right)
    {
            currentSpace = currentSpace->right;
            return true;
    }
    //if we get here they must have hit cancel
    return false;
}


/*-----------------------------------------------------------------------------
decrements the time (moves) remaining
adjusts game state and/or resets timer when necessary
------------------------------------------------------------------------------*/
bool Game::decrementTime()
{
    std::string temp;
	if (timeLeft > 1)
    {
		timeLeft--;

        //check if we should show hint
        if (timeTilHint > 1)
        {
            timeTilHint--;
        }
        else
        {
            printFile("hint.txt", RED, 0);
            std::cout << "\nPress enter to continue" << std::endl;
            getline(std::cin, temp);
            timeTilHint = TIME_HINT;
        }
        //keep playing
        return true;
    }
    else
    {
        if (!markNelson.incubated)
        {
    		markNelson.incubated = true;
    		std::cout << RED
                      << "\nTHE PARASITE HAS INCUBATED.  You must now kill the "
                      << "host before it \nspreads to another crew member.\n"
                      << RESET << "\nPress enter to continue" << std::endl;
            getline(std::cin, temp);
            if (!markNelson.pack.checkFor(compound))
            {
    		          objective2 =
                      "-Neutralize the parasite - FAILED";
            }
            objective3 = "-kill any infected crewMembers";
    		timeLeft = TIME_TIL_SPREAD;
    		deadline = "          TIME UNTIL NEXT CREW MEMBER IS INFECTED";
            //keep playing
            return true;
        }
    	else
        {
            //check if gameOver
            bool continueGame = parasiteSpreads();
            //if not display updates
            if (markNelson.state == UNFINISHED)
            {   //don't need to display this if the game is over
                std::cout << RED
                          << "THE PARASITE HAS SPREAD TO ANOTHER CREW MEMBER.\n"
                          << "Kill any infected to save the rest of your crew\n"
                          << RESET << "\nPress enter to continue" << std::endl
                          << std::endl;
                getline(std::cin, temp);
        		timeLeft = TIME_TIL_SPREAD;
        		objective1 =
                    "-talk to the crew to discover all imposters";
            }
            return continueGame;
        }
    }
}


/*-----------------------------------------------------------------------------
converts time int to a time value, formats and outputs to screen
------------------------------------------------------------------------------*/
void Game::printTime()
{
    std::cout << MAP_COLOR << deadline << ": " << TIME_COLOR;
    int niceTime = timeLeft * TIME_FACTOR;
    if (niceTime > 59)
    {
        std::cout << niceTime/60;
    }
    else
    {
        std::cout << "0";
    }

    std::cout << ":";
    if (niceTime % 60 == 0)
    {
        std::cout << "0";
    }
    std::cout << niceTime % 60 << RESET << std::endl;
}


/*-----------------------------------------------------------------------------
parasite spreads to next crew member
updates data members, Player stats and game state
return false if game needs to end, true to keep playing
------------------------------------------------------------------------------*/
bool Game::parasiteSpreads()
{
    //spread to next person in the chain if they're alive
    if (!bridge->getOccupant()->getInfected()
        && bridge->getOccupant()->getAlive())
    {
        bridge->getOccupant()->setInfected(true);
        markNelson.crewInfected++;
        return true;
    }
    else if (!lounge->getOccupant()->getInfected()
             && lounge->getOccupant()->getAlive())
    {
        lounge->getOccupant()->setInfected(true);
        markNelson.crewInfected++;
        return true;
    }
    else if (!crewQ->getOccupant()->getInfected()
             && crewQ->getOccupant()->getAlive())
    {
        crewQ->getOccupant()->setInfected(true);
        markNelson.crewInfected++;
        return true;
    }
    else if (!engineering->getOccupant()->getInfected()
              && engineering->getOccupant()->getAlive())
    {
        engineering->getOccupant()->setInfected(true);
        markNelson.crewInfected++;
        return true;
    }
    //you are the last one, so game over - trigger appropriate ending
    else if (markNelson.crewDead == 0)
    {
        markNelson.state = PLAYER_AND_CREW_INFECTED;
        return false;
    }
    else if (markNelson.crewDead == 1)
    {
        markNelson.state = KILLED_PERSON_INFECTED_ANYWAY;
        return false;
    }
    else
    {
        markNelson.state = KILLED_PEOPLE_INFECTED_ANYWAY;
        return false;
    }
}


/*-----------------------------------------------------------------------------
prints the state of the ship - map and game stats
------------------------------------------------------------------------------*/
void Game::printShip()
{
    //print Map, indicate location with color of room name
    //names are red if occupant is dead
    //Stats are printed after the map, see below
    std::cout << MAP_COLOR << std::endl <<

    "                      MAP OF STARSHIP DONNAR V                       \n"
    "+-------------------------------------------------------------------+\n"
    "|                              ";

    if (currentSpace == bridge)
    {
        std::cout << LOCATION_COLOR << "BRIDGE";
    }
    else
    {
        std::cout << MAP_COLOR << "BRIDGE";
    }

    std::cout << MAP_COLOR <<  "                               |\n"
    "|                                                  ";

    if(bridge->getOccupant()->getAlive())
    {
        std::cout << bridge->getOccupant()->getName();
    }
    else
    {
        std::cout << RED << bridge->getOccupant()->getName() << MAP_COLOR;
    }

    std::cout << MAP_COLOR << "           |\n"
    "|                                                                   |\n"
    "+------------------------+-------+     +------+---------------------+\n"
    "|   ";

    if (currentSpace == captainsQ)
    {
        std::cout << LOCATION_COLOR << "CAPTAIN'S QUARTERS";
    }
    else
    {
        std::cout << MAP_COLOR << "CAPTAIN'S QUARTERS";
    }

    std::cout << MAP_COLOR << "   |    ";

    if (currentSpace == corridor)
    {
        std::cout << LOCATION_COLOR << "MAIN CORRIDOR";
    }
    else
    {
        std::cout << MAP_COLOR << "MAIN CORRIDOR";
    }

    std::cout << MAP_COLOR <<  "   |        ";

    if (currentSpace == lounge)
    {
        std::cout << LOCATION_COLOR << "LOUNGE";
    }
    else
    {
        std::cout << MAP_COLOR << "LOUNGE";
    }

    std::cout <<  MAP_COLOR << "       |\n"
    "|                        +                    +                     |\n"
    "|                                                                   |\n"
    "|                        +                    +                     |\n"
    "|         ";

    if(captainsQ->getOccupant()->getAlive())
    {
        std::cout << captainsQ->getOccupant()->getName();
    }
    else
    {
        std::cout << RED << captainsQ->getOccupant()->getName() << MAP_COLOR;
    }

    std::cout << "          |                    |               ";

    if(lounge->getOccupant()->getAlive())
    {
        std::cout << lounge->getOccupant()->getName();
    }
    else
    {
        std::cout << RED << lounge->getOccupant()->getName() << MAP_COLOR;
    }

    std::cout << " |\n"
    "+------------------------+---+  +--+----------+--------+    +-------|\n"
    "|        ";

    if (currentSpace == lab)
    {
        std::cout << LOCATION_COLOR << "MEDICAL LAB";
    }
    else
    {
        std::cout << MAP_COLOR << "MEDICAL LAB";
    }

    std::cout << MAP_COLOR << "               |      ";

    if (currentSpace == crewQ)
    {
        std::cout << LOCATION_COLOR << "CREW QUARTERS";
    }
    else
    {
        std::cout << MAP_COLOR << "CREW QUARTERS";
    }

    std::cout << MAP_COLOR << "             |\n"
    "|                                  |                                |\n"
    "|                                  |                                |\n"
    "|                                  |      ";

    if(crewQ->getOccupant()->getAlive())
    {
        std::cout << crewQ->getOccupant()->getName();
    }
    else
    {
        std::cout << RED << crewQ->getOccupant()->getName() << MAP_COLOR;
    }

    std::cout << "                      |\n"
    "+-----------+     +----------------+--------------------------------+\n"
    "|                           ";

    if (currentSpace == engineering)
    {
        std::cout << LOCATION_COLOR << "ENGINEERING";
    }
    else
    {
        std::cout << MAP_COLOR << "ENGINEERING";
    }


    std::cout << MAP_COLOR << "                             |\n"
    "|                                                   ";

    if(engineering->getOccupant()->getAlive())
    {
        std::cout << engineering->getOccupant()->getName();
    }
    else
    {
        std::cout << RED << engineering->getOccupant()->getName() << MAP_COLOR;
    }

    std::cout << "          |\n"
    "|                                                                   |\n"
    "+-------------------------------------------------------------------+"
    << RESET << std::endl;


    //print time left
    printTime();

    //print crew stats
    if (markNelson.crewDead > 0)
    {
        std::cout << RED << "                            CREW DEAD: "
                  << markNelson.crewDead
                  << RESET << std::endl;
    }
    std::cout << MAP_COLOR << "                          CREW INFECTED: "
              << markNelson.crewInfected
              <<  "\n";

    //print ingredients found
    if (markNelson.ingredientsFound > 0 && !markNelson.pack.checkFor(compound))
    {
    std::cout << MAP_COLOR << "                       INGREDIENTS FOUND: "
              << markNelson.ingredientsFound << "/5"
              << RESET << std::endl;
    }

    //print objectives
    std::cout << MAP_COLOR << "CURRENT OBJECTIVES \n"
              << objective1 << std::endl
              << objective2;
    if (markNelson.pack.checkFor(compound))
    {
        std::cout << " - COMPLETE";
    }
    std::cout << std::endl << objective3 << RESET << "\n" << std::endl;

}


/*-----------------------------------------------------------------------------
prints the ending based on the game state enum value
------------------------------------------------------------------------------*/
void Game::printEnding()
{
    //enum is in the same order as file.  formula to find 1st line of ending
    int line = markNelson.state * 4 - 2;

    std::ifstream stream("endings.txt", std::ios::in);
    std::string endingText1;
    std::string endingText2;

    //get each line until we have the right one, then stop
    for (int i = 0; i < line; i++)
    {
        getline(stream, endingText1);
    }
    //each ending is two lines, have first using loop above, so grab second one
    getline(stream, endingText2);

    std::cout << std::endl << std::endl;

    //check for best ending, different color if so
    if (markNelson.state == SAVED_WIFE)
    {
        std::cout << NARRATOR_COLOR << "PARASITE ERADICATED!\n";
        printString(endingText1, NARRATOR_COLOR, SHORT);
        printString(endingText2, NARRATOR_COLOR, SHORT);
    }
    else
    {
        std::cout << RED << "GAME OVER\n";
        printString(endingText1, RED, SHORT);
        printString(endingText2, RED, SHORT);
    }

    //long dramatic pause before play again menu
    std::cout << std::endl;
    wait(LONG);
    std::cout << std::endl;

    stream.close();
}
