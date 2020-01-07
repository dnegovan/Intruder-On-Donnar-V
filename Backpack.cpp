/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: contains the data members and methods for the player's pack
------------------------------------------------------------------------------*/

#include "Backpack.hpp"
#include "dansLibrary.hpp"

#include <iostream>
#include <algorithm>


/*-----------------------------------------------------------------------------
print pack's contents
------------------------------------------------------------------------------*/
void Backpack::printContents()
{
    std::cout << NARRATOR_COLOR;
    if (contents.empty())
    {
        std::cout << "\nYour pack is empty." << RESET << std::endl;
    }
    else
    {
        //cast from unsigned int to avoid compiler warnings
        int size = static_cast<int>(contents.size());

        std::cout << "\nYour pack contains: \n" << ITEM_COLOR;
        for (int i = 0; i < size; i++)
        {
            std::cout << contents[i] << "\n";
        }
        std::cout << RESET << std::endl;
    }
}


/*-----------------------------------------------------------------------------
menu for discarding things in your pack
only allows removal if item isn't important to the game
------------------------------------------------------------------------------*/
void Backpack::discardMenu()
{
    while (true)
    {
        //cast from unsigned int to avoid compiler warnings
        int size = static_cast<int>(contents.size());

        int input = 0;
        while (input < 1 || input > (size + 2))
        {
            std::cout << RESET << std::endl;
            for (int i = 0; i < size; i++)
            {
                //count menu numbers from 1 not 0
                std::cout << i+1 << ". Discard " << contents[i] << "\n";
            }
            std::cout << size + 1 << ". Show neutralization formula"
                      << std::endl
                      << size + 2 << ". Go back" << std::endl;
            input = getInteger();
        }


        if (input == size + 2)
        {
            //they chose cancel
            return;
        }

        if (input == size + 1)
        {
            displayFormula();
        }
        else
        {
            //save string to be deleted
            std::string toDelete = contents[input - 1];
            //store iterator of its location in pack
            auto iterator = contents.begin() + input - 1;

            //erase their selection if it's not important to the game
            if (std::find(importantItems.begin(), importantItems.end(),
                           toDelete) != importantItems.end())
            {
                std::cout << NARRATOR_COLOR << "\nYou might need that."
                          << std::endl;
            }
            else
            {
                contents.erase(iterator);
                std::cout << NARRATOR_COLOR << "\n"
                          << toDelete << " has been discarded.\n" << RESET;
            }
        }
    }
}


/*-----------------------------------------------------------------------------
main pack menu (Open Pack).  displays contents then gives options
------------------------------------------------------------------------------*/
void Backpack::menu()
{
    if (contents.empty())
    {
        printContents();
        //no need for options if pack is empty
        return;
    }

    int input = 0;

    while (true)
    {
        printContents();
        std::cout << "1. Discard Items...\n"
                  << "2. Show neutralization formula\n"
                  << "3. Return" << std::endl;

        input = getInteger();

        if (input == 3)
        {
            return;
        }

        if (input == 2)
        {
            displayFormula();
            wait(SHORT);
        }

        if (input == 1)
        {
            discardMenu();
            return;
        }

        input = 0;
    }





}


/*-----------------------------------------------------------------------------
returns true if pack is full
------------------------------------------------------------------------------*/
bool Backpack::isFull()
{
    if (contents.size() == PACK_MAX)
    {
        return true;
    }
    else
    {
        return false;
    }
}


/*-----------------------------------------------------------------------------
returns size of pack
------------------------------------------------------------------------------*/
int Backpack::getSize()
{
    return contents.size();
}


/*-----------------------------------------------------------------------------
adds provided string to pack.  will execute even if pack is full so need to
check with isFull() before calling this function
------------------------------------------------------------------------------*/
void Backpack::addItem(std::string item)
{
    contents.push_back(item);
}

/*-----------------------------------------------------------------------------
returns true if pack contains provided string argument
------------------------------------------------------------------------------*/
bool Backpack::checkFor(std::string item)
{
    if (std::find(contents.begin(), contents.end(), item) != contents.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}


/*-----------------------------------------------------------------------------
removes item from pack, make sure it's in there and that it's not important
to the game before calling this
------------------------------------------------------------------------------*/
void Backpack::removeItem(std::string item)
{
    auto iterator = std::find(contents.begin(), contents.end(), item);
    contents.erase(iterator);
}

/*-----------------------------------------------------------------------------
displays the Neutralization Formula to the screen
------------------------------------------------------------------------------*/
void Backpack::displayFormula()
{
    std::cout << PROLOGUE_COLOR
              << "\nNEUTRALIZATION FORMULA"
              << "\n-quadriprohyl alcohol"
              << "\n-ecitobeniphal"
              << "\n-black iron oxide"
              << "\n-tricarbonated liquid"
              << "\n-injection device\n" << RESET << std::endl;
}
