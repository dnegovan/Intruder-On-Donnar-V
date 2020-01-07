/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data and methods for the Captains Quarters of the ship.
derived from Space class.
------------------------------------------------------------------------------*/

#ifndef CAPTAINS_QUARTERS_HPP
#define CAPTAINS_QUARTERS_HPP

#include "Space.hpp"
#include "Holly.hpp"

class CaptainsQuarters: public Space
{

public:
    CaptainsQuarters();
    ~CaptainsQuarters();
    bool administerCompound(Player&);
};

#endif
