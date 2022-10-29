#pragma once

#include <iostream>
#include <random>

class RandomNumberGenerator
{
	private:
        // https://learn.microsoft.com/en-us/events/goingnative-2013/rand-considered-harmful
        // Non-deterministic 32-bit seed
        std::random_device rd;
		uint_fast32_t randState{ rd() };

	public:
        uint_fast32_t getRandom32BitNumber(void)
        {
            // https://en.wikipedia.org/wiki/Xorshift

            uint_fast32_t number = randState;

            // XOR shift algorithm
            number ^= number << 13;
            number ^= number >> 17;
            number ^= number << 5;

            // Update random number state
            randState = number;

            return number;
        }

        uint_fast64_t getRandom64BitNumber(void)
        {
            // https://www.chessprogramming.org/Looking_for_Magics

            // Init 4 random 32-bit numbers, removing 16 bits from MS1B side
            uint_fast64_t n1 = (uint_fast64_t)(getRandom32BitNumber()) & 0xFFFF;
            uint_fast64_t n2 = (uint_fast64_t)(getRandom32BitNumber()) & 0xFFFF;
            uint_fast64_t n3 = (uint_fast64_t)(getRandom32BitNumber()) & 0xFFFF;
            uint_fast64_t n4 = (uint_fast64_t)(getRandom32BitNumber()) & 0xFFFF;

            // Combine the 4 16-bit random numbers into a 64-bit result
            return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
        }
};
