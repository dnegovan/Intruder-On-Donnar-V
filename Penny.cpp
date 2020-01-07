/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data members and methods for the Penny class
derived from CrewMember
------------------------------------------------------------------------------*/

#include "Penny.hpp"

/*-----------------------------------------------------------------------------
constructor, define in derived classes
------------------------------------------------------------------------------*/
Penny::Penny() : CrewMember()
{
    name = "Penny";
    fullTitle = "Penny Basak - Doctor, Biologist & Head of Research";
    infected = false;
}

/*-----------------------------------------------------------------------------
virtual destructor
------------------------------------------------------------------------------*/
Penny::~Penny()
{
}
