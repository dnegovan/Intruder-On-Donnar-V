/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data and methods for the Engineering room.
derived from Space class.
special actionMenu allows use of escape pod 
------------------------------------------------------------------------------*/

#ifndef ENGINEERING_HPP
#define ENGINEERING_HPP

#include "Space.hpp"
#include "Lester.hpp"

class Engineering: public Space
{

public:
    Engineering();
    ~Engineering();
    bool actionMenu(Player&);
};

#endif
