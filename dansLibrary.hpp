/*------------------------------------------------------------------------------
-- Program name: CS162
-- Author: Daniel Negovan
-- Date: Winter 2019
-- Description: These are helper functions for validation, formatting etc, that
I plan to use throughout the course.
------------------------------------------------------------------------------*/

#ifndef DANS_LIBRARY_HPP
#define DANS_LIBRARY_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <sstream>
#include "formatting.hpp"


//wait times for wait function
const double SHORT = 1;
const double MED = 2;
const double LONG = 2.5;


std::string getLetters();
char getYesNo(std::string);

int getInteger();
int getInteger(std::string);
double getDouble();

int getIntWithinRange(std::string, int, int);
double getDoubleWithinRange(std::string, double, double);
double getMoneyWithinRange(std::string, double, double);

void promptOpenRead(std::ifstream&);
void promptOpenWrite(std::ofstream&);

std::string makeTwoDecimals(double);
std::string addCommas (int);

void printFile(std::string, std::string, double);
void printString(std::string, std::string, double);
void wait(double);

#endif
