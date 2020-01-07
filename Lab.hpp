/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data and methods for the Bridge of the ship.
derived from Space class.
specialized functions allow producing the neutralization compound 
------------------------------------------------------------------------------*/

#ifndef LAB_HPP
#define LAB_HPP

#include "Space.hpp"

class Lab: public Space
{

public:
    Lab();
    ~Lab();
    bool actionMenu(Player&);
    void takeItem(Player&, int);
    void makeCompound(Player&);
};

#endif
