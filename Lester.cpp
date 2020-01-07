/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data members and methods for the Lester class
derived from CrewMember
------------------------------------------------------------------------------*/

#include "Lester.hpp"

/*-----------------------------------------------------------------------------
constructor, define in derived classes
------------------------------------------------------------------------------*/
Lester::Lester() : CrewMember()
{
    name = "Lester";
    fullTitle = "Lester Fryman - Engineer";
    infected = false;
}

/*-----------------------------------------------------------------------------
virtual destructor
------------------------------------------------------------------------------*/
Lester::~Lester()
{
}
