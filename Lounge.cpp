/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data and methods for the Lounge of the ship.
derived from Space class.
------------------------------------------------------------------------------*/

#include "Lounge.hpp"

/*-----------------------------------------------------------------------------
constructor
------------------------------------------------------------------------------*/
Lounge::Lounge()
{
    //set up room
    this->roomName = "Lounge";
    occupant = new Penny;

    roomItems.push_back("water bottle");
    roomItems.push_back("nutrition bar");
    roomItems.push_back(loungeIngredient);
}

/*-----------------------------------------------------------------------------
virtual destructor
------------------------------------------------------------------------------*/
Lounge::~Lounge()
{
    delete occupant;
}
