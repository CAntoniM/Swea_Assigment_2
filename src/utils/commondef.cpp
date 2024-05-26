
#include <utils/commondef.h>

fint32_t balance(fint32_t change) {

    static fint32_t balance = INITAL_BALANCE;
    balance += change;
    return balance;
}

int32_t roll(int32_t sides) { 
    return rand() % sides;
}
