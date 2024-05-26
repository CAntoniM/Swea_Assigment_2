#pragma once
#include "utils/commondef.h"
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

/**
 * @brief Card Object 
 * 
 * 8 Bits allocated for this usage shown below big endianie used
 *
 * First 2 bytes define suite e.g. 11000000 is the mask
 * Bytes 3,4,5,6 define the rank of the card e.g. 00111100 is the mask
 * Bytes 7 and 8 define error states. 
 * 
 */
typedef uint8_t Card;

/**
 * @brief Enum to make it easier to work with the suit rather than having to bit
 *        Mask everything
 * 
 */
enum Suite {
    Hearts = 0,
    Diamonds = 1,
    Clubs = 2,
    Spades = 3,
};

static const uint8_t NUMBER_OF_SUITES = Suite::Spades + 1;
// Binary 11000000 to mask out the the rank from the number
static const uint8_t SUITE_MASK = 3;

// returns the suite of a given card
Suite suite(Card card);

std::string toString(Suite suite);

inline bool operator==(const Suite& suit, const Card& card){
    return (card & SUITE_MASK) == suit;
}

/**
 * @brief Enum to give 
 * 
 */
enum Rank {
    Ace = 0,
    Two = 4,
    Three = 8,
    Four = 12,
    Five = 16,
    Six = 20,
    Seven = 24,
    Eight = 28,
    Nine = 32,
    Ten = 36,
    Jack = 40,
    Queen = 44,
    King = 48,
    Joker = 52,
};

static const uint8_t RANK_OFFSET=2;
// the joker is defined as the last rank and the rank starts from the 4th least 
// significant bit and counts so this should allways calculate the number of ranks
static const uint8_t NUMBER_OF_RANKS = (Rank::Joker >> RANK_OFFSET) + 1 ;
// Binary 0011 1100 to mask our the 
static const uint8_t RANK_MASK = 60;

// Returns the rank of a given card
Rank rank(Card card);

std::string toString(Rank rank);

/**
 * @brief Checks the rank of the card against a rank
 * 
 * @param rank 
 * @param card 
 * @return true 
 * @return false 
 */
inline bool operator==(const Rank& rank, const Card& card) {
    return (card & RANK_MASK) == rank;
}

inline std::ostream& operator<< (std::ostream &out, Rank rank) {
    out << toString(rank);
    return out;
}

inline std::ostream& operator<< (std::ostream &out, Suite suite) {
    out << toString(suite);
    return out;
}

inline std::ostream& operator<< (std::ostream &out, Card card) {
    out << rank(card) << " of " << suite(card);
    return out;
}

enum CardError {
  NO_ERROR = 0, //00
  OUT_OF_BOUNDS = 64, //10
  CHECK_ERRNO = 192 //11 We have a problem but errno has more info
};

static const uint8_t ERROR_OFFSET = RANK_OFFSET + 4;
static const uint8_t ERROR_MASK = CardError::CHECK_ERRNO;
static const uint8_t NUMBER_OF_ERRORS = (CardError::CHECK_ERRNO >> ERROR_OFFSET) + 1;

CardError error(Card card);
inline bool hasError(Card card) { return card >= OUT_OF_BOUNDS; }

/**
 * @brief Structure containing a List of cards in a desk of playing cards
 * 
 */
struct Deck {
    //As all cards are mapped on a contigus range we can simple get the last card + 1;
    static const uint8_t NUMBER_OF_CARDS = Rank::King + Suite::Spades + 1;
    std::size_t size = NUMBER_OF_CARDS;
    Card cards[NUMBER_OF_CARDS];

    /**
     * @brief Construct a new Deck object
     * 
     */
    Deck();
    /**
     * @brief Draws a card from the top of the deck
     * 
     * @return Card 
     */
    Card draw();
    /**
     * @brief Plays a card from the hand to the deck
     * 
     * @param card 
     */
    Card play(Card card);
    /**
     * @brief reorder all of the cards in the deck
     * 
     */
    void shuffle();
};

/**
 * @brief Structure containing a list of cards in a hand of playing cards
 * 
 */
struct Hand {
    //Hand size = 4 Aces + 4 twos + 3 threes
    static const uint8_t MAX_HAND_SIZE = 11;
    uint8_t size = 0;
    Card cards[MAX_HAND_SIZE];
    std::string name;

    /**
     * @brief Construct a new Hand object
     * 
     */
    Hand(std::string name);

    /**
     * @brief get the value of the hand in black jack
     * 
     * @return std::size_t 
     */
    std::size_t value() const ;
    
    /**
     * @brief Draw a card from the deck to this hand
     * 
     * @param deck 
     */
    void draw(Deck& deck);

    /**
     * @brief Play a card from the hand to the deck;
     * 
     * @return Card 
     */
    Card play();

    inline bool operator== (const Hand &hand) {
        return value() == hand.value();
    }

    inline bool operator!= (const Hand &hand) {
        return !(*this == hand);
    }

    inline bool operator< (const Hand &hand) {
        return value() < hand.value();
    }

    inline bool operator> (const Hand &hand) {
        return  hand.value() < value();
    }

    inline bool operator<= (const Hand &hand) {
        return !(value() > hand.value());
    }

    inline bool operator>= (const Hand &hand) {
        return  value() < hand.value();
    }
};

struct BlackJack {
    Deck deck;
    Hand dealer;
    Hand player;

    static const uint8_t MAX_HAND_VAL=21;
    static const uint8_t INITIAL_HAND_SIZE = 2;

    BlackJack();

    /**
     * @brief Plays a new game of blackjack
     * 
     */
    void play();

    /**
     * @brief check if a player has won the game processes the winning if they
     have
     * 
     * @param bet 
     * @return true 
     * @return false 
     */
    bool game_over(fint32_t bet);

    /**
     * @brief the player draws a card and then if they are over the max then we will stay
     * 
     */
    void hit(fint32_t bet);

    /**
     * @brief The player will not draw anymore cards and the dealer will then 
     *        draw until they are either closer or over the max
     * 
     */
    void stay(fint32_t bet);

    /**
     * @brief The player will discard their hand and loose the game.
     * 
     */
    void fold(fint32_t bet);


};
