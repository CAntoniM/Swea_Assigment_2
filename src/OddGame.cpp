
#include "OddGame.h"

std::string toString(Oddness val) {
    switch (val)
    {
    case Oddness::ODD:
        return "Odd";
    case Oddness::EVEN:
        return "Even";
    default:
        return "Unknown";
    }
};

inline  Oddness flip (Oddness val) {
    return val == Oddness::EVEN ? Oddness::ODD : Oddness::EVEN;
}

int32_t is_odd(int32_t val) {
    return (val & 1 ) == 0 ? Oddness::EVEN : Oddness::ODD ;
}

void guess_is_odd() {
    
    fint32_t bet = get_bet();
    
    Oddness guess;
    bool valid_guess = 0;

    do {
        std::cout << "Please select what you think the dice will be:\n" << 
                        "\t" << Oddness::ODD  << ") odd\n" << 
                        "\t" << Oddness::EVEN << ") even\n\n";
        std::cout.flush();

        std::string user_input = prompt("guess");

        switch (atoi(user_input.c_str())) {
            case Oddness::ODD:
                guess = Oddness::ODD;
                valid_guess = true;
                break;
            case Oddness::EVEN: 
                guess = Oddness::EVEN;
                valid_guess = true;
                break;
            default:
                std::cerr << "ERROR: invalid selction\n\n";
                std::cerr.flush();
                valid_guess = false;
        }

    } while(!valid_guess);

    bool result = true;

    for (int32_t i = 0; i < NUNBER_OF_DICE; i++) { 
        if (is_odd(roll()) != guess) {
            result = false;
            break;
        }
    }

    if (result) {
        bet *= REWARD_SCALER;
        balance(bet);
        
        std::cout << "Congratulations: You have guessed correctly\n\n";
    }else {
        bet *= -1;
        balance(bet);
        
        std::cout << "Sorry: You guessed: " 
                    << toString(guess)
                    << " and rolled: " 
                    << toString(flip(guess)) << "\n\n";
    }

    std::cout.flush();
}

