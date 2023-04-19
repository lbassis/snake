#include <curses.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>

#include <world.h>

typedef struct {
  unsigned short size_x;
  unsigned short size_y;

  unsigned short **world;
} WORLD_t;

void init_world(void **world, int width, int height) {

  WORLD_t *b = malloc(sizeof(WORLD_t));

  b->size_x = width;
  b->size_y = height;

  b->world = (unsigned short**)malloc(sizeof(unsigned short*) * width);
  for (int i = 0; i < width; i++)
    b->world[i] = (unsigned short*)malloc(sizeof(unsigned short) * height);

  for (int i=0; i<width; i++)
    {
      for (int j=0; j<height; j++)
        {
	  b->world[i][j] = 0;    
        }
    }

  * world = b;
}

void create_enemy(void *world, unsigned short x, unsigned short y) {

  WORLD_t *b = (WORLD_t *)world;

  b->world[x][y] = ENEMY;
}

int check_enemy(void *world, unsigned short x, unsigned short y) {

  WORLD_t *b = (WORLD_t *)world;

  return (b->world[x][y] == ENEMY);
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
