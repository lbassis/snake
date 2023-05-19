#include <unistd.h>
#include <curses.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <string.h>

#include <interface.h>
#include <world.h>
#include <player.h>

#define GAME_OVER "Game Over!"

void init_curses(void) {
  
  initscr();
  
  curs_set(0); /* Hides the cursor */
  clear();
  noecho();
  cbreak();    /* Line buffering disabled. pass on everything */
  keypad(stdscr, TRUE); /* So we can get KEY_* */
  timeout(1); /* So getch won't block */
  
}

struct winsize create_screen(void) {

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  

  return w;
}

void draw_screen(struct winsize w, void *world) {

  int i;

  attron(A_BOLD);
  
  for (i = MARGIN_Y; i < w.ws_col-MARGIN_Y; i++) {
    mvaddch(MARGIN_X, i, '#');
    create_obstacle(world, i, MARGIN_X, BORDER_CELL);
  }
  for (i = MARGIN_Y; i < w.ws_col-MARGIN_Y; i++) {
    mvaddch(w.ws_row-MARGIN_X-1, i, '#');
    create_obstacle(world, i, w.ws_row-MARGIN_X-1, BORDER_CELL);
  }

  for (i = MARGIN_X; i < w.ws_row-MARGIN_X; i++) {
    mvaddch(i, MARGIN_Y, '#');
    create_obstacle(world, MARGIN_Y, i, BORDER_CELL);
  }

  for (i = MARGIN_X; i < w.ws_row-MARGIN_X; i++) {
    mvaddch(i, w.ws_col-MARGIN_Y-1, '#');
    create_obstacle(world, w.ws_col-MARGIN_Y-1, i, BORDER_CELL);
  }

  attroff(A_BOLD);
}

void draw_game_over(struct winsize w) {

  int width = w.ws_col;
  int height = w.ws_row;

  int center_width = width/2 - strlen(GAME_OVER)/2;
  int center_height = height/2;

  
  attron(A_BOLD);

  clear();
  mvaddstr(center_height, center_width, GAME_OVER);

  attroff(A_BOLD);
  
}

int draw_score(struct winsize w) {

  int center_width;
  int width = w.ws_col;
  char score[50];

  sprintf(score, "Current size: \n");
  center_width = width/2 - (strlen(score)/2); 
  mvaddstr(1, center_width, score);

  return width/2 + (strlen(score)/2);
}

void update_score(void *player, int position) {

  int size = get_size(player);
  char size_str[10];

  sprintf(size_str, "%d", size);
  mvaddstr(1, position, size_str);
}
