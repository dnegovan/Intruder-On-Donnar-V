/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: The Game class contains the data members and methods that
control the flow of the game.  create a Game object, and call the startMenu
to ask the player how to start the game (see below).  Then call the play method
to trigger the play loop.
------------------------------------------------------------------------------*/

#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Space.hpp"
#include <string>


class Game
{
private:
    Player markNelson;
    int timeLeft;
    int timeTilHint;
    std::string deadline;
    std::string objective1;
    std::string objective2;
    std::string objective3;

    Space* currentSpace;
    Space* bridge;
    Space* lab;
    Space* lounge;
    Space* captainsQ;
    Space* crewQ;
    Space* engineering;
    Space* corridor;


    void printPrologue();
    void printIntro();
    void printTitle();
    bool move();
    bool decrementTime();
    void printTime();
    bool parasiteSpreads();
    void printShip();
    void printEnding();

public:
    Game();
    ~Game();
    void play(int);
    int startMenu();

};


#endif
