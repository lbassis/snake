#define DRAW 0
#define CLEAR 1

#define GAME_OVER "Game Over"
#define PRESS_TO_START "Press any key to start"
#define ESC "Esc to quit"

void init_curses(void);
struct winsize create_screen(void);
void draw_screen(struct winsize w, void *world);
void draw_menu(struct winsize w, unsigned short mode);
void draw_game_over(struct winsize w);
int draw_score(struct winsize w);
void update_score(void *player, int position);
