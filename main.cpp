/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: main creates the game object and sets up the loop allowing
multiple playthroughs.  calls the startMenu to get user preference for
type of intro/ if they want to quit
------------------------------------------------------------------------------*/

#include "Game.hpp"

int main()
{
    int start = 1;
    bool firstGame = true;

    while (start == 1 || start == 2)
    {
        //create game
        Game donnarV;
        if (firstGame)
        {
            start = donnarV.startMenu();
            if (start == 3)
            {
                return 0;
            }
        }

        //play the game
        donnarV.play(start);

        //play again?
        firstGame = false;
        start = donnarV.startMenu();
    }

    return 0;
}
