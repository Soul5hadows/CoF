#ifndef ECS_H
#define ECS_H

#include <stdio.h>
#include <stdbool.h>
#include "stack.h"
#include "componentvector.h"
#include "components.h"

typedef struct
{
  bool mask[MAX_ENTITIES][MAX_COMPONENTS];
  Stack *stack;
  ComponentVector *component_vectors[MAX_COMPONENTS];
}EntityManager;

EntityManager* Init_Entity_Manager(void);
Entity create_entity(EntityManager *);
void destroy_entity(EntityManager *, Entity);
void add_component(EntityManager *, Entity, int);
void remove_component(EntityManager *, Entity, int);
bool has_component(EntityManager *, Entity, int);
Entity* fetch_with(EntityManager *, int, ...);
void* return_component(EntityManager *, Entity, int);
void clean_manager(EntityManager *);

#endif