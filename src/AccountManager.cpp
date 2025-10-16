#include "../include/AccountManager.h"
#include "../include/Utils.h"
#include "../include/Account.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor loads data from file
AccountManager::AccountManager() {
    loadFromFile();
}

// Check if email already exists
bool AccountManager::emailExists(const std::string &email) const {
    for (const auto &p : players) {
        if (p.getEmail() == email) return true;
    }
    return false;
}

// Check if nickname already exists
bool AccountManager::nicknameExists(const std::string &nickname) const {
    for (const auto &p : players) {
        if (p.getName() == nickname) return true;
    }
    return false;
}

// Registration
void AccountManager::registerAccount() {
    std::string nickname;
    while (true) {
        nickname = Utils::getValidNick("Enter nickname: ");
        if (nicknameExists(nickname)) {
            std::cout << "Nickname already taken\n";
            continue;
        }
        break;
    }

    std::string email;
    while (true) {
        email = Utils::getValidEmail("Enter email: ");
        if (emailExists(email)) {
            std::cout << "Email already registered\n";
            continue;
        }
        break;
    }

    std::string password = Utils::getStrongPassword("Enter password: ");

    Account acc(email, password, nickname); // create account
    Player player(acc, 1000.0);             // create player
    players.push_back(player);              // Add player to all registered players

    currentPlayer = &players.back();        // set newly registered user as active
    saveToFile();
    std::cout << "Account created successfully\n";
}


// login
void AccountManager::login() {
    std::string email = Utils::getTrimmedInput("Enter your email: ");
    std::string password = Utils::getTrimmedInput("Enter your password: ");

    for (auto &p : players) {
        Account &acc = p.getAccount();  // reference to actual stored account

        if (acc.getEmail() == email && acc.verifyPassword(password)) {
            currentPlayer = &p; // pointer to the logged-in player
            std::cout << "Login successful! Welcome back, " << acc.getName() << "\n";
            return;
        }
    }

    std::cout << "Invalid email or password\n";
}

// logout
void AccountManager::logout() {
    currentPlayer = nullptr;
    std::cout << "Logged out successfully\n";
}

// Save all account to file
void AccountManager::saveToFile() {
    std::ofstream file("accounts.txt");
    if (!file) {
        std::cerr << "Error: could not open accounts.txt for writing\n";
        return;
    }
    for (const auto &p : players) {
        const Account &acc = p.getAccount();    // access player's Account
        file << acc.getName() << ", "
        << acc.getEmail() << ", "
        << acc.getPasswordHash() << ", "
        << p.getBalance() << "\n";
    }
}

// Load accounts from file
void AccountManager::loadFromFile() {
    std::ifstream file("accounts.txt");
    if (!file) {
        std::cerr << "Error: could not open accounts.txt for reading\n";
        return;
    }
    std::string line;   // Each line presumably represents one player with their details
    while (std::getline(file, line)) {  // reads one line at a time from the file
        std::stringstream ss(line); // Creates a std::stringstream from the line, which allows you to extract individual parts like a stream
        std::string name, email, passHash;  // hashed password (stored, not plain password)
        double balance;
        char comma; // used to skip the commas in CSV format
        ss >> name >> comma >> email >> comma >> passHash >> comma >> balance;
        Account acc(email, passHash, name);
        players.emplace_back(acc, balance); // emplace_back() constructs the Player directly in the vector without extra copying
    }
}

// Get current player
Player *AccountManager::getCurrentPlayer() {
    return currentPlayer;
}







