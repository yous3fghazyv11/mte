#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/editor.h"
#include "../include/term.h"

char read_key(void)
{
    char c;
    ssize_t nread;

    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN)
            die("read");
        /* if nread == 0 or EAGAIN keep waiting */
    }

    return c;
}

void handle_key_press()
{
    char c = read_key();

    if (c == CTRL_KEY('q'))
        exit(0);

    switch (c) {
        case CTRL_KEY('q'):
            exit(0);
            break;
        case 13:
            write(STDERR_FILENO, "\n\r", 2);
            break;
        default: {
            char buff[64];
            int len = snprintf(buff, sizeof(buff), "%c", c);
            write(STDOUT_FILENO, buff, len);
        }
    }

    /* if (iscntrl(c)) { */
    /*     char buff[64]; */
    /*     int len = snprintf(buff, sizeof(buff), "%d\n\r", c); */
    /*     write(STDOUT_FILENO, buff, len); */
    /* } else { */
    /*     char buff[64]; */
    /*     int len = snprintf(buff, sizeof(buff), "%c\n\r", c); */
    /*     write(STDOUT_FILENO, buff, len); */
    /* } */
}
