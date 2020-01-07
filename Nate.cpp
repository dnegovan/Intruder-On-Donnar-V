/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data members and methods for the Nate class
derived from CrewMember
------------------------------------------------------------------------------*/

#include "Nate.hpp"

/*-----------------------------------------------------------------------------
constructor, define in derived classes
------------------------------------------------------------------------------*/
Nate::Nate() : CrewMember()
{
    name = "Nate";
    fullTitle = "Nate Rogers - Systems Technician";
    infected = false;
}

/*-----------------------------------------------------------------------------
virtual destructor
------------------------------------------------------------------------------*/
Nate::~Nate()
{
}
