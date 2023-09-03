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

#include <ncurses.h>

#include "../game/game.hpp"
#include "../printer/printer.hpp"

using bocan::snake::Printer;

Printer::Printer() {

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);

    win_title = newwin(7, 50, 3, 35);
    win_high_score = newwin(7, 20, 3, 10);
    win_points = newwin(7, 20, 3, 90);
    win_game_space = newwin(45, 100, 10, 10);

    wborder(win_title, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_high_score, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_points, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_game_space, 0, 0, 0, 0, 0, 0, 0, 0);

}

Printer::~Printer() {

    delwin(win_title);
    delwin(win_high_score);
    delwin(win_points);
    delwin(win_game_space);
    endwin();

}

void Printer::RefreshScreen() {


}

void Printer::RefreshGameSpace() {


}

void Printer::RefreshPoints() {


}

void Printer::StartGame() {


}

void Printer::EndGame() {

    
}

void Printer::GetUserInput() {


}