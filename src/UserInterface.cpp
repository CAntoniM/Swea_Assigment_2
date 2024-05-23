
#include <UserInterface.h>

std::string prompt( std::string msg) {
    
    std::string buffer;
    
    std::cout << "Balance $" << balance() << " | "<< msg << " > ";
    std::cout.flush();
    
    std::getline(std::cin,buffer);

    std::cout << std::endl;
    
    return buffer;
}

bool valid_bet(fint32_t bet) {
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
fint32_t get_bet() {
    fint32_t bet = -1;
    
    do {
        std::string user_input = prompt("Please enter your bet");
        bet = atof(user_input.c_str());
    } while (!valid_bet(bet));

    return bet;
}
