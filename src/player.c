#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

#include <world.h>
#include <player.h>

typedef struct {
  unsigned short size;
  unsigned short position_x;
  unsigned short position_y;

  enum Direction direction;
} PLAYER_t;


void debug_player(void *player) {
  
  PLAYER_t *p = (PLAYER_t *)player;
  printf("position_x = %hu; position_y = %hu; direction = %hu\n",
	 p->position_x, p->position_y, p->direction);
}

void init_player(void **player, int width, int height) {

  PLAYER_t *p = malloc(sizeof(PLAYER_t));

  p->direction = SOUTH;
  p->position_x = (int) width/2 + MARGIN_X;
  p->position_y = (int) height/2 + MARGIN_Y;

  *player = p;
}

void move_player(void *player, void *world) {

  PLAYER_t *p = (PLAYER_t *)player;

  create_enemy(world, p->position_x, p->position_y);
  
  switch (p->direction) {

  case NORTH:
    p->position_y -= 1;
    break;
  case WEST:
    p->position_x += 1;
    break;
  case SOUTH:
    p->position_y += 1;
    break;
  case EAST:
    p->position_x -= 1;
    break;
  default:
    break;
  }

}

void print_player(void *player) {

  PLAYER_t *p = (PLAYER_t *)player;
  
  mvaddch(p->position_y, p->position_x, '#');
}

void change_direction(void *player, enum Direction dir) {
  
  PLAYER_t *p = (PLAYER_t *)player;
  int diff = abs((int)p->direction - (int)dir);
  
  if (diff != 2) { /* We can't make a 180 */
    p->direction = dir;
  }
}

int is_alive(void *player, void *world) {

  PLAYER_t *p = (PLAYER_t *)player;

  //printf("testando %hu,%hu\n", p->position_x, p->position_y);
  int rt = check_enemy(world, p->position_x, p->position_y);
  return !rt;
}
    
