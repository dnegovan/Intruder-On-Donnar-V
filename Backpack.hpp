/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: contains the data members and methods for the player's pack
------------------------------------------------------------------------------*/

#ifndef BACKPACK_HPP
#define BACKPACK_HPP

#include <string>
#include <vector>
#include "items.hpp"


const unsigned int PACK_MAX = 10;

class Backpack
{
private:
    std::vector <std::string> contents;
    void printContents();
    void discardMenu();

public:
    void menu();
    bool isFull();
    int getSize();
    void addItem(std::string);
    bool checkFor(std::string);
    void removeItem(std::string);
    void displayFormula();

};

#endif
