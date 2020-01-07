/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data members and methods for the abstract Space class.  The
derived rooms will make up the ship/map in which the game takes place and the
player moves through
------------------------------------------------------------------------------*/

#include "Space.hpp"

/*-----------------------------------------------------------------------------
constructor
------------------------------------------------------------------------------*/
Space::Space()
{
}

/*-----------------------------------------------------------------------------
virtual destructor
------------------------------------------------------------------------------*/
Space::~Space()
{
}

/*-----------------------------------------------------------------------------
getters and setters
------------------------------------------------------------------------------*/
std::string Space::getRoomName()
{
    return this->roomName;
}

CrewMember* Space::getOccupant()
{
    return this->occupant;
}


/*-----------------------------------------------------------------------------
this is the main menu you'll see when entering each room, the only way
out of it is to leave the room (returns true) or trigger the end of the game
somehow (returns false).  calls other methods based on user choices
------------------------------------------------------------------------------*/
bool Space::actionMenu(Player& markNelson)
{
    int menuNum = START_COUNT;    //running menu number counter
    int input = 0;

    //these will become the menu options we check against
    int talk = 0, search = 0, pack = 0, formula = 0,
        leave = 0, administer = 0, kill = 0;

    std::cout << NARRATOR_COLOR << "Location: " << getRoomName() << RESET;
    while (true)
    {
        while (input < START_COUNT || input > menuNum)
        {
            talk = 0, search = 0, pack = 0, formula = 0, leave = 0,
                      administer = 0, kill = 0;

            std::cout << std::endl;
            menuNum = START_COUNT;

            //check if possible to speak to occupant
            if (occupant)
            {
                if (occupant->getAlive())
                {
                    talk = menuNum;
                    std::cout << menuNum << ". Speak to " << occupant->getName()
                              << std::endl;
                    menuNum++;
                }
            }

            //check if possible to kill occupant
            if (markNelson.pack.checkFor(gun) && occupant)  //false if nullptr
            {
                if (occupant->getAlive())
                {
                    kill = menuNum;
                    std::cout << menuNum
                              << ". Execute " << occupant->getName() << "\n";
                    menuNum++;
                }
            }

            search = menuNum;
            std::cout << menuNum << ". Search room\n";
            menuNum++;
            pack = menuNum;
            std::cout << menuNum << ". Open pack\n";
            menuNum++;
            formula = menuNum;
            std::cout << menuNum << ". Show neutralization formula\n";
            menuNum++;
            leave = menuNum;
            std::cout << menuNum << ". Leave room\n";
            menuNum++;

            //check if it's possible to adminster compound
            if (markNelson.pack.checkFor(compound) && occupant)
            {
                if (occupant->getAlive())
                {
                    administer = menuNum;
                    std::cout << menuNum
                              << ". Administer " << compound << std::endl;
                    menuNum++;
                }
            }

            input = getInteger();
        }

        if (input == talk)
        {
            occupant->talk();
        }
        else if (input == search)
        {
            searchRoom(markNelson);
        }
        else if (input == pack)
        {
            markNelson.pack.menu();
        }
        else if (input == formula)
        {
            markNelson.pack.displayFormula();
        }
        else if (input == leave)
        {
            return true;  //wants to leave, continue game
        }
        else if (input == administer)
        {
            if(!administerCompound(markNelson))
            {
                //breaks out of function & play loop if gameOver
                return false;
            }
        }
        else if (input == kill)
        {
            if(!killOccupant(markNelson))
            {
                //breaks out of function and play loop if gameOver
                return false;
            }
        }

        input = 0;  //reset to access main actionMenu again
    }
}

