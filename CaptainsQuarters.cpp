/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data and methods for the Captains Quarters of the ship.
derived from Space class.
------------------------------------------------------------------------------*/

#include "CaptainsQuarters.hpp"

/*-----------------------------------------------------------------------------
constructor
------------------------------------------------------------------------------*/
CaptainsQuarters::CaptainsQuarters()
{
    //set up room
    this->roomName = "Captain's Quarters";
    occupant = new Holly;

    roomItems.push_back(keyCard);
    roomItems.push_back(captainsQIngredient);
    roomItems.push_back("sour candy ration");
}

/*-----------------------------------------------------------------------------
virtual destructor
------------------------------------------------------------------------------*/
CaptainsQuarters::~CaptainsQuarters()
{
    delete occupant;
}

/*-----------------------------------------------------------------------------
administers compound to wife
calls base then ends game if parasite hasn't incubated
------------------------------------------------------------------------------*/
bool CaptainsQuarters::administerCompound(Player& markNelson)
{
    //call base first
    bool continueGame = Space::administerCompound(markNelson);

    //apply ending if parasite hasn't incubated
    if (!markNelson.incubated)
    {
        if (markNelson.crewDead == 0)
        {
            //best ending, won game
            markNelson.state = SAVED_WIFE;
            return false;
        }
        if (markNelson.crewDead == 1)
        {
            markNelson.state = SHOT_ONE_THEN_SAVED_WIFE;
            return false;
        }
        if (markNelson.crewDead == (ALL_CREW - 1)) //all but wife
        {
            markNelson.state = SHOT_ALL_THEN_SAVED_WIFE;
            return false;
        }
        if (markNelson.crewDead > 1)
        {
            markNelson.state = SHOT_SOME_THEN_SAVED_WIFE;
            return false;
        }
    }
    //if we make it here, continue game
    return continueGame;
}
