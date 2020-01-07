/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data and methods for the Engineering room.
derived from Space class.
special actionMenu allows use of escape pod 
------------------------------------------------------------------------------*/

#include "Engineering.hpp"

/*-----------------------------------------------------------------------------
constructor
------------------------------------------------------------------------------*/
Engineering::Engineering()
{
    //set up room
    this->roomName = "Engineering";
    occupant = new Lester;

    roomItems.push_back(engineeringIngredient);
    roomItems.push_back("wrench");
    roomItems.push_back("tikurian generator");
}

/*-----------------------------------------------------------------------------
virtual destructor
------------------------------------------------------------------------------*/
Engineering::~Engineering()
{
    delete occupant;
}

/*-----------------------------------------------------------------------------
allows for escape pod option if you have the codes
------------------------------------------------------------------------------*/
bool Engineering::actionMenu(Player& markNelson)
{
    if (markNelson.pack.checkFor(codes))
    {
        std::cout << NARRATOR_COLOR
                  << "As you enter Engineering, you notice the escape pod. "
                     " You have the \ncodes, and it is out of Lester's field of"
                     " view.  It only fits one \nperson."
                  << RESET << std:: endl;

        int choice = 0;
        while (choice < 1 || choice > 2)
        {
            std::cout << "1. Take escape pod\n"
                      << "2. Stay aboard the ship" << std::endl;

            choice = getInteger();
        }

        //game Over if you take pod
        if (choice == 1)
        {
            if (markNelson.crewDead == 0)
            {
                markNelson.state = TOOK_POD_NONE_DEAD;
                return false;
            }
            else
            {
                markNelson.state = TOOK_POD_SOME_DEAD;
                return false;
            }
        }
    }

    return Space::actionMenu(markNelson);
}
