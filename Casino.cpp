
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdint>
#include <ctime>

// Insert Standard rant about cstdint not defining floating point versions 
// meaning I either have to choose between the non unified naming scheme or 
// adding the cruft at the top of my apps
typedef float fint32_t;
typedef double fint64_t;

//inital value given to users to play with
const fint32_t inital_balance = 500;
//the scale factor that we are rewarding the users with if they are correct.
const fint32_t reward_scaler = 2;
//the number of dice we are using for each game
static const int number_of_dice = 2;
//the number of sides we are using for the game
static const int number_of_sides = 6;

enum Games {

    GuessTheNumber = 1,
    GuessIsOdd = 2,
    Exit = 3,
};

/**
 * @brief Wrapper function for getting and upating the buffer
 * 
 * @param change 
 * @return fint32_t 
 */
inline fint32_t balance(fint32_t change = 0) {

    static fint32_t balance = inital_balance;
    balance += change;
    return balance;
}

/**
 * @brief Helper Function for propmting the user of the avalible options
 * 
 */
inline void help() {
    
    std::cout << "Avaliable Games: \n" <<
                    "\t" << Games::GuessTheNumber << ") Guess the number.\n"    <<
                    "\t" << Games::GuessIsOdd     << ") Guess Odds or evens.\n" <<
                    "\t" << Games::Exit           << ") Exit\n\n";
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
 * @brief Helper function for displaying the standard user prompt
 * 
 * @param message 
 * @return std::string 
 */
inline std::string prompt( std::string msg) {
    
    std::string buffer;
    
    std::cout << "Balance $" << balance() << " | "<< msg << " > ";
    std::cout.flush();
    
    std::cin >> buffer;

    std::cout << std::endl;
    
    return buffer;
}

/**
 * @brief Helper function that check if the bet that is placed is valid
 * 
 * @param bet 
 * @return true 
 * @return false if either the bet < 0 or bet > balance  
 */
inline bool valid_bet(fint32_t bet) {
    if (bet < 0) {
        std::cerr << "ERROR: Please enter a balance greater than 0.\n\n";
        std::cerr.flush();

        return false;
    } else if (bet > balance()) {
        std::cerr << "ERROR: You do not have a sufficent balance to place that bet.\n\n";
        std::cerr.flush();
        
        return false;
    }
    return true;
}

/**
 * @breif Prompts the user for a bet and validates the outupt
 * @return bet
*/
inline fint32_t get_bet() {
    fint32_t bet = -1;
    
    do {
        std::string user_input = prompt("Please enter your bet");
        bet = atof(user_input.c_str());
    } while (!valid_bet(bet));

    return bet;
}

/**
 * @breif checks if the dice are within a valid range for the number of dice
 *        rolled and number of sides on those dice.
 * @param guess
 * @return true if guess meets the user validation
 * @return false if the guess does not meet user validation
*/
inline bool valid_guess(int32_t guess) {
    const int32_t lower_bound = number_of_dice;
    const int32_t upper_bound = number_of_sides * number_of_dice;

    if (guess < lower_bound || guess > upper_bound ) {
        std::cerr << "ERROR: Gueses must be in the range : " 
                    << lower_bound << "-" << upper_bound << "\n\n";

        return false;
    }
    return true;
} 

/**
 * @brief roll a dice of given sides and return the results
 * 
 * @param sides 
 * @return int32_t 
 */
inline int32_t roll(int32_t sides = number_of_sides) { 
    return rand() % sides;
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
                    number_of_dice << " and " << number_of_dice * number_of_sides <<
                    ": \n\n";
        std::cout.flush();

        std::string user_input = prompt("guess");
        guess = atoi(user_input.c_str());
    } while(!valid_guess(guess));

    int32_t number = 0;

    for (int32_t i = 0; i < number_of_dice; i++) number += roll();

    if (number == guess) {
        bet *= reward_scaler;
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
/**
 * @brief tests for an odd number by using the LSB
 * 
 * @param val 
 * @return int32_t 
 */
inline int32_t is_odd(int32_t val) {
    return val & 1;
}

/**
 * @brief Runs the game where 2d6 are rolled and the user guess if they are odd
 * or even
 * 
 * @return true 
 * @return false 
 */
void guess_is_odd() {
    
    
    fint32_t bet = get_bet();
    
    int guess = -1;
    bool valid_guess = 0;

    do {
        std::cout << "Please select what you think the dice will be:\n" << 
                        "\t0) even\n" << 
                        "\t1) odd\n\n";
        std::cout.flush();

        std::string user_input = prompt("guess");
        guess = atoi(user_input.c_str());

        switch (guess) {
            case 0:
            case 1: 
                valid_guess = true;
                break;
            default:
                std::cerr << "ERROR: invalid selction\n\n";
                std::cerr.flush();
                valid_guess = false;
        }

    } while(!valid_guess);

    bool result = true;

    for (int32_t i = 0; i < number_of_dice; i++) { 
        if (is_odd(roll()) != guess) {
            result = false;
            break;
        }
    }

    if (result) {
        bet *= reward_scaler;
        balance(bet);
        
        std::cout << "Congratulations: You have guessed correctly\n\n";
    }else {
        bet *= -1;
        balance(bet);

        const std::string selection_names[] = {"even","odd"};
        const int32_t result = (guess == 0) ? 1 : 0;

        std::cout << "Sorry: You guessed: " 
                    << selection_names[guess]
                    << " and rolled: " 
                    << selection_names[result] << "\n\n";
    }

    std::cout.flush();
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
            case Games::Exit:           shutting_down = true; break;
            default:                    help();               break;
        }

        if (!shutting_down) shutting_down = balance() <= 0;
        
    } while(!shutting_down);

}
