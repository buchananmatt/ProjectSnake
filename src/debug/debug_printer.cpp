// 
// DEBUG.CPP [PROJECT SNAKE]
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

#include <deque>
#include <string>

#include "../debug/debug_printer.hpp"

using bocan::snake::DebugPrinter;

DebugPrinter::DebugPrinter() {

    initscr();
    cbreak();
    noecho();
    keypad(win_debug, true);
    nodelay(win_debug, true);

    win_debug = newwin(m_debug.y_height, m_debug.x_length, m_debug.y_origin, m_debug.x_origin);


    wborder(win_debug, 0, 0, 0, 0, 0, 0, 0, 0);

    wmove(win_debug, 1, 1);                                                             
    static_cast<void> ( waddstr(win_debug, ">BOCAN DEBUG CONSOLE") );

    wrefresh(win_debug);
}

DebugPrinter::~DebugPrinter() {

    delwin(win_debug);

    endwin();
}

void DebugPrinter::Print(int message) {

    m_debug_queue.push_back(message);

    while(m_debug_queue.size() > m_max_queue_size) {

        m_debug_queue.pop_front();
    }

    werase(win_debug);
    wborder(win_debug, 0, 0, 0, 0, 0, 0, 0, 0);

    wmove(win_debug, 1, 1);                                                             
    static_cast<void> ( waddstr(win_debug, ">BOCAN DEBUG CONSOLE") );                 

    int i = 2;

    for(auto s : m_debug_queue) {
        wmove(win_debug, i, 1);                                                            
        static_cast<void> ( waddch(win_debug, s) );                                 
        i++;
    }
    wrefresh(win_debug);
    
}