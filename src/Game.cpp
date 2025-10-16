#include "../include/Game.h"
#include <iomanip>
#include <iostream>

// Function to play round
bool Game::playRound(Player &player, double betAmount, int winRange) {
    if (betAmount > player.getBalance()) {  // bet amount can't be greater than player balance
        std::cout << "Not enough balance!\n";
        return false;
    } else if (betAmount < 1) {
        std::cout << "Too low bet amount. Minimum $1 is required\n";
        return false;
    }

    // Withdraw the stake immediately and log the bet
    bool withdrawn = player.withdraw(betAmount);
    if (!withdrawn) {
        std::cout << "Failed to place bet (withdrawal failed)\n";
        return false;
    }
    player.addTransaction("bet", betAmount);

    int roll = dice.roll(); // roll dice
    std::cout << "Dice rolled: " << roll << "\n";

    bool won = (roll <= winRange);
    double multiplier = 99.0 / static_cast<double>(winRange);
    if (won) {
        double payout = betAmount * multiplier; // full payout (stake + profit)
        player.deposit(payout); // give payout back
        player.addTransaction("win", payout);   // log thr winning payout
        std::cout << "You won " << std::fixed << std::setprecision(4) << payout << "!\n";
        return true;
    } else {
        // We already withdrew the stake, but we can log a loss record for clarity
        player.addTransaction("loss", betAmount);
        std::cout << "You lost!\n";
        return false;
    }
}
