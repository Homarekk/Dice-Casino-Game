#pragma once
#include <string>

class Transaction {
    std::string type;       // type of transaction (deposit/withdraw)
    double amount;          // amount to withdraw
    std::string timestamp;  // timestamp to get time when transaction happened

public:
    Transaction(std::string type, double amount);   // Constructor taking these arguments

    // Returns formatted string describing the transaction
    std::string toString() const;

    // Getters
    double getAmount() const { return amount; }
    const std::string &getType() const { return type; }
    const std::string &getTimestamp() const { return timestamp; }
};
