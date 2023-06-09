#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <ncurses.h>
#include <sys/ioctl.h>

#include <interface.h>
#include <player.h>
#include <world.h>

#define DELAY 75000
#define ESC_KEY 27

int while_esc();
void game_loop(void *player, void *world, int score_position);

int main() {

  int score_position;
  void *player = NULL;
  void *world = NULL;
  struct winsize w;

  init_curses();
  w = create_screen();


  while (1) {

    init_world(&world, w);
    draw_menu(w, DRAW);

    if (while_esc()) {
      break;
    }

    draw_menu(w, CLEAR);
    draw_screen(w, world);
    score_position = draw_score(w);
    init_player(&player, w.ws_col, w.ws_row);
    create_food(world);

    game_loop(player, world, score_position);

    destroy_world(&world);
    destroy_player(&player);
    draw_game_over(w);

    if (while_esc()) {
      break;
    }
  }

  endwin();
  return 0;
}

int while_esc() {

  int char_read;

  do {
    char_read = getch();

    if (char_read == ESC_KEY) {
      return 1;
    }

  }while(char_read == ERR);

  return 0;
}

void game_loop(void *player, void *world, int score_position) {

  while (1) {
    if (!is_alive(player, world)) {
      return;
    }
    else {
      eat(player, world);
    }

    update_world(world);
    print_player(player);
    move_player(player, world);

    update_score(player, score_position);
    usleep(DELAY);
  }
}
