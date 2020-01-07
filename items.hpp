/*------------------------------------------------------------------------------
-- Program name: Intruder on Donnar V
-- Author: Daniel Negovan
-- Date: 3/19/2019
-- Description: This header file contains static strings and data that different
classes will need to reference during gameplay
------------------------------------------------------------------------------*/

#ifndef ITEMS_HPP
#define ITEMS_HPP

const int TOTAL_INGREDIENTS = 5;

const std::string labIngredient = "injection device";
const std::string loungeIngredient = "tricarbonated liquid";
const std::string captainsQIngredient = "painkillers (ecitobeniphal)";
const std::string crewQIngredient = "quadriprophyl alcohol";
const std::string engineeringIngredient = "black iron oxide";
const std::string gun = "handgun";
const std::string codes = "escape pod codes";
const std::string keyCard = "captain's key card";
const std::string compound = "Neutralization Compound";

static const std::vector <std::string> importantItems =
                                        {labIngredient, loungeIngredient,
                                        captainsQIngredient, crewQIngredient,
                                        engineeringIngredient, gun, codes,
                                        keyCard, compound};

static const std::vector <std::string> ingredientList =
                                        {labIngredient, loungeIngredient,
                                        captainsQIngredient, crewQIngredient,
                                        engineeringIngredient};


static const std::vector <std::string> crewList = {"Harper", "Holly", "Penny",
                                      "Nate", "Lester"};

const int ALL_CREW = 5;   //doesn't include you, the player

#endif
