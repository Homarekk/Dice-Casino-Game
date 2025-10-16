#pragma once
#include "Account.h"
#include "Player.h"
#include <vector>
#include <optional>

class AccountManager {
    std::vector<Player> players;    // stores all registered users
    Player *currentPlayer = nullptr;    // pointer to currently logged-in

public:
    AccountManager();

    void registerAccount();
    void login();
    void logout();
    Player *getCurrentPlayer();

    void saveToFile();
    void loadFromFile();

    bool emailExists(const std::string &email) const;
    bool nicknameExists(const std::string &nickname) const;
};
