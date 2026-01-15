#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "../include/term.h"
#include "../include/editor.h"

void handle_key_press();
char read_key();


int main()
{
    enable_raw_mode();
    get_window_size();
    E.cx = E.cy = 0;
    refresh_screen();
    while (1) {
        /* refresh_screen(); */
        handle_key_press();
    }
    exit(0);
}
