#include <unistd.h>
#include <curses.h>
#include <ncurses.h>
#include <sys/ioctl.h>

#include <base.h>
#include <interface.h>
#include <world.h>

struct winsize create_screen(void) {

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  return w;
}

void print_log(char s)
{
  mvaddch(1, 1, s);
}


void draw_screen(struct winsize w, void *world) {

  int i;

  attron(A_BOLD);
  
  for (i = MARGIN_Y; i < w.ws_col-MARGIN_Y; i++) {
    mvaddch(MARGIN_X, i, '#');
    create_enemy(world, i, MARGIN_X);
  }
  for (i = MARGIN_Y; i < w.ws_col-MARGIN_Y; i++) {
    mvaddch(w.ws_row-MARGIN_X-1, i, '#');
    create_enemy(world, i, w.ws_row-MARGIN_X-1);
  }

  for (i = MARGIN_X; i < w.ws_row-MARGIN_X; i++) {
    mvaddch(i, MARGIN_Y, '#');
    create_enemy(world, MARGIN_Y, i);
  }

  for (i = MARGIN_X; i < w.ws_row-MARGIN_X; i++) {
    mvaddch(i, w.ws_col-MARGIN_Y-1, '#');
    create_enemy(world, w.ws_col-MARGIN_Y-1, i);
  }

  attroff(A_BOLD);
}

void draw_game_over() {
  
}
