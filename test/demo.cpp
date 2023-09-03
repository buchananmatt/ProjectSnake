// 
// DEMO.CPP [PROJECT SNAKE]
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

// program design
// game
//  clock to control framerate and game speed
//  randomizer to emplace food at game start
//  counter to add up points and game score
//  collision detection for snake and walls to end the game
//  file system to keep track of previous high score
//  receive standard arrow keys as input to move snake direction
// snake
//  data structure for snake size, position of segments, current direction
//  snake position updates every frame
// printer
//  api for ncurses
//  print to screen every frame

int main(int argc, char** argv) {

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    WINDOW* win_title = newwin(7, 50, 3, 35);
    WINDOW* win_game = newwin(7, 20, 3, 10);
    WINDOW* win_score = newwin(7, 20, 3, 90);
    WINDOW* win_main = newwin(45, 100, 10, 10);

    wborder(win_title, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_game, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_score, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_main, 0, 0, 0, 0, 0, 0, 0, 0);

    wmove(win_title, 2, 19);
    static_cast<void> ( waddstr(win_title, "PROJECT SNAKE") );

    wmove(win_title, 4, 4);
    static_cast<void> ( waddstr(win_title, "[2023] [MATTHEW BUCHANAN] [BOCAN SOFTWARE]") );

    wmove(win_game, 2, 5);
    static_cast<void> ( waddstr(win_game, "HIGH SCORE") );

    wmove(win_game, 4, 9);
    static_cast<void> ( waddstr(win_game, "90") );

    wmove(win_score, 2, 7);
    static_cast<void> ( waddstr(win_score, "POINTS") );

    wmove(win_score, 4, 9);
    static_cast<void> ( waddstr(win_score, "20") );

    wmove(win_main, 3, 30);
    static_cast<void> ( waddch(win_main, '0') );

    wmove(win_main, 32, 70);
    static_cast<void> ( waddch(win_main, '0') );

    wmove(win_main, 20, 50);
    static_cast<void> ( waddch(win_main, '0') );

    wmove(win_main, 19, 9);
    static_cast<void> ( waddch(win_main, '0') );

    for(int i = 0; i < 7; i++) {
        wmove(win_main, i+20, 34);
        static_cast<void> ( waddch(win_main, '0') );
    }
    for(int i = 0; i < 15; i++) {
        wmove(win_main, 26, 34+i);
        static_cast<void> ( waddch(win_main, '0') );
    }

    wrefresh(win_title);
    wrefresh(win_game);
    wrefresh(win_score);
    wrefresh(win_main);

    static_cast<void> ( wgetch(win_main) );
    
    delwin(win_title);
    delwin(win_main);

    endwin();

    return 0;
}