#ifndef EDITOR_H
#define EDITOR_H

#define CTRL_KEY(k) ((k) & 0x1f)

char read_key();
void handle_key_press();

#endif  /* EDITOR_H */
