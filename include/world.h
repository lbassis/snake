#include <stdlib.h>
#include <sys/ioctl.h>

/* By default, every cell is 0; food is -1, the borders are -2 
 * and the snake's body is the number of frames until it disappears
 */
#define EMPTY_CELL -1
#define FOOD_CELL -2
#define BORDER_CELL -3

void init_world(void **world, struct winsize w);
void create_obstacle(void *world, unsigned short x, unsigned short y, unsigned short duration);
int check_obstacle(void *world, unsigned short x, unsigned short y);

int check_position(void *world, unsigned short x, unsigned short y);
void update_world(void *world);
void debug_world(void *world);

void create_food(void *world);
void destroy_food(void *world, unsigned short x, unsigned short y);
int check_food(void *world, unsigned short x, unsigned short y);
void increase_tail(void *world);
