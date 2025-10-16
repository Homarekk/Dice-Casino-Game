#include "../include/Account.h"
#include <regex>
#include <functional> // for std::hash

// Account constructor
Account::Account(std::string email, std::string password, std::string name)
    : email(std::move(email)), passwordHash(hashPassword(password)), name(std::move(name)) {}

// Email validation
bool Account::isValidEmail(const std::string &email) {
    // Simple regex pattern — good enough for typical validation
    const std::regex pattern(R"((\w+)(\.|\_)?(\w*)@(\w+)(\.(\w+))+)");
    return std::regex_match(email, pattern);    // Returns true if the entire string matches the pattern
}
/*
(\w+)         part before dot or underscore — e.g., "john"
(\.|\_)?      optionally a dot or underscore — e.g., "john.doe"
(\w*)         zero or more extra word chars — e.g., "doe"
@             literal '@' symbol
(\w+)         domain name — e.g., "gmail"
(\.(\w+))+    one or more ".something" — e.g., ".com" or ".co.uk"
R"( ... )"    Raw string literal (no need for escaping)
*/

std::string Account::hashPassword(const std::string &password) {
    std::hash<std::string> hasher;  // hasher object
    // hasher("MySecret123!") → produces a numeric hash, e.g. 1234567890123456789
    return std::to_string(hasher(password));    // return string version of numeric hash
}
// passwordHash now stores "1234567890123456789"

bool Account::verifyPassword(const std::string &password) const {
    // hashPassword(password) produces same hash number or some different and compares with stored passwordHash
    return hashPassword(password) == passwordHash;  // Returns true -> login succeeds or returns false -> login fails
}
