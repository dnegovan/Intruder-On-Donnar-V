/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data and methods for the Bridge of the ship.
derived from Space class.
special searchRoom function allows searching captain's locker 
------------------------------------------------------------------------------*/

#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include "Space.hpp"
#include "Harper.hpp"

class Bridge: public Space
{

public:
    Bridge();
    ~Bridge();
    void searchRoom(Player&);
};

#endif
