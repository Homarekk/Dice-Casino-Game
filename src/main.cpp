#include <iostream>
#include "../include/AccountManager.h"
#include "../include/Utils.h"
#include "../include/Game.h"

/*
The Player class contains a std::vector<Transaction> and uses Transaction functions, so we don't have to include it
The Game class contains a Dice object and Game.h already includes Dice.h
*/

int main() {
    AccountManager manager;
    Game game;

    while (true) {
        Utils::clearScreen();
        std::cout << "\n=== DICE CASINO ===\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Exit\n";

        int choice = Utils::getValidInt("Enter choice: ", 1, 3);
        if (choice == 3) break;

        if (choice == 1) manager.registerAccount();
        else if (choice == 2) manager.login();

        Player *player = manager.getCurrentPlayer();    // pointer to the current player
        if (!player) continue;

        // Game loop for logged in user
        while (true) {
            std::cout << "\nWelcome " << player->getName() << "! Balance: $" << player->getBalance() << "\n";
            std::cout << "1. Play\n2. Deposit\n3. Withdraw\n4. History\n5. Logout\n";
            int option = Utils::getValidInt("Choose option: ", 1, 5);

            if (option == 1) {
                if (player->getBalance() < 1) {
                    std::cout << "Too low balance to place bet\n";
                    continue;
                }
                double bet = Utils::getPositiveDouble("Enter your bet: ");
                if (bet < 1) {
                    std::cout << "Minimum bet amount is $1\n";
                    continue;
                }
                int winRange = Utils::getValidInt("Enter winning range (1-99): ", 1, 99);

                game.playRound(*player, bet, winRange);
            }
            else if (option == 2) {
                double amount = Utils::getPositiveDouble("Enter amount to deposit: ");
                player->deposit(amount);
            }
            else if (option == 3) {
                double amount = Utils::getPositiveDouble("Enter amount to withdraw: ");
                player->withdraw(amount);
            }
            else if (option == 4) {
                player->showHistory();
            }
            else if (option == 5) {
                manager.logout();
                break;
            }

            manager.saveToFile();
        }
    }

    return 0;
}
