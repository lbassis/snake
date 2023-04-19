#include <curses.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned short size_x;
  unsigned short size_y;

  unsigned short **world;
} WORLD;

void init_world(void **world, int width, int height) {

    WORLD *b = malloc(sizeof(WORLD));

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