#pragma once

#include <commondef.h>
#include <UserInterface.h>

/**
 * @breif checks if the dice are within a valid range for the number of dice
 *        rolled and number of sides on those dice.
 * @param guess
 * @return true if guess meets the user validation
 * @return false if the guess does not meet user validation
*/
inline bool valid_guess(int32_t guess);

/**
 * @brief Runs the game where 2d6 are rolled and summed then if the user
 * 
 * @return true 
 * @return false 
 */
void guess_the_number();
