
#include "games/NumberGame.h"
#include <iostream>

/**
 * @breif checks if the dice are within a valid range for the number of dice
 *        rolled and number of sides on those dice.
 * @param guess
 * @return true if guess meets the user validation
 * @return false if the guess does not meet user validation
*/
inline bool valid_guess(int32_t guess) {
    const int32_t lower_bound = NUNBER_OF_DICE;
    const int32_t upper_bound = NUMBER_OF_SIDED * NUNBER_OF_DICE;

    if (guess < lower_bound || guess > upper_bound ) {
        std::cerr << "ERROR: Gueses must be in the range : " 
                    << lower_bound << "-" << upper_bound << "\n\n";

        return false;
    }
    return true;
} 

/**
 * @brief Runs the game where 2d6 are rolled and summed then if the user
 * 
 * @return true 
 * @return false 
 */
void guess_the_number() {
    
    fint32_t bet = get_bet();
    
    int32_t guess = -1;

    do {
        std::cout << "Please enter your guess between " << 
                    NUNBER_OF_DICE << " and " << NUNBER_OF_DICE * NUMBER_OF_SIDED <<
                    ": \n\n";
        std::cout.flush();

        std::string user_input = prompt("guess");
        guess = atoi(user_input.c_str());
    } while(!valid_guess(guess));

    int32_t number = 0;

    for (int32_t i = 0; i < NUNBER_OF_DICE; i++) number += roll();

    if (number == guess) {
        bet *= REWARD_SCALER;
        balance(bet);
        
        std::cout << "Congratulations: You have guessed correctly\n\n";
    }else {
        bet *= -1;
        balance(bet);

        std::cout << "Sorry: You guessed: " << guess << " and rolled: " 
                    << number << "\n\n";
    }

    std::cout.flush();
}
