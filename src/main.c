#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <pthread.h>

#include <interface.h>
#include <player.h>

void *input_control(void *player)
{
  int ch;
  
  while (1) {

    ch = getch();

    switch (ch) {
    case KEY_UP:
      change_direction(player, NORTH);
      break;
    case KEY_RIGHT:
      change_direction(player, WEST);
      break;
    case KEY_DOWN:
      change_direction(player, SOUTH);
      break;
    case KEY_LEFT:
      change_direction(player, EAST);
      break;
    default:
      break;
    }
  }
}

int main() {

  void *player = NULL;
  pthread_t thread_id;
  struct winsize w;
  
  initscr();
  curs_set(0); /* Hides the cursor */
  clear();
  noecho();
  cbreak();	/* Line buffering disabled. pass on everything */
  keypad(stdscr, TRUE);
  timeout(1);

  w = draw_screen();
  init_player(&player, w.ws_col, w.ws_row);
  
  pthread_create (&thread_id, NULL, input_control, player);  

  
  while (1) {
    usleep(100000);
    print_player(player);
    move_player(player);

    if (check_outside(player, w)) {
      break;
    }
  }
  endwin();
  return 0;
}
