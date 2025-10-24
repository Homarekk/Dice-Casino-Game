#include "../include/Utils.h"
#include "../include/Account.h" // for Account::isValidEmail
#include <iostream>
#include <limits>
#include <cctype>
#include <cstdlib>

std::string Utils::getTrimmedInput(const std::string &prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, input)) exit(0);    // exit if getline fails

        // Trim functions
        input.erase(0, input.find_first_not_of(" \t\r\n"));
        input.erase(input.find_last_not_of(" \t\r\n") + 1);

        // Input can't be empty
        if (input.empty()) {
            std::cout << "Invalid input!\n";
            continue;
        }

        return input;
    }
}

double Utils::getValidDouble(const std::string &prompt) {
    while (true) {
        std::string input = getTrimmedInput(prompt);
        try {
            size_t pos; // pos stores the index at which stol() stopped
            long val = std::stod(input, &pos);  // ✅ use stod instead of stol
            if (pos != input.size()) {  // pos index at which stol() stopped should be the same like input.size
                std::cout << "Invalid input: unexpected characters\n";
                continue;
            }
            return val; // no need to cast
        } catch (...) { // catch(...) handles all error in our case we can have 2 errors, because stol() it throws exceptions like std::invalid_argument and std::out_of_range
            std::cout << "Invalid input\n";
        }
    }
}

int Utils::getValidInt(const std::string &prompt, int minVal, int maxVal) {
    while (true) {
        std::string input = getTrimmedInput(prompt);
        try {
            size_t pos; // pos stores the index at which stol() stopped
            long val = std::stol(input, &pos);  // Get value ("123bab" we get 123 and pos = 3, because it stopped at 'b')
            if (pos != input.size()) {  // pos index at which stol() stopped should be the same like input.size
                std::cout << "Invalid input: unexpected characters\n";
                continue;
            }

            if (val < minVal || val > maxVal) { // val can't be must fall in the range
                std::cout << "Value out of range (" << minVal << "-" << maxVal << ")\n";
                continue;
            }
            return static_cast<int>(val);   // cast to int
        } catch (...) { // catch(...) handles all error in our case we can have 2 errors, because stol() it throws exceptions like std::invalid_argument and std::out_of_range
            std::cout << "Invalid input\n";
        }
    }
}

// Function to check if all chars in string are alphabetic
bool Utils::isAlphabetic(std::string &s) {
    for (unsigned char c : s) { // isalpha() expects unsigned char
        if (!isalpha(c)) return false;
    }
    return true;
}

// Get strong password
std::string Utils::getStrongPassword(const std::string &prompt) {
    while (true) {
        std::string password = getTrimmedInput(prompt);

        if (hasSpaces(password)) {
            std::cout << "Password cannot contain spaces\n";
            continue;
        }

        // Validation flags
        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

        // Check each char
        for (unsigned char c : password) {
            if (std::isupper(c)) hasUpper = true;
            else if (std::islower(c)) hasLower = true;
            else if (std::isdigit(c)) hasDigit = true;
            else if (std::ispunct(c)) hasSpecial = true;
        }

        // Check if everything is okay
        if (password.length() < 8) {
            std::cout << "Password must be at least 8 characters long\n";
        } else if (!hasUpper) {
            std::cout << "Password must include an uppercase letter\n";
        } else if (!hasLower) {
            std::cout << "Password must include an lowercase letter\n";
        } else if (!hasDigit) {
            std::cout << "Password must include a digit\n";
        } else if (!hasSpecial) {
            std::cout << "Password must include a special character\n";
        } else {
            return password;    // Strong password accepted
        }
    }
}

// Function to artificially clear screen
void Utils::clearScreen() {
    for (int i = 0; i < 15; ++i) { std::cout << "\n"; }
}

// Get valid nickname
std::string Utils::getValidNick(const std::string &prompt) {
    while (true) {
        std::string nickname = Utils::getTrimmedInput(prompt);

        if (nickname.length() < 6 && nickname.length > 20) {
            std::cout << "Nickname length must be 6-20 characters long\n";
            continue;
        }

        if (hasSpaces(nickname)) {
            std::cout << "Nickname cannot contain spaces\n";
            continue;
        }

        return nickname;    // valid nickname
    }
}

// Get valid email
std::string Utils::getValidEmail(const std::string &prompt) {
    while (true) {
        std::string email = getTrimmedInput(prompt);

        if (hasSpaces(email)) {
            std::cout << "Email cannot contain spaces\n";
            continue;
        }

        if (!Account::isValidEmail(email)) {
            std::cout << "Invalid email format! Try again.\n";
            continue;
        }

        return email;   // valid email
    }
}

// Get positive value
double Utils::getPositiveDouble(const std::string &prompt) {
    while (true) {
        std::string input = getTrimmedInput(prompt);
        try {
            size_t pos;
            double val = std::stod(input, &pos);  // <-- use stod for doubles
            if (pos != input.size()) {
                std::cout << "Invalid input: unexpected characters\n";
                continue;
            }
            if (val <= 0) {
                std::cout << "Amount must be positive\n";
                continue;
            }
            return val;
        } catch (...) {
            std::cout << "Invalid input\n";
        }
    }
}

// Check for sapces
bool Utils::hasSpaces(const std::string &s) {
    for (char c : s) {
        if (std::isspace(static_cast<unsigned char>(c))) return true;
    }
    return false;
}






