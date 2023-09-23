// 
// PRINTER.HPP [PROJECT SNAKE]
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

#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <string>
#include <fstream>

#include <ncurses.h>

namespace bocan {

namespace snake {

///
/// @brief
/// @brief
/// @todo:  implement enum class here instead of enum
///
enum user_input {
    QUIT = 0,
    NO,
    YES,
    PAUSE,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
    ENTER,
    ERROR
};

///
/// @class Printer
/// @brief Provides the interface between the Game and the user. Prints game elements to the screen and receives keyboard input from the user.
/// @brief Acts as the interface with the ncurses library. Responsible for reading and writing information to the savefile.
///
class Printer {
public:

    Printer();
    ~Printer();

    void SetupScreen();
    void EndScreen();
    void RefreshScreen(int);
    void RefreshGameSpace(std::list<std::array<int, 2>>, std::array<int, 2>);

    bool StartGame();
    bool EndGame(int);

    void Pause();        

    void Exit();

    int GetDirection();

private:

    WINDOW* win_title;
    WINDOW* win_high_score;
    WINDOW* win_score;
    WINDOW* win_game_space;

    std::ifstream m_load_stream;
    std::ofstream m_save_stream;
    std::string m_save_file = { "./save/savefile" };

    std::string m_high_score;
    std::string m_player_name;
    std::string m_snake_name;

private:

    void PrintTitle();
    void PrintHighScore();
    void PrintScore(int);
    void PrintGameSpace(std::list<std::array<int, 2>>, std::array<int, 2>);

};

} // NAMESPACE SNAKE

} // NAMESPACE BOCAN

#endif // PRINTER_HPP
