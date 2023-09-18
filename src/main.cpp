// 
// MAIN.CPP [PROJECT SNAKE]
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

/// @file main.cpp This file contains the main function and entry point for the application.
/// The main function constructs a Game object and calls its public methods to
/// run the game. Game takes care of all of the Printer method calls.
///
/// @namespace bocan is the namespace used for all bocan software projects.
/// It is my personal namespace for all of my C++ projects.
///
/// @namespace snake is the namespace used for this application.

#include "./game/game.hpp"

int main(int argc, char** argv) {

    bocan::snake::Game game;

    do {
        game.Start();
        game.GameLoop();
        
    } while(!game.EndGame());

    return 0;
}
