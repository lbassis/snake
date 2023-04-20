#include <stdlib.h>

enum CELL {
  EMPTY,
  PLAYER,
  ENEMY
};


void init_world(void **world, int width, int height);
void create_enemy(void *world, unsigned short x, unsigned short y);
int check_enemy(void *world, unsigned short x, unsigned short y);

void debug_world(void *world);
