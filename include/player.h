#include <stdlib.h>
#include <sys/ioctl.h>

#include "base.h"

void debug_player(void *player);
void init_player(void **player, int width, int height);
void move_player(void *player, void *world);
void print_player(void *player);
void change_direction(void *player, enum Direction dir);
int is_alive(void *player, void *world);
