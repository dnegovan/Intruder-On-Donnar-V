/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data members and methods for the Harper class
derived from CrewMember
------------------------------------------------------------------------------*/

#include "Harper.hpp"

/*-----------------------------------------------------------------------------
constructor, define in derived classes
------------------------------------------------------------------------------*/
Harper::Harper() : CrewMember()
{
    name = "Harper";
    fullTitle = "Harper Galveston - Pilot/Navigation";
    infected = false;
}

/*-----------------------------------------------------------------------------
virtual destructor
------------------------------------------------------------------------------*/
Harper::~Harper()
{
}
