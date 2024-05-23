
#include <string>
#include <iostream>
#include "commondef.h"

/**
 * @brief Helper function for displaying the standard user prompt
 * 
 * @param message 
 * @return std::string 
 */
std::string prompt( std::string msg);

/**
 * @brief Helper function that check if the bet that is placed is valid
 * 
 * @param bet 
 * @return true 
 * @return false if either the bet < 0 or bet > balance  
 */
bool valid_bet(fint32_t bet);

/**
 * @breif Prompts the user for a bet and validates the outupt
 * @return bet
*/
fint32_t get_bet();
