#pragma once
#include <string>

namespace Utils {
    std::string getTrimmedInput(const std::string &prompt);
    double getValidDouble(const std::string &prompt);   // check if double is Valid
    int getValidInt(const std::string &prompt, int min, int max);   // check if int is valid
    std::string getStrongPassword(const std::string &prompt);   // get strong password
    bool isAlphabetic(std::string &s);  // check if all chars in string are alphabetic
    void clearScreen(); // artificially clear screen
    std::string getValidNick(const std::string &prompt);    // get valid nickname
    std::string getValidEmail(const std::string &prompt);   // get Valid Email
    double getPositiveDouble(const std::string &prompt);    // get positive value
    static bool hasSpaces(const std::string &s);
}