/*-----------------------------------------------------------------------------
shows the player what is in the room, gives options
------------------------------------------------------------------------------*/
void Space::searchRoom(Player& markNelson)
{
    if (occupant)
    {
        if (!occupant->getAlive())
        {
            std::cout << NARRATOR_COLOR
                      << "\nAs you scan the room, your eyes move quickly past "
                      << occupant->getName() << "'s dead body." << RESET
                      << std::endl;
        }
    }

    while (true)
    {
        //cast from unsigned int to avoid compiler warnings
        int size = static_cast<int>(roomItems.size());

        if (roomItems.empty())
        {
            std::cout << NARRATOR_COLOR << "\nThere's nothing here."
                      << RESET << std::endl;
            return;
        }
        //Show what's in the room
        std::cout << NARRATOR_COLOR << "\nThis room contains: \n" << ITEM_COLOR;
        for (int i = 0; i < size - 1; i++)
        {
            std::cout << roomItems[i] << ", ";
        }
        std::cout << roomItems[size - 1] << ".\n";

        //menu for which item to take, or cancel
        int input = 0;
        while (input < 1 || input > (size + 2))
        {
            std::cout << RESET << "\n";
            for (int i = 0; i < size; i++)
            {
                std::cout << i+1 << ". Take " << roomItems[i] << ".\n";
            }

            //the last two options will always be size +1 and size +2
            std::cout << size + 1 << ". Show neutralization formula\n"
                      << size + 2 << ". Return to previous menu"
                      << std::endl;

            input = getInteger();
        }

        //execute user choice
        if (input >= 1 && input <= size)
        {
            //they want an item in the room
            takeItem(markNelson, input);
        }
        else if (input == (size + 1))
        {
            markNelson.pack.displayFormula();
        }
        else if (input == (size + 2))
        {
            //exit menu
            return;
        }
    }
}

/*-----------------------------------------------------------------------------
moves items from room to pack items based on user input, passed as a parameter
------------------------------------------------------------------------------*/
void Space::takeItem(Player& markNelson, int input)
{
    if (markNelson.pack.isFull())
    {
        std::cout << RED
                  << "\nYour pack is full. Discard items you don't need."
                  << RESET << std::endl;
        //won't be able to take anything else, exit search menu
        return;
    }
    else
    {
        std::cout << NARRATOR_COLOR << "\n" << roomItems[input-1]
                  << " added to pack." << RESET << std::endl;
        //add item to pack
        markNelson.pack.addItem(roomItems[input-1]);

        //update ingredient counter if necessary
        checkForIngredient(markNelson, roomItems[input-1]);

        //remove item from room
        auto iterator = roomItems.begin() + input - 1;
        roomItems.erase(iterator);
    }
}

/*-----------------------------------------------------------------------------
use this when adding an item to pack, it updates the ingredients Found
counter if the item is an ingredient
------------------------------------------------------------------------------*/
void Space::checkForIngredient(Player& markNelson, std::string item)
{
    //update counter if we've found an ingredient
    if (std::find(ingredientList.begin(),
        ingredientList.end(), item)
        != ingredientList.end())
    {
        markNelson.ingredientsFound++;
    }
}

