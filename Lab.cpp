/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data and methods for the Medical Lab of the ship.
derived from Space class.
specialized functions allow producing the neutralization compound
------------------------------------------------------------------------------*/

#include "Lab.hpp"

/*-----------------------------------------------------------------------------
constructor
------------------------------------------------------------------------------*/
Lab::Lab()
{
    //set up room
    this->roomName = "Medical Lab";
    occupant = nullptr;

    roomItems.push_back("erlenmeyer flask");
    roomItems.push_back("jar of gray matter");
    roomItems.push_back(labIngredient);
}

/*-----------------------------------------------------------------------------
virtual destructor
------------------------------------------------------------------------------*/
Lab::~Lab()
{
}

/*-----------------------------------------------------------------------------
gives option to make compound when entering the room if the player has
all ingredients, then calls base actionMenu
------------------------------------------------------------------------------*/
bool Lab::actionMenu(Player& markNelson)
{

    //if player has all ingredients, give option to make compound
    if (markNelson.ingredientsFound == TOTAL_INGREDIENTS)
    {
        char answer = getYesNo("Create Neutralization Compound? [y/n]: ");
        if (answer == 'Y')
        {
            makeCompound(markNelson);
            //reset this so this option isn't triggered next time you enter
            //the room
            markNelson.ingredientsFound = 0;
        }
    }
    //then call regular menu
    return Space::actionMenu(markNelson);

}

/*-----------------------------------------------------------------------------
moves items from room to pack items based on user input, passed as a parameter
------------------------------------------------------------------------------*/
void Lab::takeItem(Player& markNelson, int input)
{
    if (markNelson.pack.isFull())
    {
        std::cout << RED
                  << "\nYour pack is full. Discard items you don't need."
                  << RESET << std::endl;
        //won't be able to take anything else, exit search menu
        return;
    }
    else
    {
        std::cout << NARRATOR_COLOR << "\n" << roomItems[input-1]
                  << " added to pack." << RESET << std::endl;
        //add item to pack
        markNelson.pack.addItem(roomItems[input-1]);

        //update ingredient counter if necessary
        checkForIngredient(markNelson, roomItems[input-1]);

        //remove item from room
        auto iterator = roomItems.begin() + input - 1;
        roomItems.erase(iterator);

        //if player has all ingredients, give option to make compound
        if (markNelson.ingredientsFound == TOTAL_INGREDIENTS)
        {
            char answer = getYesNo("Create Neutralization Compound? [y/n]: ");
            if (answer == 'Y')
            {
                makeCompound(markNelson);
                //reset this so this option isn't triggered next time you enter
                //the room
                markNelson.ingredientsFound = 0;
            }
        }
    }
}


/*-----------------------------------------------------------------------------
removes ingredients from pack, adds compound to pack 
------------------------------------------------------------------------------*/
void Lab::makeCompound(Player& markNelson)
{
    markNelson.pack.removeItem(labIngredient);
    markNelson.pack.removeItem(loungeIngredient);
    markNelson.pack.removeItem(captainsQIngredient);
    markNelson.pack.removeItem(crewQIngredient);
    markNelson.pack.removeItem(engineeringIngredient);

    std::cout << NARRATOR_COLOR
              << "\ncompound ingredients removed from pack.\n"
              << compound << " added to pack.\n" << std::endl;

    markNelson.pack.addItem(compound);

}
