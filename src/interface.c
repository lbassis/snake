#include <unistd.h>
#include <curses.h>
#include <ncurses.h>
#include <sys/ioctl.h>

#include <base.h>
#include <interface.h>

struct winsize draw_screen() {

  int i;
  
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);


  attron(A_BOLD);
  
  for (i = MARGIN_Y; i < w.ws_col-MARGIN_Y; i++) {
    mvaddch(MARGIN_X, i, '#');
  }
  for (i = MARGIN_Y; i < w.ws_col-MARGIN_Y; i++) {
    mvaddch(w.ws_row-MARGIN_X-1, i, '#');
  }

  for (i = MARGIN_X; i < w.ws_row-MARGIN_X; i++) {
    mvaddch(i, MARGIN_Y, '#');
  }

  for (i = MARGIN_X; i < w.ws_row-MARGIN_X; i++) {
    mvaddch(i, w.ws_col-MARGIN_Y-1, '#');
  }

  attroff(A_BOLD);
  return w;
}

void draw_game_over() {
  
}
