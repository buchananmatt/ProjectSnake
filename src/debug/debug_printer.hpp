// 
// DEBUG.HPP [PROJECT SNAKE]
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

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <deque>
#include <string>
#include <array>
#include <list>

#include <ncurses.h>

namespace bocan {

namespace snake {

/// @class DebugPrinter
/// @brief draws a debugging console window to the screen separate from the Printer screen windows.
/// @brief used to debug the game during early development. Not included in the release version of the game.
///
class DebugPrinter {

public:
    DebugPrinter();
    ~DebugPrinter();

    void Print(int);

private:

    WINDOW* win_debug;

    std::deque<int> m_debug_queue;

    int m_max_queue_size = 35;

    struct window_size {
        const int y_origin = 1;
        const int x_origin = 120;
        const int y_height = 40;
        const int x_length = 45;
    } m_debug;
};

} // NAMESPACE SNAKE

} // NAMESPACE BOCAN

#endif // DEBUG_HPP
