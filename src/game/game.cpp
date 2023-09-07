// 
// GAME.CPP [PROJECT SNAKE]
// C++ VERSION GNU++14
// macOS 11.7.9
// DUAL-CORE INTEL CORE i5 @ 2.8 GHZ
//
// GITHUB REPOSITORY https://github.com/buchananmatt/ProjectSnake.git
//
// THIS PROJECT IS DOCUMENTED WITH DOXYGEN. SEE DOCUMENTATION AT BELOW SITE.
// https://htmlpreview.github.io/?https://github.com/buchananmatt/ProjectSnake/blob/master/doc/html/index.html
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

#include <cstdlib>
#include <ctime>

#include "../game/game.hpp"
#include "../printer/printer.hpp"

using bocan::snake::Game;
using bocan::snake::Printer;

/// @brief Constructor for the Game class object.
/// 
/// @return Game object instance. Only one instance is initialized in the main function.
///
Game::Game() {

    std::srand(std::time(NULL));

    m_quit_flag = false;

    printer = new Printer();
    printer->SetupScreen();
//    printer->RefreshScreen();
}

/// @brief Destructor for the Game class object.
///
///
///
Game::~Game() {

    printer->EndScreen();
    delete printer;

}

void Game::Start() {

    m_points = 0;

    printer->StartGame();

    int input = printer->GetUserInput();
    if(input == QUIT)
        m_quit_flag = true;

}

void Game::GameLoop() {

    if(m_quit_flag) return;

    GenerateSnake();
    GenerateFood();
    printer->RefreshGameSpace(m_snake, m_food);
//    int i = printer->GetUserInput();

    int dir;

    do {
        // delay program to establish frame rate
        std::this_thread::sleep_for(std::chrono::milliseconds(k_frame_rate));

        // get user input to change snake direction of movement
        if( (dir = printer->GetUserInput()) == ERROR) {
            MoveSnake();
        }

        // update snake positions
        else {
            m_snake_dir = dir;
            MoveSnake();   
        }

/*
        // check if snake collided with food
        if(FoodCollision()) {
            GenerateFood();
            IncreaseSnakeSize();
            m_points += 10; 
            printer->RefreshPoints();
        }
*/
        // refresh the game space window
        printer->RefreshGameSpace(m_snake, m_food);
/*
        // check if snake collided with wall or snake
    }   while(!CollisionDetect());
*/
    } while(1);
}


bool Game::EndGame() {

    if(m_quit_flag) return true;

    printer->EndGame();

    return true;

}

void Game::GenerateSnake() {

    // generate snake segment in the middle of the game space
    m_snake.push_back( {{k_game_space_h / 2, k_game_space_w / 2}} );

    // generate random starting direction of the snake
    m_snake_dir = rand() % 4;
}

void Game::GenerateFood() {

    // generate random location of the food
    m_food = {rand() % k_game_space_h, rand() % k_game_space_w};

}

void Game::MoveSnake() {

    std::array<int, 2> new_seg = m_snake.front();

    switch(m_snake_dir) {
        case DIRECTION_UP:
            new_seg.at(0) -= 1;
            break;
        case DIRECTION_DOWN:
            new_seg.at(0) += 1;
            break;
        case DIRECTION_LEFT:
            new_seg.at(1) -= 1;
            break;
        case DIRECTION_RIGHT:
            new_seg.at(1) += 1;
            break;
        default:
            new_seg.at(1) += 1;
            break;
    }



    m_snake.push_front(new_seg);
    m_snake.pop_back();

}

bool Game::FoodCollision() {

    return 1;
}

void Game::IncreaseSnakeSize() {


}

bool Game::CollisionDetect() {

    return 1;
}