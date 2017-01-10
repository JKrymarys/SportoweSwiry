cmake_minimum_required(VERSION 2.6)
project(battleships)
set(battleships_sources
        include/GAME.H src/Game.cpp
        include/GRID.H src/Grid.cpp
        include/PLAYER.H src/Player.cpp
        include/SHIP.H src/Ship.cpp
        include/ComputerStrategies.h src/ComputerStrategies.cpp
        include/TextUI.h src/TextUI.cpp
        src/main.cpp)
add_executable(battleships ${battleships_sources})
target_include_directories(battleships PUBLIC include)
