// 
// GAME.CPP [PROJECT SNAKE]
// C++ VERSION GNU++14
// macOS 11.7.10
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

#include <thread>
#include <chrono>

#include <cstdlib>
#include <ctime>

#include "../game/game.hpp"
#include "../printer/printer.hpp"

using bocan::snake::Game;
using bocan::snake::Printer;

///
/// @brief: constructor for the Game class object.
/// @param: none.
/// @return: Game object instance. only one instance is initialized in the main function.
/// @todo: none.
///
Game::Game() {

    std::srand(std::time(NULL));

    m_quit_flag = false;

    printer = new Printer();
    printer->SetupScreen();
}

///
/// @brief: destructor for the Game class object.
/// @param: none.
/// @return: none.
/// @todo: none.
///
Game::~Game() {

    printer->EndScreen();
    delete printer;

}

///
/// @brief: sets the current score to zero and calls the printer->StartGame() function to print the start menu and receive user input.
/// @param: none.
/// @return: none.
/// @todo: none.
///
void Game::Start() {

    m_score = 0;

    bool input = printer->StartGame();

    if(!input)
        m_quit_flag = true;

}

///
/// @brief: main game loop. refreshes at a set constant frame rate to move the snake, generate food and snake positions, and refresh the screen.
/// @param: none.
/// @return: none.
/// @todo: none.
///
void Game::GameLoop() {

    if(m_quit_flag) return;

    GenerateSnake();
    GenerateFood();
    printer->RefreshScreen(m_score);
    printer->RefreshGameSpace(m_snake, m_food);

    int direction;

    do {
        // delay program to establish frame rate
        std::this_thread::sleep_for(std::chrono::milliseconds(k_frame_rate));

        // get user input to change snake direction, quit or pause the game
        direction = printer->GetDirection();

        // check if user paused the game
        if(direction == PAUSE) {
            printer->Pause();

        // check if user quit the game
        } else if(direction == QUIT) {
            m_quit_flag = true;
            break;
        
        // if no user input, continue movement in current direction
        } else if(direction == ERROR) {
            MoveSnake();

        // throw away input if move command is in opposite direction
        } else if(direction == DIRECTION_UP && m_snake_direction == DIRECTION_DOWN) {
            MoveSnake();
        } else if(direction == DIRECTION_DOWN && m_snake_direction == DIRECTION_UP) {
            MoveSnake();
        } else if(direction == DIRECTION_LEFT && m_snake_direction == DIRECTION_RIGHT) {
            MoveSnake();
        } else if (direction == DIRECTION_RIGHT && m_snake_direction == DIRECTION_LEFT) {
            MoveSnake();
        }
        // update snake positions
        else {
            m_snake_direction = direction;
            MoveSnake();   
        }


        // check if snake collided with food
        if(FoodCollision()) {
            
            GenerateFood();
            IncreaseSnakeSize();
            m_score += 10; 
        }

        // refresh the game space window
        printer->RefreshScreen(m_score);
        printer->RefreshGameSpace(m_snake, m_food);

        // check if snake collided with wall or snake or if user quit the game
    }   while(!CollisionDetect());
}

///
/// @brief: check if user quit the game. calls printer->EndGame() to print the end game menu and receive user input.
/// @param: none.
/// @return: boolean true if user quit the game, boolean false to return to the start menu.
/// @todo: none.
///
bool Game::EndGame() {

    if(m_quit_flag) {
        
        printer->Exit();
        return true;
    }
    
    int input = printer->EndGame(m_score);
    
    if(input) 
        printer->Exit();

    return input;
}

///
/// @brief: generates the snake for the beginning of the game in the middle of the game space window.
/// @param: none.
/// @return: none.
/// @todo: link game space constants in Game to the window constants in Printer.
///
void Game::GenerateSnake() {
    
    // clear the snake from the previous game
    m_snake.clear();

    // generate snake segment in the middle of the game space
    m_snake.push_back( {{k_game_space_h / 2, k_game_space_w / 2}} );

    // generate random starting direction of the snake
    m_snake_direction = ( rand() % 4 ) + 3;
}

///
/// @brief: generates the food at a random location within the game space
/// @param: none.
/// @return: none.
/// @todo: none.
///
void Game::GenerateFood() {

    // generate random location of the food
    m_food = {rand() % (k_game_space_h-1), rand() % (k_game_space_w-1)};
    
    // generate food within game boundary
    if(m_food.at(0) == 0) m_food.at(0)++;
    if(m_food.at(1) == 0) m_food.at(1)++;
}

