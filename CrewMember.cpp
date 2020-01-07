/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data and methods for the CrewMember abstract class.
Derived crew have different data member values but all use these methods
------------------------------------------------------------------------------*/

#include "CrewMember.hpp"
#include <algorithm>

/*-----------------------------------------------------------------------------
constructor, define in derived classes
------------------------------------------------------------------------------*/
CrewMember::CrewMember()
{
    this->alive = true;
}

/*-----------------------------------------------------------------------------
virtual destructor
------------------------------------------------------------------------------*/
CrewMember::~CrewMember()
{
}

/*-----------------------------------------------------------------------------
getters and setters
------------------------------------------------------------------------------*/
std::string CrewMember::getName()
{
    return name;
}

void CrewMember::setAlive(bool alive)
{
    this->alive = alive;
}

bool CrewMember::getAlive()
{
    return alive;
}

void CrewMember::setInfected(bool infected)
{
    this->infected = infected;
}

bool CrewMember::getInfected()
{
    return infected;
}


/*-----------------------------------------------------------------------------
the menu for conversing with occupant.  each crew member has one thing to say
about every other crew member. contained in dialogue files.
------------------------------------------------------------------------------*/
void CrewMember::talk()
{
    //create otherCrew vector by removing this name from copy of full crew list
    otherCrew = crewList;
    auto iterator = std::find(otherCrew.begin(), otherCrew.end(), name);
    otherCrew.erase(iterator);

    int input = 0;

    std::cout << NARRATOR_COLOR "\n" << fullTitle << RESET << std::endl;

    //if the occupant is infected, use special dialogue (different txt file)
    std::string fileName;
    if (infected)
    {
        //use infected dialogue options
        fileName = name + "Infected.txt";
    }
    else
    {
        //use regular dialogue options
        fileName = name + ".txt";
    }

    //open dialogue file
    std::ifstream stream(fileName, std::ios::in);

    //diaplay greeting (1st line of file)
    std::string dialogue;
    getline(stream, dialogue);
    std::cout << DIALOGUE_COLOR << dialogue << RESET << "\n" << std::endl;
    stream.close();

    while (true)
    {
        //need to skip the first line, already showed it above
        stream.open(fileName);
        getline(stream, dialogue);

        //menu for asking about other crewmembers
        while (input < 1 || input > ALL_CREW)
        {
            for (int i = 0; i < (ALL_CREW - 1); i++)
            {
                std::cout << i + 1 << ". Ask about " << otherCrew[i] << "\n";
            }

            std::cout << ALL_CREW << ". Return" << std::endl;

            input = getInteger();
        }

        if (input == ALL_CREW)
        {
            //on the menu, 1 more than all other crew will be the cancel option
            return;
        }

        //get and then overwrite any lines between greeting and user's choice
        //repeats until desired option
        for (int i = 0; i < input; i++)
        {
            getline(stream, dialogue);
        }

        std::cout << std::endl;
        printString(dialogue, DIALOGUE_COLOR, 0);
        wait(MED);

        //reset for next loop
        input = 0;
        stream.close();
    }
}
