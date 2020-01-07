/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: The Player struct is a container for many of the dynamic elements
that need to be changed by different classes as the game progresses. The
intention being that one Player is created at the start of the game and is then
passed by reference to whatever function is in control of the game at the time
------------------------------------------------------------------------------*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Backpack.hpp"
#include <vector>

enum gameState {UNFINISHED, TOOK_POD_NONE_DEAD, TOOK_POD_SOME_DEAD,
                KILLED_WIFE_PRE_INCUBATION, KILLED_WIFE_WRONG_INJECTION,
                KILLED_WIFE_BEFORE_SPREAD, SAVED_WIFE, SHOT_ONE_THEN_SAVED_WIFE,
                SHOT_SOME_THEN_SAVED_WIFE, SHOT_ALL_THEN_SAVED_WIFE,
                ALL_CREW_DEAD_YOU_SURVIVE, INCUBATED_SOME_SURVIVE,
                SHOT_INNOCENT_AND_WIFE, SHOT_ALL_SOME_INNOCENT,
                PLAYER_AND_CREW_INFECTED, KILLED_PEOPLE_INFECTED_ANYWAY,
                KILLED_PERSON_INFECTED_ANYWAY};

struct Player
{
    Backpack pack;
    bool injectedWrong;
    int ingredientsFound;
    int crewDead;
    int crewInfected;
    bool incubated;
    int innocentsShot;
    gameState state;

    Player();
};

#endif
