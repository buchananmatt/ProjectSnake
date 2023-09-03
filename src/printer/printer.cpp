// 
// PRINTER.CPP [PROJECT SNAKE]
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



}

Printer::~Printer() {

    delwin(win_title);
    delwin(win_high_score);
    delwin(win_points);
    delwin(win_game_space);
    endwin();

}

void Printer::SetupScreen() {

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

void Printer::RefreshScreen() {

    PrintTitle();
    PrintHighScore();
    PrintPoints();
    PrintGameSpace();

}

void Printer::RefreshGameSpace() {

    PrintGameSpace();
}

void Printer::RefreshPoints() {

    PrintPoints();
}

void Printer::StartGame() {

    PrintGameSpace();
}

void Printer::EndGame() {

    PrintGameSpace();
}

int Printer::GetUserInput() {

//    int ch = wgetch(stdscr);
    int ch = wgetch(win_title);

    switch(ch) {
        case KEY_UP:
            return DIRECTION_UP;    
        case KEY_DOWN:
            return DIRECTION_DOWN;
        case KEY_LEFT:
            return DIRECTION_LEFT;
        case KEY_RIGHT:
            return DIRECTION_RIGHT; 
        case KEY_ENTER:
            return ENTER;
        case 'Q':
        case 'q':
            return QUIT;
        default:
            return ERROR;
    }
}

void Printer::PrintTitle() {

    wmove(win_title, 2, 19);
    static_cast<void> ( waddstr(win_title, "PROJECT SNAKE") );

    wmove(win_title, 4, 4);
    static_cast<void> ( waddstr(win_title, "[2023] [MATTHEW BUCHANAN] [BOCAN SOFTWARE]") );

    wrefresh(win_title);

}

void Printer::PrintHighScore() {

    wmove(win_high_score, 2, 5);
    static_cast<void> ( waddstr(win_high_score, "HIGH SCORE") );

    wmove(win_high_score, 4, 9);
    static_cast<void> ( waddstr(win_high_score, "90") );

    wrefresh(win_high_score);

}

void Printer::PrintPoints() {

    wmove(win_points, 2, 7);
    static_cast<void> ( waddstr(win_points, "POINTS") );

    wmove(win_points, 4, 9);
    static_cast<void> ( waddstr(win_points, "20") );

    wrefresh(win_points);

}

void Printer::PrintGameSpace() {

    wmove(win_game_space, 19, 9);
    static_cast<void> ( waddch(win_game_space, '0') );

    for(int i = 0; i < 7; i++) {
        wmove(win_game_space, i+20, 34);
        static_cast<void> ( waddch(win_game_space, '0') );
    }
    for(int i = 0; i < 15; i++) {
        wmove(win_game_space, 26, 34+i);
        static_cast<void> ( waddch(win_game_space, '0') );
    }

    wrefresh(win_game_space);

}