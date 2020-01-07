/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data and methods for the Crew Quarters.
derived from Space class.
------------------------------------------------------------------------------*/

#include "CrewQuarters.hpp"

/*-----------------------------------------------------------------------------
constructor
------------------------------------------------------------------------------*/
CrewQuarters::CrewQuarters()
{
    //set up room
    this->roomName = "Crew Quarters";
    occupant = new Nate;

    roomItems.push_back("dumbbells");
    roomItems.push_back(crewQIngredient);
    roomItems.push_back("reading glasses");
}

/*-----------------------------------------------------------------------------
virtual destructor
------------------------------------------------------------------------------*/
CrewQuarters::~CrewQuarters()
{
    delete occupant;
}
