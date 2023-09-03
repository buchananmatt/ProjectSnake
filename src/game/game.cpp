// 
// GAME.HPP [PROJECT SNAKE]
// C++ VERSION GNU++14
// macOS 11.7.9
// DUAL-CORE INTEL CORE i5 @ 2.8 GHZ
//
// GITHUB REPOSITORY https://github.com/buchananmatt/ProjectSnake.git
//
// COPYRIGHT [2023] [MATTHEW T. BUCHANAN] [BOCAN SOFTWARE]
//
// LICENSED UNDER THE APACHE LICENSE, VERSION 2.0 (THE "LICENSE");
// YOU MAY NOT USE THIS FILE EXCEPT IN COMPLIANCE WITH THE LICENSE.
// YOU MAY OBTAIN A COPY OF THE LICENSE AT 
//
// http://www.apacher.org/licenses.LICENSE-2.0
//
// UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING, SOFTWARE
// DISTRIBUTED UNDER THE LICENSE IS DISTRIBUTED ON AN "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
// SEE THE LICENSE FOR THE SPECIFIC LANGUAGE GOVERNING PERMISSIONS AND
// LIMITATIONS UNDER THE LICENSE.

#include <fstream>
#include <thread>
#include <chrono>

#include "../game/game.hpp"
#include "../printer/printer.hpp"

using bocan::snake::Game;
using bocan::snake::Printer;

Game::Game() {

    Printer p = Printer();
    printer = &p;

}

Game::~Game() {

    printer->~Printer();

}

void Game::Start() {

    points = 0;

    printer->StartGame();
    printer->RefreshScreen();
    printer->GetUserInput();

}

void Game::GameLoop() {

    do {
        // delay program to establish frame rate
        std::this_thread::sleep_for(std::chrono::milliseconds(frame_rate));

        // get user input
        printer->GetUserInput();

        // update snake positions
        MoveSnake();

        // check if snake collided with food
        if(FoodCollision) {
            GenerateFood();
            IncreaseSnakeSize();
            points += 10;
            printer->RefreshPoints();
        }

        // refresh the game space window
        printer->RefreshGameSpace();

        // check if snake collided with wall or snake
    }   while(!CollisionDetect());
}

void Game::EndGame() {

    printer->EndGame();
    printer->RefreshScreen();
    printer->GetUserInput();

}
