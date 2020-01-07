/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data and methods for the corridor of the ship.
derived from Space class.
------------------------------------------------------------------------------*/

#include "Corridor.hpp"

/*-----------------------------------------------------------------------------
constructor
------------------------------------------------------------------------------*/
Corridor::Corridor()
{
    //set up room
    this->roomName = "Main Corridor";
    occupant = nullptr;
}

/*-----------------------------------------------------------------------------
virtual destructor
------------------------------------------------------------------------------*/
Corridor::~Corridor()
{
}