///
/// @brief: moves the snake in the current snake direction by popping segment of the end and pushing back at the beginning.
/// @param: none.
/// @return: none.
/// @todo: fix bug which causes segments to "leak" on the game space during portions of game play.
///
void Game::MoveSnake() {

    // generate a new snake segment at the front of the snake
    std::array<int, 2> new_segment = m_snake.front();

    // move the new snake segment toward the current snake direction
    switch(m_snake_direction) {
        case DIRECTION_UP:
            new_segment.at(0) -= 1;
            break;
        case DIRECTION_DOWN:
            new_segment.at(0) += 1;
            break;
        case DIRECTION_LEFT:
            new_segment.at(1) -= 1;
            break;
        case DIRECTION_RIGHT:
            new_segment.at(1) += 1;
            break;
        default:
            break;
    }

    // add the new snake segment to the snake and delete the last snake segment
    m_snake.push_front(new_segment);
    m_snake.pop_back();

}

///
/// @brief: checks if the front of the snake has collided with the food
/// @param: none.
/// @return: boolean true if the front of the snake and the food share the same position, false if they do not
/// @todo: none.
///
bool Game::FoodCollision() {

    if(m_snake.front() == m_food) 
        return true;
    else 
        return false;
}

///
/// @brief: increases the size of the snake by one segment.
/// @param: none.
/// @return: none.
/// @todo: none.
///
void Game::IncreaseSnakeSize() {

    std::array<int, 2> new_last_segment;

    // check if snake has only one segment to avoid comparing last two segments
    if(m_snake.size() == 1) {

        // set new last segment opposite to the current snake direction
        new_last_segment = m_snake.front();
        switch(m_snake_direction) {
            case DIRECTION_UP:
                new_last_segment.at(0) += 1;
                break;
            case DIRECTION_DOWN:
                new_last_segment.at(0) -= 1;
                break;
            case DIRECTION_LEFT:
                new_last_segment.at(1) += 1;
                break;
            case DIRECTION_RIGHT:
                new_last_segment.at(1) -= 1;
                break;
            default:

                break;
        }
        m_snake.push_back(new_last_segment);
        return;
    }

    std::array<int, 2> current_last_segment = m_snake.back();
    m_snake.pop_back();


    // compare x values of last two segments
    if(current_last_segment.at(0) == m_snake.back().at(0)) {

        // snake is moving left, add new segment right of current last segment
        if(current_last_segment.at(1) > m_snake.back().at(1))

            new_last_segment = {current_last_segment.at(0), current_last_segment.at(1) + 1};
        // snake is moving right, add new segment left of current last segment
        else 

            new_last_segment = {current_last_segment.at(0), current_last_segment.at(1) - 1};

    // compare y values of last two segments
    } else if (current_last_segment.at(1) == m_snake.back().at(1)) {

        // snake is moving up, add new segment down from current last segment
        if(current_last_segment.at(0) > m_snake.back().at(0))

            new_last_segment = {current_last_segment.at(0) + 1, current_last_segment.at(1)};

        // snake is moving down, add new segment up from current last segment
        else

            new_last_segment = {current_last_segment.at(0) - 1, current_last_segment.at(1)};
    }

    m_snake.push_back(current_last_segment);
    m_snake.push_back(new_last_segment);
}

///
/// @brief: checks for a collision between the snake and the game space boundary or between different snake segments.
/// @param: none.
/// @return: boolean true if a collision is detected, false if no collision is detected.
/// @todo: none.
///
bool Game::CollisionDetect() {

    // check for collision between snake and boundary

    // check vertical boundary
    if(m_snake.front().at(0) == 0 || m_snake.front().at(0) == k_game_space_h-1)
        return true;
    // check horizontal boundary
    if(m_snake.front().at(1) == 0 || m_snake.front().at(1) == k_game_space_w-1)
        return true;

    // check for collision between snake front and other snake segments

    // temporarily remove first segment
    std::array<int, 2> first_segment = m_snake.front();
    m_snake.pop_front();

    // compare position of first segment with other segments
    for(auto itr = m_snake.rbegin(); itr != m_snake.rend(); itr++) {
        if(first_segment == *itr) {
            m_snake.push_front(first_segment);
            return true;
        }
    }
    
    // collision not detected
    m_snake.push_front(first_segment);
    return false;
}
