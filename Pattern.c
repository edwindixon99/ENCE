#include "pio.h"
#include "Pattern.h"

//Paper pattern
static const uint8_t Paper[] =
{
    0b1111111,
    0b1000001,
    0b1000001,
    0b1000001,
    0b1111111,
};

//Rock pattern
static const uint8_t Rock[] =
{
    0b0001110,
    0b1110001,
    0b0000001,
    0b1110001,
    0b0001110,
};

//Scissor pattern
static const uint8_t Scissor[] =
{
    0b1000111,
    0b0101010,
    0b0010100,
    0b0101010,
    0b1000111,
};
