#include <asm-generic/ioctls.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "../include/term.h"

struct editor_config E;

void die(char* s)
{
    perror(s);
    exit(1);
}

void disable_raw_mode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
        die("tcsetattr");
    printf("Exiting...\n");
}

void enable_raw_mode()
{
    if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1)
        die("tcgetattr");
    atexit(disable_raw_mode);
    struct termios raw = E.orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

void refresh_screen()
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
    draw_rows();
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void draw_rows()
{
    for (int i = 0; i < E.rows; i++) {
        if (i != E.rows -1)
            write(STDOUT_FILENO, "~\n\r", 3);
        else
            write(STDOUT_FILENO, "~", 1);
    }
}

void get_window_size()
{
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
        die("get_window_size");
    E.cols = ws.ws_col;
    E.rows = ws.ws_row;
}
