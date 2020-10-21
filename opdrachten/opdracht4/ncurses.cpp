// Embedded Systems | HvA 2020
// Opdracht 4 week 2
//
// Rowan Bolding
// Bart-Jan van Strien
//
// Compile: g++ -Wall -o ncurses ncurses.cpp -lncurses
// Run    : ./ncurses

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

int main()
{
    WINDOW * mainwin, * childwin;

    // init main window
    int width = 30, height = 6;
    int rows = 25, cols = 80;
    int x = (cols - width) /2;
    int y = (rows - height) /2;
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
    // wait for user input before exit
    getch();
	
    // EXIT!
    delwin(childwin);
    delwin(mainwin);
    endwin();
    refresh();
    return EXIT_SUCCESS;
}