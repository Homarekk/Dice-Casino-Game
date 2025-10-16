#pragma once
#include <string>

class Account {
    std::string email;  // var for email
    std::string passwordHash;   // var for hashed password
    std::string name;   // var for nickname

public:
    Account() = default;    // defaulted constructor
    Account(std::string email, std::string password, std::string name);   // custom constructor
    // Now in main we can call both Account acc; or Account acc("Daniel", *****);

    // Static helpers
    static bool isValidEmail(const std::string &email);
    static std::string hashPassword(const std::string &password);

    // Getters
    const std::string &getEmail() const { return email; }
    const std::string &getName() const { return name; }
    const std::string &getPasswordHash() const { return passwordHash; }   // only used for saving/loading

    // Authentication
    bool verifyPassword(const std::string &password) const;
};
