/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data and methods for the Bridge of the ship.
derived from Space class.
special searchRoom function allows searching captain's locker 
------------------------------------------------------------------------------*/

#include "Bridge.hpp"

/*-----------------------------------------------------------------------------
constructor
------------------------------------------------------------------------------*/
Bridge::Bridge()
{
    //set up room
    this->roomName = "Bridge";
    occupant = new Harper;

    roomItems.push_back("handgun");
    roomItems.push_back("escape pod codes");
    roomItems.push_back("photos of you and Holly");
}

/*-----------------------------------------------------------------------------
virtual destructor
------------------------------------------------------------------------------*/
Bridge::~Bridge()
{
    delete occupant;
}

/*-----------------------------------------------------------------------------
searches the room - bridge is special case becasue it has captain's locker
otherwise behaves similarly to base function
------------------------------------------------------------------------------*/
void Bridge::searchRoom(Player& markNelson)
{
    if (!occupant->getAlive())
    {
        std::cout << NARRATOR_COLOR
                  <<  "\nAs you scan the room, your eyes move quickly past "
                  << occupant->getName() << "'s dead body." << std::endl;
    }

    std::cout << NARRATOR_COLOR << "\nThe crew's lockers are located here.\n"
              << RESET;
    int lockerInput = 0;
    while (lockerInput < 1 || lockerInput > 2)
    {
        std::cout << "1. Open Captain's locker\n"
                  << "2. Return" << std::endl;

        lockerInput = getInteger();
    }

    if (lockerInput == 2)
    {
        return;   //exit room search
    }
    else
    {
        if (!markNelson.pack.checkFor(keyCard))
        {
            std::cout << NARRATOR_COLOR << "\nYou need a key card to open it."
                      << RESET << std::endl;
            //exit since user can't open the locker yet
            return;
        }
        else
        {
            std::cout << NARRATOR_COLOR
                      << "\nYou use your key card to open the locker"
                      << std::endl;
        }
    }

    //menu to search locker
    while (true)
    {
        //cast from unsigned int to avoid compiler warnings
        int size = static_cast<int>(roomItems.size());

        if (roomItems.empty())
        {
            std::cout << NARRATOR_COLOR << "\nYour locker is empty."
                      << RESET << std::endl;
            return;
        }
        //Show what's in the locker
        std::cout << NARRATOR_COLOR << "\nThese items are in your locker: \n"
                  << ITEM_COLOR;
        for (int i = 0; i < size - 1; i++)
        {
            std::cout << roomItems[i] << ", ";
        }
        std::cout << roomItems[size - 1] << ".\n";

        //menu for which item to take, or cancel
        int input = 0;
        while (input < 1 || input > (size + 1))
        {
            std::cout << RESET << "\n";
            for (int i = 0; i < size; i++)
            {
                std::cout << i+1 << ". Take " << roomItems[i] << ".\n";
            }
            std::cout << size + 1 << ". Return to previous menu"
                      << std::endl;
            input = getInteger();
        }

        //execute user choice
        if (input >= 1 && input <= size)
        {
            takeItem(markNelson, input);
        }
        else
        {
            std::cout << RESET;
            //exit menu
            return;
        }
    }
}
