// 
// PRINTER.CPP [PROJECT SNAKE]
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

#include <string>
#include <ncurses.h>

#include "../game/game.hpp"
#include "../printer/printer.hpp"
#include "../debug/debug_printer.hpp"

using bocan::snake::Game;
using bocan::snake::Printer;
using bocan::snake::DebugPrinter;

Printer::Printer() {

    db_printer = new bocan::snake::DebugPrinter();

} 

Printer::~Printer() {


}

void Printer::SetupScreen() {

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);

    // total screen size 115 columns x 52 rows
    // screen begins on column 10 and row 2
    win_title = newwin(7, 50, 1, 43);
    win_high_score = newwin(7, 20, 1, 10);
    win_points = newwin(7, 20, 1, 105);
    win_game_space = newwin(37, 115, 8, 10);

    wborder(win_title, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_high_score, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_points, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_game_space, 0, 0, 0, 0, 0, 0, 0, 0);

    PrintTitle();
    PrintHighScore();
    PrintPoints(0);

    wrefresh(win_game_space);

}

void Printer::EndScreen() {

    delwin(win_title);
    delwin(win_high_score);
    delwin(win_points);
    delwin(win_game_space);
    endwin();

}

void Printer::RefreshScreen(int score) {

    PrintTitle();
    PrintHighScore();
    PrintPoints(score);

}

void Printer::RefreshGameSpace(std::list<std::array<int, 2>> snake, std::array<int, 2> food) {

    PrintGameSpace(snake, food);
}

void Printer::RefreshPoints() {

}

bool Printer::StartGame() {

    // clear the screen
    werase(win_game_space);
    wborder(win_game_space, 0, 0, 0, 0, 0, 0, 0, 0);

    nodelay(stdscr, false);
    wmove(win_game_space, 1, 1);
    static_cast<void> ( waddstr(win_game_space, ">WELCOME TO PROJECT SNAKE! BOCAN SOFTWARE'S IMPLEMENTATION OF THE CLASSIC GAME, SNAKE.") );
    wmove(win_game_space, 2, 1);
    static_cast<void> ( waddstr(win_game_space, ">THE CURRENT HIGH SCORE IS ... MADE ON ...") );
    wmove(win_game_space, 3, 1);
    static_cast<void> ( waddstr(win_game_space, ">PRESS ANY KEY TO START... PRESS 'Q' ANYTIME TO QUIT...") );
    wrefresh(win_game_space);

    int ch = wgetch(win_game_space);
    nodelay(stdscr, true);
    switch(ch) {
        case 'Q':
        case 'q':
            return false;
        default:
            return true;
    }
}

bool Printer::EndGame(int score) {
    
    // clear the screen
    werase(win_game_space);
    wborder(win_game_space, 0, 0, 0, 0, 0, 0, 0, 0);

    nodelay(stdscr, false);
    wmove(win_game_space, 1, 1);
    static_cast<void> ( waddstr(win_game_space, ">GAME OVER.") );
    wmove(win_game_space, 2, 1);
    static_cast<void> ( waddstr(win_game_space, ">YOUR SCORE IS ...") );
    wmove(win_game_space, 3, 1);
    if(score > m_high_score) {
        static_cast<void> ( waddstr(win_game_space, ">YOU HAVE THE NEW HIGH SCORE!") );   
    } else {
        static_cast<void> ( waddstr(win_game_space, ">THE CURRENT HIGH SCORE IS ... MADE ON ...") );
    }
    wmove(win_game_space, 4, 1);
    static_cast<void> ( waddstr(win_game_space, ">PRESS ANY KEY TO PLAY AGAIN OR PRESS 'Q' TO QUIT.") );

    int ch = wgetch(win_game_space);
    nodelay(stdscr, true);
    switch(ch) {
        case 'Q':
        case 'q':
            return true;
        default:
            return false;
    }
}

int Printer::GetUserInput() {

    int ch;

    if( (ch = wgetch(stdscr)) == ERR) {
        db_printer->Print(ch);
        return ERROR;
    }
    else {

        db_printer->Print(ch);

        switch(ch) {
            case 'Q':
            case 'q':
                return QUIT;
            case 'N':
            case 'n':
                return NO;
            case 'Y':
            case 'y':
                return YES;
            case KEY_UP:
                return DIRECTION_UP;    
            case KEY_DOWN:
                return DIRECTION_DOWN;
            case KEY_LEFT:
                return DIRECTION_LEFT;
            case KEY_RIGHT:
                return DIRECTION_RIGHT; 
            default:
                return ERROR;
        }
    }
}

void Printer::PrintTitle() {

    werase(win_title); 
    wborder(win_title, 0, 0, 0, 0, 0, 0, 0, 0);

    wmove(win_title, 2, 19);
    static_cast<void> ( waddstr(win_title, "PROJECT SNAKE") );

    wmove(win_title, 4, 4);
    static_cast<void> ( waddstr(win_title, "[2023] [MATTHEW BUCHANAN] [BOCAN SOFTWARE]") );

    wrefresh(win_title);

}

void Printer::PrintHighScore() {

    std::string high_score_str = std::to_string(m_high_score);

    werase(win_high_score); 
    wborder(win_high_score, 0, 0, 0, 0, 0, 0, 0, 0);

    wmove(win_high_score, 2, 5);
    static_cast<void> ( waddstr(win_high_score, "HIGH SCORE") );

    wmove(win_high_score, 4, 9);
    static_cast<void> ( waddstr(win_high_score, high_score_str.c_str()) );

    wrefresh(win_high_score);

}

void Printer::PrintPoints(int score) {

    std::string score_str = std::to_string(score);

    werase(win_points); 
    wborder(win_points, 0, 0, 0, 0, 0, 0, 0, 0);

    wmove(win_points, 2, 7);
    static_cast<void> ( waddstr(win_points, "SCORE") );

    wmove(win_points, 4, 9);
    static_cast<void> ( waddstr(win_points, score_str.c_str()) );

    wrefresh(win_points);

}

void Printer::PrintGameSpace(std::list<std::array<int, 2>> snake, std::array<int, 2> food) {

    // clear the screen
    werase(win_game_space); 
    wborder(win_game_space, 0, 0, 0, 0, 0, 0, 0, 0);

    // print the snake
    for(auto seg : snake) {
        wmove(win_game_space, seg[0], seg[1]);
        static_cast<void> ( waddch(win_game_space, '#') );
    }

    // print the food
    wmove(win_game_space, food[0], food[1]);
    static_cast<void> ( waddch(win_game_space, '*') );

    wmove(win_game_space, 1, 1);
    wrefresh(win_game_space);

}
