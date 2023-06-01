#ifndef GAME_H
#define GAME_H
#include <curses.h>
#include "ecs.h"
#include "tilesystem.h"

typedef struct Game Game;
struct Game
{
	int is_running;
	EntityManager *manager;
	void (*init)(Game *);
	void (*handle_events)(Game *);
	void (*update)(Game *);
	void (*draw)(Game *);
};

void run(void);

#endif
