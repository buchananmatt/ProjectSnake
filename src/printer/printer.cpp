// 
// PRINTER.CPP [PROJECT SNAKE]
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
#include <string>
#include <fstream>

#include <ncurses.h>

#include "../game/game.hpp"
#include "../printer/printer.hpp"

using bocan::snake::Game;
using bocan::snake::Printer;

///
/// @brief constructor method for the Printer class. initializations occur in the SetupScreen() function. 
/// @param
/// @return Printer object.
/// @todo
///
Printer::Printer() {

} 

///
/// @brief: destructor method for the Printer class. memory is deallocated in the Exit() function.
/// @param
/// @return
/// @todo
///
Printer::~Printer() {

}

///
/// @brief initializes the screen windows and draws window borders.
/// @param
/// @return
/// @todo define window size constants in printer.hpp to replace constants.
///
void Printer::SetupScreen() {

    // ncurses window setup
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);

    // total screen size ... columns x ... rows
    // screen begins on column ... and row ...
    win_title = newwin(5, 50, 1, 30);
    win_high_score = newwin(5, 24, 1, 2);
    win_score = newwin(5, 24, 1, 84);
    win_game_space = newwin(35, 106, 6, 2);

    // draw borders around each window
    wborder(win_title, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_high_score, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_score, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(win_game_space, 0, 0, 0, 0, 0, 0, 0, 0);

    // print each window
    PrintTitle();
    PrintHighScore();
    PrintScore(0);

    wrefresh(win_game_space);

}

///
/// @brief delete screen windows and deallocate memory.
/// @param
/// @return
/// @todo
///
void Printer::EndScreen() {

    delwin(win_title);
    delwin(win_high_score);
    delwin(win_score);
    delwin(win_game_space);
    endwin();

}

///
/// @brief reprint contents of the title and score windows.
/// @param[in] score as an integer, passed to the private method PrintScore(int).
/// @return
/// @todo
///
void Printer::RefreshScreen(int score) {

    PrintTitle();
    PrintHighScore();
    PrintScore(score);

}

///
/// @brief reprint contents of the gamespace window. this function is called every frame to move the snake.
/// @param[in] snake as a linked-list of integer arrays. integer arrays represent each snake segment position in {column, row} from the left and top of the screen.
/// @param[in] food as an integer array. integer array represents the food position in {column, row} from the left and top of the screen.
/// @return
/// @todo pass snake and food by const reference instead of by value to improve performance.
///
void Printer::RefreshGameSpace(std::list<std::array<int, 2>> snake, std::array<int, 2> food) {

    PrintGameSpace(snake, food);
}

