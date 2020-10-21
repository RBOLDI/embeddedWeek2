//
//
// Compile: g++ -Wall -o ncurses ncurses.cpp -lncurses
// Run    : ./ncurses

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

int main()
{
    WINDOW * mainwin, * childwin;
    int width = 30, height = 6;
    int rows = 25, cols = 80;
    int x = (cols - width) /2;
    int y = (rows - height) /2;

    // init main window
    if ( (mainwin = initscr()) == NULL )
    {
        fprintf(stderr, "ERROR INIT NCURSES\n");
        exit(EXIT_FAILURE);
    }
    noecho();
    keypad(mainwin, TRUE);
    // init child window
    childwin = subwin(mainwin, height, width, y, x);
    box(childwin, '|', '-');
    mvwaddstr(childwin, 1, 7, "Embedded Systems");
    mvwaddstr(childwin, 2, 11, "HvA 2020");
    mvwaddstr(childwin, 3, 8, "Rowan Bolding");
    mvwaddstr(childwin, 4, 5, "Bart-Jan van Strien");
    refresh();
    getch();
	
    delwin(childwin);
    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
   
}