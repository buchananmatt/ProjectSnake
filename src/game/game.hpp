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
    void EndGame();

private:

    friend class Printer;

    Printer* printer;

    std::vector<std::array<int, 2>> m_snake;

    std::array<int, 2> m_food;

    const int k_frame_rate = 10;
    const int k_game_space_x = 100;
    const int k_game_space_y = 45;

    int m_points;
    int m_high_score;
    int m_snake_dir;

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