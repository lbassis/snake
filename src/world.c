#include <unistd.h>
#include <curses.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <base.h>
#include <interface.h>
#include <world.h>

typedef struct {
  unsigned short size_x;
  unsigned short size_y;
  int **world;
} WORLD_t;

void init_world(void **world, struct winsize w) {

  int i, j;
  int width = w.ws_col;
  int height = w.ws_row;
  WORLD_t *b = malloc(sizeof(WORLD_t));

  b->size_x = width;
  b->size_y = height;

  b->world = (int**)malloc(sizeof(int*) * width);

  for (i = 0; i < width; i++) {
    b->world[i] = (int*)malloc(sizeof(int) * height);
  }

  for (i = 0; i < width; i++) {
    for (j = 0; j < height; j++) {
      b->world[i][j] = EMPTY_CELL;
    }
  }

  /* sets the seed */
  srand(time(0));

  *world = b;
}

void destroy_world(void **world) {

  int i, width;
  WORLD_t *b = (WORLD_t *)*world;
  
  width = b->size_x;

  for (i = 0; i < width; i++) {
    free(b->world[i]);
  }
  free(b->world);
  free(b);
}

void update_world(void *world) {

  int i, j;
  WORLD_t *b = (WORLD_t *)world;
  int width = b->size_x;
  int height = b->size_y;
  
  for (i = 0; i < width; i++) {
    for (j = 0; j < height; j++) {
      
      if (b->world[i][j] > EMPTY_CELL) {
	b->world[i][j]--;

	if (b->world[i][j] <= (EMPTY_CELL + 1)) {
	  mvaddch(j, i, ' ');
	}
      }
    }
  }
}

void debug_world(void *world) {

  int i, j;
  WORLD_t *b = (WORLD_t *)world;
  int width = b->size_x;
  int height = b->size_y;
  
  for (i=0; i<width; i++) {
    for (j=0; j<height; j++) {
      printf("%hu ", b->world[i][j]);
    }
    printf("\n");
  }
}

void create_obstacle(void *world, unsigned short x, unsigned short y, unsigned short duration) {

  WORLD_t *b = (WORLD_t *)world;

  b->world[x][y] = duration;
}

int check_obstacle(void *world, unsigned short x, unsigned short y) {

  WORLD_t *b = (WORLD_t *)world;

  if (b->world[x][y] > 0 || b->world[x][y] == BORDER_CELL) {
    return 1;
  }
  else {
    return 0;
  }
}

void create_food(void *world) {
  
  WORLD_t *b = (WORLD_t *)world;
  int width = b->size_x;
  int height = b->size_y;

  int x = MARGIN_X + 1 + random() % (width - 2*(MARGIN_X+1));
  int y = MARGIN_Y + 1 + random() % (height - 2*(MARGIN_Y+1));

  b->world[x][y] = FOOD_CELL;
  mvaddch(y, x, '*');
}

void destroy_food(void *world, unsigned short x, unsigned short y) {

  WORLD_t *b = (WORLD_t *)world;

  b->world[x][y] = 0;
  mvaddch(y, x, ' ');
}

int check_food(void *world, unsigned short x, unsigned short y) {

  WORLD_t *b = (WORLD_t *)world;

  if (b->world[x][y] == FOOD_CELL) {
    destroy_food(world, x, y);
    increase_tail(world);
    create_food(world);

    return 1;
  }

  return 0;
}

void increase_tail(void *world) {

  int i, j;
  WORLD_t *b = (WORLD_t *)world;

  for (i = 0; i < b->size_x; i++) {
    for (j = 0; j < b->size_y; j++) {
      if (b->world[i][j] > EMPTY_CELL) {
	b->world[i][j]++;
	mvaddch(j, i, '#');
      }
    }
  }
}
