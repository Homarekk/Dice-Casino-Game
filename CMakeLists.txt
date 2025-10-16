cmake_minimum_required(VERSION 4.0)
project(Dice_Game)

set(CMAKE_CXX_STANDARD 20)

add_executable(Dice_Game src/main.cpp
        include/Game.h
        include/Dice.h
        include/Utils.h
        include/Transaction.h
        include/Player.h
        src/Game.cpp
        src/Dice.cpp
        src/Utils.cpp
        src/Transaction.cpp
        src/Player.cpp
        include/Account.h
        src/Account.cpp
        include/AccountManager.h
        src/AccountManager.cpp)
