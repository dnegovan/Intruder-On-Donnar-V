/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data members and methods for the abstract Space class.  The
derived rooms will make up the ship/map in which the game takes place and the
player moves through
------------------------------------------------------------------------------*/

#ifndef SPACE_HPP
#define SPACE_HPP

#include "Player.hpp"
#include "CrewMember.hpp"
#include "dansLibrary.hpp"
#include "formatting.hpp"
#include "items.hpp"

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

const int START_COUNT = 1;

class Space
{
protected:
    CrewMember* occupant;
    std::string roomName;
    std::vector <std::string> roomItems;

public:
    Space* up;
    Space* down;
    Space* left;
    Space* right;

    Space();
    virtual ~Space() = 0;
    std::string getRoomName();
    CrewMember* getOccupant();
    virtual bool actionMenu(Player&);
    virtual void searchRoom(Player&);
    virtual void takeItem(Player&, int);
    void checkForIngredient(Player&, std::string);
    virtual bool killOccupant(Player&);
    virtual bool administerCompound(Player&);
};

#endif
