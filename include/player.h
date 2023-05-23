#include <stdlib.h>
#include <sys/ioctl.h>
#include <base.h>

#define INITIAL_SIZE 3

int get_size(void *player);
void debug_player(void *player);
void init_player(void **player, int width, int height);
void destroy_player(void **player);
void *input_control(void *player);
void move_player(void *player, void *world);
void print_player(void *player);
void change_direction(void *player, enum Direction dir);
int is_alive(void *player, void *world);
void eat(void *player, void *world);
