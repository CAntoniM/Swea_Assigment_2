#include "games/BlackJack.h"
#include "utils/commondef.h"
#include "utils/UserInterface.h"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <sys/types.h>

Suite suite(Card card) {
    return (Suite)(card & SUITE_MASK);
}

std::string toString(Suite suite) {
    switch (suite) {
    case Hearts:
        return "Hearts";
    case Diamonds:
        return "Diamonds";
    case Clubs:
        return "Clubs";
    case Spades:
        return "Spades";
      break;
    }
}

Rank rank(Card card){
    return (Rank)(card & RANK_MASK);
}

std::string toString(Rank rank) {
    switch (rank) {

    case Ace:
        return "Ace";
    case Two:
        return "Two";
    case Three:
        return "Three";
    case Four:
        return "Four";
    case Five:
        return "five";
    case Six:
        return "six";
    case Seven:
        return "seven";
    case Eight:
        return "Eight";
    case Nine:
        return "Nine";
    case Ten:
        return "Ten";
    case Jack:
        return "Jack";
    case Queen:
        return "Queen";
    case King:
        return "King";
    case Joker:
        return "Joker";
      break;
    }
}


CardError error(Card card) {
    return (CardError)(card & ERROR_MASK);
}

Deck::Deck(){
    for (Card card = 0; card < size ; card++) this->cards[card] = card;
}

Card Deck::draw() {
    if (size <= 0) return CardError::OUT_OF_BOUNDS;
    size --;
    return cards[size];
}

Card Deck::play(Card card) {    
    if (size > NUMBER_OF_CARDS) return card + CardError::OUT_OF_BOUNDS;
    cards[size] = card;
    size++;
    return card;
}

void Deck::shuffle(){   

    for(Card card = 0; card < size ; card++) {
        Card first = roll(size);
        Card second = roll(size);
        
        //In place swap
        cards[second] += cards[first];
        cards[first] = cards[second] - cards[first];
        cards[second] -= cards[first];
    }

}

Hand::Hand(std::string n) : name(n) {
    
}

std::size_t Hand::value() const {
    uint8_t aces = 0;
    uint8_t value = 0;
    for(uint8_t pos = 0; pos < size ; pos++ ) {
        Rank card_rank = rank(cards[pos]);
        switch (card_rank) {
        case Ace:
            aces ++;
            value += 10;
        case Two:
        case Three:
        case Four:
        case Five:
        case Six:
        case Seven:
        case Eight:
        case Nine:
            value += card_rank & RANK_MASK;
            break;
        case Ten:
        case Jack:
        case Queen:
        case King:
            value += 10;
        default:
          break;
        }

        //Correct for aces double values
        if (value > BlackJack::MAX_HAND_VAL && aces > 0 ) {
            aces--;
            value -= 10;
        }
    }

    return value;
}

void Hand::draw(Deck& deck) {
    cards[size] = deck.draw();
    size++;
    std::cout << name 
              << " Drew a "
              << cards[size-1] 
              << " | Current total :"
              << value() 
              << std::endl; 

}

Card Hand::play() {
    size --;
    return cards[size];
}

void deal(Hand &player, Deck& deck, uint8_t ammount = BlackJack::INITIAL_HAND_SIZE ) {
    for(uint8_t i = 0 ; i < ammount; i++) player.draw(deck);
}

enum MoveSelection {
    Hit = 1,
    Stay = 2,
    Fold = 3
};

BlackJack::BlackJack(): player("You"), dealer("The Dealer") {
}

void BlackJack::play() {

    fint32_t bet = get_bet();

    deck.shuffle();

    deal(player,deck);
    deal(dealer,deck);

    if(player.value() >= BlackJack::MAX_HAND_VAL) {
        stay(bet);
        return;
    }

    while (true) {

        do {
            std::cout << "Your moves:\n\t" << 
                MoveSelection::Hit << ") Hit\n\t" <<
                MoveSelection::Stay << ") Stay\n\t" <<
                MoveSelection::Fold << ") Fold\n\n";
            std::cout.flush();
            
            std::string selection = prompt("Choose your move");

            bool valid_guess = false;

            switch (atoi(selection.c_str())) {
                case MoveSelection::Hit:
                    if (hit(bet)) return ;
                    valid_guess = true;
                    break;
                case MoveSelection::Stay:
                    stay(bet);
                    return;
                case MoveSelection::Fold:
                    fold(bet);
                    return;
                default:
                    std::cerr << "ERROR: invalid selection \n\n";
                    std::cerr.flush();
                    valid_guess = false;
                    break;
            }
        } while(true);

    }
}


bool BlackJack::hit(fint32_t bet) {
    player.draw(deck);

    if (player.value() >= MAX_HAND_VAL) {
        stay(bet);
        return true;
    }

    return false;
}

void BlackJack::stay(fint32_t bet) {

    auto win = [](fint32_t bet) {  
        std::cout << "You Won Blackjack !! \n\n";
        std::cout.flush();
        
        bet *= REWARD_SCALER;
        balance(bet);
    };

    auto lose = [](fint32_t bet) {
        std::cout << "You Lost BlackJack :( \n\n";
        std::cout.flush();

        bet*= -1;
        balance(bet);
    };

    while(dealer < player && dealer.value() < MAX_HAND_VAL && dealer.value() != MAX_HAND_VAL) {
        dealer.draw(deck);        
    }
    // Draw
    if (dealer == player) {
        return;
    }

    int8_t dealer_distance = MAX_HAND_VAL - dealer.value();
    int8_t player_distance = MAX_HAND_VAL - player.value();

    //Player win due to dealer being out of bounds
    if (dealer_distance < 0 && player_distance >= 0) {  
        win(bet);
        return;
    } else if (dealer_distance >= 0 &&  player_distance < 0) {
        lose(bet);
        return;
    }

    //as either both have gone over or both have not gone over check if we have 
    //and invert the difference as to make the rest simpler
    if (dealer_distance < 0 ) {
        dealer_distance *= -1;
        player_distance *= -1;
    }

    if (dealer_distance < player_distance) {
        lose(bet);
        return;
    } else {
        win(bet);
        return;
    }
}

void BlackJack::fold(fint32_t bet ) {
    std::cout << "You folded :(" << std::endl;
    bet *= -1;
    balance(bet);
}
