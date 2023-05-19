#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>
#include <pthread.h>

#include <world.h>
#include <player.h>

typedef struct {
  unsigned short size;
  unsigned short position_x;
  unsigned short position_y;

  enum Direction direction;
  pthread_t control_tid;
} PLAYER_t;

int get_size(void *player) {

  PLAYER_t *p = (PLAYER_t *)player;
  return p->size;
}

void debug_player(void *player) {
  
  PLAYER_t *p = (PLAYER_t *)player;
  printf("position_x = %hu; position_y = %hu; direction = %hu\n",
	 p->position_x, p->position_y, p->direction);
}

void init_player(void **player, int width, int height) {

  PLAYER_t *p = malloc(sizeof(PLAYER_t));

  p->size = INITIAL_SIZE;
  p->direction = SOUTH;
  p->position_x = (int) width/2 + MARGIN_X;
  p->position_y = (int) height/2 + MARGIN_Y;

  pthread_create(&(p->control_tid), NULL, input_control, p);
  *player = p;
}

void *input_control(void *player) {
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

void move_player(void *player, void *world) {

  PLAYER_t *p = (PLAYER_t *)player;

  create_obstacle(world, p->position_x, p->position_y, p->size);
  
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

  int rt = check_obstacle(world, p->position_x, p->position_y);
  
  return !rt;
}
    
void eat(void *player, void *world) {

  PLAYER_t *p = (PLAYER_t *)player;

  if (check_food(world, p->position_x, p->position_y)) {
    p->size++;
  }
}
