#pragma once
#include <string>
#include <vector>
#include "Account.h"
#include "Transaction.h"

class Player {  // class for Player
    Account account;    // Player owns an Account
    double balance;
    std::vector<Transaction> history;

public:
    Player(Account account, double startingBalance = 0);

    // Getters
    const std::string &getName() const { return account.getName(); }
    double getBalance() const { return balance; }
    const std::string &getEmail() const { return account.getEmail(); }
    const Account &getAccount() const { return account; }   // read-only version for const Player objects
    Account &getAccount() { return account; }   // modifiable version for normal ones

    // Game money functions
    void deposit(double amount);    // function to deposit
    bool withdraw(double amount);   // function to withdraw
    void addTransaction(const std::string &type, double amount);    // This function adds a new record (a Transaction) to the player’s history vector whenever something happens — like a deposit, withdrawal, or bet
    void showHistory() const;   // function to show transaction history
};
