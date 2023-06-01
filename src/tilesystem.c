#ifndef MAP_HEIGHT
#define MAP_HEIGHT 25
#endif
#ifndef MAP_WIDTH
#define MAP_WIDTH 100
#endif

#include "tilesystem.h"
typedef enum
{
    WALKABLE
} states;

Entity create_tile(EntityManager *manager, TileSystem *tilesystem)
{
    Entity tile = create_entity(manager);
    add_component(manager, tile, SPRITE);
    add_component(manager, tile, STATE);
    add_component(manager, tile, POSITION);
    tilesystem->TILES[tile] = true;
    return tile;
}

void destroy_tile(EntityManager *manager, TileSystem *tilesystem, Entity ID)
{
    destroy_entity(manager, ID);
    tilesystem->TILES[ID] = false;
}

TileSystem *Init_Tile_System()
{
    TileSystem *tilesystem = malloc(sizeof(TileSystem));
    tilesystem->create_tile = create_tile;
    for (Entity ID = 0; ID < MAX_ENTITIES; ID++)
        tilesystem->TILES[ID] = false;
    return tilesystem;
}

void create_map(EntityManager *manager, TileSystem *tilesystem)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            Entity tile = tilesystem->create_tile(manager, tilesystem);
            Sprite *sp = (Sprite *)return_component(manager, tile, SPRITE);
            State *st = (State *)return_component(manager, tile, STATE);
            Position *po = (Position *)return_component(manager, tile, POSITION);
            if (!(y > MAP_HEIGHT / 2 && x > MAP_WIDTH / 2))
            {
                sp->sprite = '#';
                st->active[WALKABLE] = false;
                po->coordinate.x = x;
                po->coordinate.y = y;
            }
            else
            {
                sp->sprite = '.';
                st->active[WALKABLE] = true;
                po->coordinate.x = x;
                po->coordinate.y = y;
            }
        }
    }
}