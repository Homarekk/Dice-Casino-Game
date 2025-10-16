#include "../include/Player.h"
#include <iostream>
#include <utility>

// Player constructor
Player::Player(Account account, double startingBalance)
    : account(std::move(account)), balance(startingBalance) {}
// Take the local parameter account (a copy passed into the constructor) and move its contents into the account member variable of this class


// Deposit function
void Player::deposit(double amount) {
    if (amount < 0) {   // amount to deposit cant be negative
        std::cout << "Deposit must be positive.\n";
        return; // quit earlier
    }
    balance += amount;  // add amount to balance
}

// Withdraw function
bool Player::withdraw(double amount) {
    if (amount <= 0 || amount > balance) {  // amount to withdraw cant be negative and greater than balance
        std::cout << "Invalid withdraw amount\n";
        return false;   // marks that the withdrawal failed
    }
    balance -= amount;  // subtract amount from balance
    return true;    // marks that withdrawal was successful
}

// Add a transaction record
void Player::addTransaction(const std::string &type, double amount) {
    history.emplace_back(type, amount);
}
/*
emplace_back() is a method of std::vector that constructs a new element directly inside the vector’s memor
push_back() would create temporary Transaction object and then copies or moves it into the vector
emplace_back() directly constructs the Transaction in place, avoiding an extra copy/move (faster and cleaner, especially for objects with constructors)
vector.emplace_back(arg1, arg2, ...) - calls the constructor of the vector’s element type (Transaction(arg1, arg2, ...)) inside the vector
*/

// Show transaction history
void Player::showHistory() const {
    std::cout << "Transaction history for " << account.getName() << ":\n";
    for (const auto &t : history) { // Iterates over every element (Transaction) in the history vector
        std::cout << t.toString() << "\n";  // toString() is a member function of the Transaction class that returns a formatted string describing the transaction
    }
}



