// 
// GAME.HPP [PROJECT SNAKE]
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

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <array>

namespace bocan {

namespace snake {

class Printer;

class Game {
public:
    Game();
    ~Game();

    void Start();
    void GameLoop();
    bool EndGame();

private:

    friend class Printer;

    Printer* printer;

    /// @brief Data structure to represent the snake.
    /// Snake is a vector of arrays. 
    /// Each array represents a snake segment's position on the screen.
    /// std::array<int,2> = {y_position, x_position}
    ///
    std::vector<std::array<int, 2>> m_snake;

    const std::vector<std::array<int, 2>>& GetSnake() { return m_snake; };

    std::array<int, 2> m_food;

    const std::array<int, 2>& GetFood() { return m_food; };

    const int k_frame_rate = 10;
    const int k_game_space_w = 115;
    const int k_game_space_h = 42;

    int m_points;
    int m_high_score;
    int m_snake_dir;

    bool m_quit_flag;

private:
    void GenerateSnake();
    void GenerateFood();
    void MoveSnake();
    bool FoodCollision();
    void IncreaseSnakeSize();
    bool CollisionDetect();
};

} // NAMESPACE SNAKE

} // NAMESPACE BOCAN

#endif // GAME_HPP