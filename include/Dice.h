#pragma once
#include <random>

class Dice {
    std::mt19937 rng;   // Mersenne Twister engine and its object rng
    std::uniform_int_distribution<int> dist;    // defines range of numbers (1-99)

public:
    Dice();     // constructor - to seed the RNG
    int roll(); // generates one random number, cannot be const since calling it modifies rng
};
