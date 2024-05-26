#pragma once

#include <cstdlib>

// Insert Standard rant about cstdint not defining floating point versions 
// meaning I either have to choose between the non unified naming scheme or 
// adding the cruft at the top of my apps
typedef float fint32_t;
typedef double fint64_t;

//inital value given to users to play with
const fint32_t INITAL_BALANCE = 500;
//the scale factor that we are rewarding the users with if they are correct.
const fint32_t REWARD_SCALER = 2;
//the number of dice we are using for each game
static const int NUNBER_OF_DICE = 2;
//the number of sides we are using for the game
static const int NUMBER_OF_SIDED = 6;


/**
 * @brief Wrapper function for getting and upating the buffer
 * 
 * @param change 
 * @return fint32_t 
 */
fint32_t balance(fint32_t change = 0);

/**
 * @brief roll a dice of given sides and return the results
 * 
 * @param sides 
 * @return int32_t 
 */
int32_t roll(int32_t sides = NUMBER_OF_SIDED);
