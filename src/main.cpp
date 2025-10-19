#include <iostream>
#include <thread>
#include <chrono>
#include "../include/AccountManager.h"
#include "../include/Utils.h"
#include "../include/Game.h"
#include <conio.h>  // for _kbhit() and _getch()


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
            std::cout << "1. Play\n2. Deposit\n3. Withdraw\n4. History\n5. Auto Play\n6. Exit\n";
            int option = Utils::getValidInt("Choose option: ", 1, 6);

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
                if (player->getBalance() < 1) {
                    std::cout << "Too low balance to place bet\n";
                    continue;
                }

                double bet = Utils::getValidDouble("Enter your bet for auto mode: ");
                if (bet < 1) {
                    std::cout << "Minimum bet amount is $1\n";
                    continue;
                }

                int winRange = Utils::getValidInt("Enter winning range (1-99): ", 1, 99);

                std::cout << "\nAuto mode started. Press ANY key to stop\n";
                while (true) {
                    if (_kbhit()) { // user pressed a key
                        std::cout << "Auto mode stopped\n";
                        break;
                    }

                    if (player->getBalance() < bet) {
                        std::cout << "Not enough balance\n";
                        break;
                    }

                    game.playRound(*player, bet, winRange);
                    std::cout << "Current Balance: $" << player->getBalance() << "\n\n";
                    manager.saveToFile();

                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
            }
            else if (option == 6) {
                manager.logout();
                break;
            }

            manager.saveToFile();
        }
    }

    return 0;
}
