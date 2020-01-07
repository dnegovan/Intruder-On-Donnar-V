/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: The Player struct is a container for many of the dynamic elements
that need to be changed by different classes as the game progresses. The
intention being that one Player is created at the start of the game and is then
passed by reference to whatever function is in control of the game at the time
------------------------------------------------------------------------------*/

#include "Player.hpp"

/*-----------------------------------------------------------------------------
constructor
------------------------------------------------------------------------------*/
Player::Player()
{
    state = UNFINISHED;
    incubated = false;
    crewInfected = 1;
    crewDead = 0;
    innocentsShot = 0;
    injectedWrong = false;
    ingredientsFound = 0;
}
