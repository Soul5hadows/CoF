#include "game.h"
#include "shared.h"
#include "tilesystem.h"
#include "BearLibTerminal.h"

void create_player(Game *, double, double);
void player_movement(Game *);
TileSystem *tilesystem;
void handle_events(Game *game);
void update(Game *);
void draw(Game *);
void init(Game *game)
{
  game->handle_events = handle_events;
  game->update = update;
  game->draw = draw;
  if (terminal_open())
    game->is_running = true;
  game->manager = Init_Entity_Manager();

  tilesystem = Init_Tile_System();
  create_player(game, 101, 26);
  create_map(game->manager, tilesystem);

  while (game->is_running == 1)
  {
    game->handle_events(game);
    game->update(game);
    game->draw(game);
  }

  clean_manager(game->manager);
  free(tilesystem);
  terminal_close();
}

void handle_events(Game *game)
{
  player_movement(game);
}

void update(Game *game)
{
  /*
  Entity *arr = fetch_with(game->manager, 2, POSITION, SPRITE);
  if (arr)
  {
    for (unsigned int i = arr[0]; i >= 1; i--)
    {
      Position *trs = (Position *)return_component(game->manager, arr[i], POSITION);
      Sprite *spr = (Sprite *)return_component(game->manager, arr[i], SPRITE);
    }
    free(arr);
  }
  */
}

void draw(Game *game)
{
}

void run(void)
{
  Game *game = malloc(sizeof(Game));
  init(game);
  free(game);
}

void create_player(Game *game, double x, double y)
{
  Entity player = create_entity(game->manager);
  add_component(game->manager, player, SPRITE);
  add_component(game->manager, player, POSITION);
  add_component(game->manager, player, INPUT);

  Position *pt = (Position *)return_component(game->manager, player, POSITION);
  Sprite *ps = (Sprite *)return_component(game->manager, player, SPRITE);

  pt->coordinate.x = x;
  pt->coordinate.y = y;
  pt->coordinate.z = 0;

  ps->length = ps->width = 1;
  ps->sprite = '@';
}
bool collide(Game *game)
{
  if (1)
  {
    bool collide = false;
    Position *pt = (Position *)return_component(game->manager, 0, POSITION);
    for (Entity ID = 0; ID < MAX_ENTITIES; ID++)
    {
      State *ts = (State *)return_component(game->manager, ID, STATE);
      Position *tt = (Position *)return_component(game->manager, ID, POSITION);
      if (tilesystem->TILES[ID] && !(ts->active[0]))
      {
        if (pt->coordinate.x == tt->coordinate.x && pt->coordinate.y == tt->coordinate.y)
          collide = true;
      }
    }
    return collide;
  }
  return 0;
}
void player_movement(Game *game)
{
  Input *pi = (Input *)return_component(game->manager, 0, INPUT);
  Position *pt = (Position *)return_component(game->manager, 0, POSITION);
  pi->input = 'q';
  switch (pi->input)
  {
  case '4':
    pt->coordinate.x--;
    if (collide(game))
    {
      pt->coordinate.x++;
    }
    break;
  case '7':
    pt->coordinate.x--;
    pt->coordinate.y--;
    if (collide(game))
    {
      pt->coordinate.x++;
      pt->coordinate.y++;
    }
    break;
  case '8':
    pt->coordinate.y--;
    if (collide(game))
    {
      pt->coordinate.y++;
    }
    break;
  case '9':
    pt->coordinate.y--;
    pt->coordinate.x++;
    if (collide(game))
    {
      pt->coordinate.x--;
      pt->coordinate.y++;
    }
    break;
  case '6':
    pt->coordinate.x++;
    if (collide(game))
    {
      pt->coordinate.x--;
    }
    break;
  case '3':
    pt->coordinate.x++;
    pt->coordinate.y++;
    if (collide(game))
    {
      pt->coordinate.x--;
      pt->coordinate.y--;
    }
    break;
  case '2':
    pt->coordinate.y++;
    if (collide(game))
    {
      pt->coordinate.y--;
    }
    break;
  case '1':
    pt->coordinate.y++;
    pt->coordinate.x--;
    if (collide(game))
    {
      pt->coordinate.x++;
      pt->coordinate.y--;
    }
    break;
  case 'q':
    game->is_running = false;
    break;
  }
}