///
/// @brief load the previous high score from the savefile. print the game start menu and receive user input.
/// @param
/// @return boolean true to start the game or boolean false if user quit the game.
/// @todo add input option to allow user to reset high score history.
///
bool Printer::StartGame() {
    
    // load save file
    m_load_stream.open(m_save_file, std::ios::in);

    // find last line of savefile
    m_load_stream.seekg(0, std::ios_base::end);
    char symbol = ' ';
    while (symbol != '\n') {
        m_load_stream.seekg(-2, std::ios_base::cur);

        if ((int)m_load_stream.tellg() == 0) {
            m_load_stream.seekg(0);
            break;
        }
        m_load_stream.get(symbol);
    }

    // load the current high score
    m_load_stream >> m_high_score;
    m_load_stream >> m_player_name;
    m_load_stream >> m_snake_name;
    m_load_stream.close();

    // clear the screen
    werase(win_game_space);
    wborder(win_game_space, 0, 0, 0, 0, 0, 0, 0, 0);

    // print the start menu
    nodelay(stdscr, false);
    wmove(win_game_space, 1, 1);
    static_cast<void> ( waddstr(win_game_space, ">PROJECT SNAKE [2023] [MATTHEW BUCHANAN] [BOCAN SOFTWARE]") );
    wrefresh(win_game_space);
    PrintHighScore();
    wmove(win_game_space, 2, 1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    if (!m_high_score.empty()) {
        static_cast<void> ( waddstr(win_game_space, ">CURRENT HIGH SCORE IS [") );
        static_cast<void> ( waddstr(win_game_space, m_high_score.c_str()) );
        static_cast<void> ( waddstr(win_game_space, "] BY PLAYER [") );
        static_cast<void> ( waddstr(win_game_space, m_player_name.c_str()) );
        static_cast<void> ( waddstr(win_game_space, "] AND SNAKE [") );
        static_cast<void> ( waddstr(win_game_space, m_snake_name.c_str()) );
        static_cast<void> ( waddstr(win_game_space, "].") );
    } else {
        static_cast<void> ( waddstr(win_game_space, ">NO PREVIOUS HIGH SCORE DATA AVAILABLE.") );
    }
    wrefresh(win_game_space);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    wmove(win_game_space, 3, 1);
    static_cast<void> ( waddstr(win_game_space, ">PRESS ANY KEY TO START THE GAME... PRESS 'Q' ANYTIME TO QUIT...") );
    wrefresh(win_game_space);

    // flush input buffer
    static_cast<void> ( flushinp() );

    // get user input
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

///
/// @brief checks for a new high score and records new high score to savefile. prints the end menu.
/// @param[in] score as an integer; used to compare against the previous high score.
/// @return boolean true if user quit the game, boolean false to return to the start menu
/// @todo
///
bool Printer::EndGame(int score) {
    
    // clear the screen
    werase(win_game_space);
    wborder(win_game_space, 0, 0, 0, 0, 0, 0, 0, 0);

    // print end game menu
    nodelay(stdscr, false);
    wmove(win_game_space, 1, 1);
    static_cast<void> ( waddstr(win_game_space, ">GAME OVER.") );
    wrefresh(win_game_space);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::string str_score = std::to_string(score);

    // print out game score
    wmove(win_game_space, 2, 1);
    static_cast<void> ( waddstr(win_game_space, ">YOUR SCORE IS ") );
    static_cast<void> ( waddstr(win_game_space, str_score.c_str()) );
    static_cast<void> ( waddstr(win_game_space, ".") );
    wrefresh(win_game_space);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    wmove(win_game_space, 3, 1);

    // player has the new high score, record new high score in savefile
    if(m_high_score.empty() || score > std::stoi(m_high_score)) {
        echo();
        char c_player_name[20];
        char c_snake_name[20];
        static_cast<void> ( waddstr(win_game_space, ">YOU HAVE THE NEW HIGH SCORE!") );
        
        static_cast<void> ( flushinp() );
        wmove(win_game_space, 4, 1);
        static_cast<void> ( waddstr(win_game_space, ">PLAYER NAME: ") );
        wrefresh(win_game_space);
        static_cast<void> ( wgetnstr(win_game_space, c_player_name, 20) );
        wmove(win_game_space, 5, 1);
        static_cast<void> ( waddstr(win_game_space, ">SNAKE NAME: ") );
        wrefresh(win_game_space);
        static_cast<void> ( wgetnstr(win_game_space, c_snake_name, 20) );
        noecho();
        m_high_score = std::to_string(score);
        m_player_name = std::string(c_player_name);
        m_snake_name = std::string(c_snake_name);

        m_save_stream.open(m_save_file, std::ios::out | std::ios::app);
        m_save_stream << std::endl;
        m_save_stream << m_high_score << " ";
        m_save_stream << m_player_name << " ";
        m_save_stream << m_snake_name;
        m_save_stream.close();

        wmove(win_game_space, 6, 1);
        static_cast<void> ( waddstr(win_game_space, ">NEW HIGH SCORE SAVED!") );

        wmove(win_game_space, 7, 1);
        static_cast<void> (waddstr(win_game_space, ">PRESS ANY KEY TO RETURN TO START MENU OR PRESS 'Q' TO QUIT.") );

    // player did not beat the previous high score
    } else {

        static_cast<void> ( waddstr(win_game_space, ">CURRENT HIGH SCORE IS [") );
        static_cast<void> ( waddstr(win_game_space, m_high_score.c_str()) );
        static_cast<void> ( waddstr(win_game_space, "] BY PLAYER [") );
        static_cast<void> ( waddstr(win_game_space, m_player_name.c_str()) );
        static_cast<void> ( waddstr(win_game_space, "] AND SNAKE [") );
        static_cast<void> ( waddstr(win_game_space, m_snake_name.c_str()) );
        static_cast<void> ( waddstr(win_game_space, "].") );
        wmove(win_game_space, 4, 1);
        static_cast<void> ( waddstr(win_game_space, "PRESS ANY KEY TO RETURN TO START MENU OR PRESS 'Q' TO QUIT.") );
    }
    wrefresh(win_game_space);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    static_cast<void> ( flushinp() );

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

///
/// @brief continuous loop while game is paused, waits for user to unpause the game.
/// @brief side effect is to remain in function until user presses unpause command.
/// @param
/// @return 
/// @todo
///
void Printer::Pause() {

    nodelay(stdscr, false);

    int input;
    static_cast<void> ( flushinp() );
    
    // loop while waiting for user to unpause
    do {
        input = wgetch(win_game_space);
    } while (input != 'p' && input != 'P');

    nodelay(stdscr, true);
}

///
/// @brief prints message to alert to user the program is exiting.
/// @param
/// @return
/// @todo
///
void Printer::Exit() {

    // clear the gamespace window
    werase(win_game_space);
    wborder(win_game_space, 0, 0, 0, 0, 0, 0, 0, 0);

    // print exit message
    wmove(win_game_space, 1, 1);
    static_cast<void> ( waddstr(win_game_space, ">EXITING...") );

    wrefresh(win_game_space);

    std::this_thread::sleep_for(std::chrono::milliseconds(1500)); 
}

///
/// @brief gets the user input during the main game loop. user can change direction of the snake, pause the game, or exit the game.
/// @param
/// @return integer represented by a user input enumerator.
/// @todo
///
int Printer::GetDirection() {

    int ch;

    // default state which means user has not pressed a key
    if( (ch = wgetch(stdscr)) == ERR) {
        return ERROR;
    }
    else {

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
            case 'P':
            case 'p':
                return PAUSE;
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

///
/// @brief prints the game title window. does not update after initial print.
/// @param
/// @return
/// @todo
///
void Printer::PrintTitle() {

    // clear the window
    werase(win_title); 
    wborder(win_title, 0, 0, 0, 0, 0, 0, 0, 0);

    // print the game title
    wmove(win_title, 1, 19);
    static_cast<void> ( waddstr(win_title, "PROJECT SNAKE") );

    wmove(win_title, 3, 4);
    static_cast<void> ( waddstr(win_title, "[2023] [MATTHEW BUCHANAN] [BOCAN SOFTWARE]") );

    wrefresh(win_title);

}

///
/// @brief prints the current high score loaded in from the savefile.
/// @param
/// @return
/// @todo
///
void Printer::PrintHighScore() {

    // clear the window
    werase(win_high_score); 
    wborder(win_high_score, 0, 0, 0, 0, 0, 0, 0, 0);

    // print the score
    wmove(win_high_score, 2, 4);
    static_cast<void> ( waddstr(win_high_score, "HIGH SCORE: ") );

    wmove(win_high_score, 2, 17);
    static_cast<void> ( waddstr(win_high_score, m_high_score.c_str()) );

    wrefresh(win_high_score);

}

///
/// @brief prints the score for the current game during the main gameloop.
/// @param[in] score for the current game as an integer.
/// @return
/// @todo
///
void Printer::PrintScore(int score) {

    // convert integer score to a string
    std::string score_str = std::to_string(score);

    // clear the window
    werase(win_score); 
    wborder(win_score, 0, 0, 0, 0, 0, 0, 0, 0);

    // print the score
    wmove(win_score, 2, 7);
    static_cast<void> ( waddstr(win_score, "SCORE: ") );

    wmove(win_score, 2, 15);
    static_cast<void> ( waddstr(win_score, score_str.c_str()) );

    wrefresh(win_score);

}

///
/// @brief prints the main gameplay window once per frame to upate snake position.
/// @param[in] snake @see Printer::RefreshGameSpace()
/// @param[in] food @see Printer::RefreshGameSpace()
/// @return
/// @todo @see Printer::RefreshGameSpace()
/// 
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
    
    // move cursor to the top left of the window
    wmove(win_game_space, 1, 1);
    wrefresh(win_game_space);

}
