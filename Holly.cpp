/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data members and methods for the Holly class
derived from CrewMember
------------------------------------------------------------------------------*/

#include "Holly.hpp"
#include <iostream>

/*-----------------------------------------------------------------------------
constructor, define in derived classes
------------------------------------------------------------------------------*/
Holly::Holly() : CrewMember()
{
    name = "Holly";
    fullTitle = "Holly Nelson - Communications Specialist";
    infected = true;
}

/*-----------------------------------------------------------------------------
virtual destructor
------------------------------------------------------------------------------*/
Holly::~Holly()
{
}
