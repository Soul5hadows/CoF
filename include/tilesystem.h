#ifndef TILESYSTEM_H
#define TILESYSTEM_H

#include "ecs.h"

typedef struct TileSystem TileSystem;
struct TileSystem
{
    bool TILES[MAX_ENTITIES];
    Entity (*create_tile)(EntityManager *, TileSystem *);
};

struct TileSystem* Init_Tile_System();

void create_map(EntityManager *, TileSystem *);

#endif