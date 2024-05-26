#pragma once

#include "utils/UserInterface.h"
#include <string>


/** Enum to represent if a value is odd or even */
enum Oddness {
	ODD = 1,
	EVEN = 2
};

/** Helper function to covert a value to the oposit value. */
std::string toString(Oddness val);

/** Helper function to get the oposite of the current value. */
Oddness flip (Oddness val);

/**
 * @brief tests for an odd number by using the LSB
 * 
 * @param val 
 * @return int32_t 
 */
int32_t is_odd(int32_t val);

/**
 * @brief Runs the game where 2d6 are rolled and the user guess if they are odd
 * or even
 * 
 * @return true 
 * @return false 
 */
void guess_is_odd();
