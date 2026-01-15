#include <termios.h>

#ifndef TERM_H
#define TERM_H

struct editor_config {
    struct termios orig_termios;
    int cx, cy;
    int rows;
    int cols;
};

extern struct editor_config E;

void die(char* s);
void disable_raw_mode();
void enable_raw_mode();
void refresh_screen();
void draw_rows();
void get_window_size();

#endif  /* TERM_H */
