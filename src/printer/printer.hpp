// 
// PRINTER.HPP [PROJECT SNAKE]
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

#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <ncurses.h>

namespace bocan {

namespace snake {

class Printer {
public:
    Printer();
    ~Printer();

    void RefreshScreen();
    void RefreshGameSpace();
    void RefreshPoints();

    void StartGame();
    void EndGame();

    void GetUserInput();

private:

    WINDOW* win_title;
    WINDOW* win_high_score;
    WINDOW* win_points;
    WINDOW* win_game_space;

private:

};

} // NAMESPACE SNAKE

} // NAMESPACE BOCAN

#endif // PRINTER_HPP