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

#include <ncurses.h>

namespace bocan {

namespace snake {

class DebugPrinter;

enum user_input {
    QUIT = 0,
    NO,
    YES,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
    ENTER,
    ERROR
};

class Printer {
public:

    Printer();
    ~Printer();

    bocan::snake::DebugPrinter* db_printer;

    void SetupScreen();
    void EndScreen();
    void RefreshScreen();
    void RefreshGameSpace(std::list<std::array<int, 2>>, std::array<int, 2>);
    void RefreshPoints();

    void StartGame();
    void EndGame();

    int GetUserInput();

private:

    WINDOW* win_title;
    WINDOW* win_high_score;
    WINDOW* win_points;
    WINDOW* win_game_space;

private:

    void PrintTitle();
    void PrintHighScore();
    void PrintPoints();
    void PrintGameSpace(std::list<std::array<int, 2>>, std::array<int, 2>);

};

} // NAMESPACE SNAKE

} // NAMESPACE BOCAN

#endif // PRINTER_HPP