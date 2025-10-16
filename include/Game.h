#pragma once
#include "Dice.h"
#include "Player.h"

/*
Game is responsible for running rounds, taking bets, and calculating winnings
Dice handles randomness, Game handles money and logic
*/
class Game {
    Dice dice;  // Game uses dice to generate rolls

public:
    Game() = default;
    bool playRound(Player &player, double betAmount, int winRange);
};
