
// STD Libs Headers
#include <cstddef>
#include <iostream>
#include <string>
#include <cstdint>
#include <ctime>

#include "Casino.h"
#include "games/BlackJack.h"

/** Enum to represent the games that can be played */
enum Games {
    GuessTheNumber = 1,
    GuessIsOdd = 2,
    BlackJack = 3,
    Exit = 4,
};

/**
 * @brief Helper Function for propmting the user of the avalible options
 * 
 */
inline void help() {
    
    std::cout << "Avaliable Games: \n\t" <<
                    Games::GuessTheNumber << ") Guess the number.\n\t"    <<
                    Games::GuessIsOdd     << ") Guess Odds or evens.\n\t" <<
                    Games::BlackJack      << ") BlackJack\n\t" <<
                    Games::Exit           << ") Exit\n\n";
    std::cout.flush();
}

/**
 * @brief Helper function for introducing the user to the applicaiton.
 * 
 */
inline void intro_message() {
    
    std::cout << "Hello, welcome to the Second Assigment! \n\n";
    help();
}

/**
 * @brief Basic Casino 
 *
 * @details 
 *   Below are the requirements for this particular app
 *   1. Terminal app
 *   2. Welcome message
 *   3. Requires Rules to be given before each game 
 *   4. Requires a main menu
 *   5. 2 simple games 
 *       5.1: Guess a even or odd (roll 2d6 guess if both are even or odd)
 *       5.2: Guess a number (ask for a number roll 2d6 check if they got it correct)
 *   6. Money system allowed to bet before each game
 *       6.1: when money hits 0 exit
 *       6.2: keep player in the loop      
*/
int main() {

    //! Warning NOT TRUE Randomness as time can be controlled by external switch
    //! to third party RNG before shipping
    srand(time(NULL));

    intro_message();

    bool shutting_down = false;
    
    do {
        std::string user_choice = prompt("Please Select a game");

        int32_t selection = atoi(user_choice.c_str());

        switch (selection) {

            case Games::GuessIsOdd:     guess_is_odd();       break;
            case Games::GuessTheNumber: guess_the_number();   break;
            case Games::BlackJack: {
                struct BlackJack game;
                game.play();
                break;
            } 
            case Games::Exit:           shutting_down = true; break;
            default:                    help();               break;
        }

        if (!shutting_down) shutting_down = balance() <= 0;
        
    } while(!shutting_down);

}