/*-----------------------------------------------------------------------------
kills occupant, should only be an option to call this if the player has the
handgun.  updates the game as necessary
------------------------------------------------------------------------------*/
bool Space::killOccupant(Player& markNelson)
{
    //opportunity to cancel murder
    std::string prompt = "Are you sure you want to kill ";
    prompt += occupant->getName();
    prompt += "? [y/n]:";
    std::cout << RED;
    char answer = getYesNo(prompt);
    std::cout << RESET;
    if (answer == 'N')
    {
        //continue game
        return true;
    }

    //print this person's death text blurb
    std::cout << std::endl;
    std::string fileName = occupant->getName() + "Death.txt";
    printFile(fileName, NARRATOR_COLOR, 0);
    wait(LONG);

    //update game variables
    if (occupant->getInfected())
    {
        //death cures host
        occupant->setInfected(false);
        markNelson.crewInfected--;
        std::cout << NARRATOR_COLOR << "\nYou knew in your gut you had to do it."
                  << std::endl << occupant->getName()
                  << " had definitely been infected with the parasite.\n"
                  << RESET;
    }
    else
    {
        markNelson.innocentsShot++;
        std::cout << NARRATOR_COLOR << "\nYou are filled with doubt. \nThere "
                  << "wasn't really any evidence that "
                  << occupant->getName()
                  << " had been infected.\n"
                  << RESET;
    }

    wait(LONG);

    occupant->setAlive(false);
    markNelson.crewDead++;

    //trigger game endings if this was last infected person
    if (markNelson.crewInfected == 0)
    {
        if (!markNelson.incubated && markNelson.innocentsShot == 0)
        {
            if (!markNelson.injectedWrong)
            {
                markNelson.state = KILLED_WIFE_PRE_INCUBATION;
                return false;
            }
            else
            {
                markNelson.state = KILLED_WIFE_WRONG_INJECTION;
                return false;
            }
        }
        if (markNelson.innocentsShot > 0)  //incubation doesn't matter for these
        {
            if (markNelson.crewDead < ALL_CREW)
            {
                markNelson.state = SHOT_INNOCENT_AND_WIFE;
                return false;
            }
            if (markNelson.crewDead == ALL_CREW)
            {
                markNelson.state = SHOT_ALL_SOME_INNOCENT;;
                return false;
            }
        }

        //only get to here if you didn't kill any innocents
        if (markNelson.incubated)
        {
            if (markNelson.crewDead == 1)
            {
                markNelson.state = KILLED_WIFE_BEFORE_SPREAD;
                return false;
            }
            if (markNelson.crewDead == 2 && markNelson.injectedWrong)
            {
                //this ending is in two places, see above
                markNelson.state = KILLED_WIFE_WRONG_INJECTION;
                return false;
            }
            if (markNelson.crewDead > 1 && markNelson.crewDead < ALL_CREW)
            {
                markNelson.state = INCUBATED_SOME_SURVIVE;
                return false;
            }
        }
    	if (markNelson.crewDead == ALL_CREW) //incubation doesn't matter here
        {
    		markNelson.state = ALL_CREW_DEAD_YOU_SURVIVE;
            return false;
        }

    }
    //if we made it here, keep playing
    return true;
}

/*-----------------------------------------------------------------------------
administers neutralization compound to the occupant.   should only be an
option if the player has the compound.  updates game as necessary
------------------------------------------------------------------------------*/
bool Space::administerCompound(Player& markNelson)
{
    std::cout << NARRATOR_COLOR
              << "Telling " << occupant->getName() << " that it's just a routine "
              "vaccine for something the crew \nmight have been exposed to on the "
              "planet, you inject the \ncompound into the side of ";

    if (occupant->getName().compare("Holly") == 0 ||
        occupant->getName().compare("Penny") == 0)
    {
        std::cout << "her neck.\n";
    }
    else
    {
        std::cout << "his neck.\n";
    }

    wait(MED);
    std::cout << std::endl;
    wait(MED);
    std::cout << std::endl;

    markNelson.pack.removeItem(compound);
    std::cout << RED;
	if (markNelson.incubated && occupant->getInfected())
    {
    	std::cout << occupant->getName() << " is unaffected. The compound is "
                  "useless because the parasite has \nincubated.\nYou'll need to "
                  " kill " << occupant->getName() << " and any other hosts "
                  "to prevent the \nparasite spreading further." << std::endl;
    }
    if (occupant->getInfected() == false)
    {
		markNelson.injectedWrong = true;
		occupant->setAlive(false);
        std::cout << occupant->getName() << " is not infected, and therefore "
                  "dies quickly and horribly before \nyour eyes.  You've wasted "
                  "the compound and must now kill \nany remaining hosts to save "
                  "the rest of the crew." << std::endl;
    }
    std::cout << RESET;

    //base can't trigger game ending, always true
    return true;
}
