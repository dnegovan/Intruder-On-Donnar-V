/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: data and methods for the CrewMember abstract class.
Derived crew have different data member values but all use these methods
------------------------------------------------------------------------------*/

#ifndef CREW_MEMBER_HPP
#define CREW_MEMBER_HPP

#include <string>
#include <vector>
#include "items.hpp"
#include "dansLibrary.hpp"

class CrewMember
{
protected:
    std::string name;
    std::string fullTitle;
    bool alive;
    bool infected;
    std::vector <std::string> otherCrew;


public:
    CrewMember();
    virtual ~CrewMember() = 0;

    std::string getName();
    void setAlive(bool);
    bool getAlive();
    void setInfected(bool);
    bool getInfected();

    void talk();
};

#endif
