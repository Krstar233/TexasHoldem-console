cmake_minimum_required(VERSION 3.26)
project(TexasHoldem_console_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TexasHoldem_console_main
        Banker.cpp
        Banker.h
        Desk.cpp
        Desk.h
        main.cpp
        Player.cpp
        Player.h
        Poker.cpp
        Poker.h
        PokerHeap.cpp
        PokerHeap.h
        TexasHoldemGame.cpp
        TexasHoldemGame.h)
