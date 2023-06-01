#include <stdarg.h>
#include "ecs.h"
#include "components.h"

void Init_Manager_Components(EntityManager *manager)
{
  ComponentVector *InputVector = malloc(sizeof(ComponentVector));
  Init_Component_Vector(InputVector);
  InputVector->component_array = calloc(InputVector->capacity, sizeof(Input *));
  manager->component_vectors[INPUT] = InputVector;

  ComponentVector *SpriteVector = malloc(sizeof(ComponentVector));
  Init_Component_Vector(SpriteVector);
  SpriteVector->component_array = calloc(SpriteVector->capacity, sizeof(Sprite *));
  manager->component_vectors[SPRITE] = SpriteVector;

  ComponentVector *StateVector = malloc(sizeof(ComponentVector));
  Init_Component_Vector(StateVector);
  StateVector->component_array = calloc(StateVector->capacity, sizeof(State *));
  manager->component_vectors[STATE] = StateVector;

  ComponentVector *StatusVector = malloc(sizeof(ComponentVector));
  Init_Component_Vector(StatusVector);
  StatusVector->component_array = calloc(StatusVector->capacity, sizeof(Status *));
  manager->component_vectors[STATUS] = StatusVector;

  ComponentVector *TransformVector = malloc(sizeof(ComponentVector));
  Init_Component_Vector(TransformVector);
  TransformVector->component_array = calloc(TransformVector->capacity, sizeof(Transform *));
  manager->component_vectors[TRANSFORM] = TransformVector;

  ComponentVector *PositionVector = malloc(sizeof(ComponentVector));
  Init_Component_Vector(PositionVector);
  PositionVector->component_array = calloc(PositionVector->capacity, sizeof(Position *));
  manager->component_vectors[POSITION] = PositionVector;
}

EntityManager *Init_Entity_Manager(void)
{
  EntityManager *manager = malloc(sizeof(EntityManager));
  for (int EID = 0; EID < MAX_ENTITIES; EID++)
  {
    for (int i = 0; i < MAX_COMPONENTS; i++)
    {
      manager->mask[EID][i] = false;
    }
  }

  manager->stack = malloc(sizeof(Stack));
  Stack_Init(manager->stack);

  for (int i = 0; i < MAX_COMPONENTS; i++)
    manager->component_vectors[i] = NULL;

  Init_Manager_Components(manager);

  return manager;
}

Entity create_entity(EntityManager *manager)
{
  Entity EID = manager->stack->pop(manager->stack);
  manager->mask[EID][0] = true;
  return EID;
}

void destroy_entity(EntityManager *manager, Entity EID)
{
  if (manager->mask[EID][0])
  {
    for (int i = 1; i < MAX_COMPONENTS; i++)
    {
      remove_component(manager, EID, i);
    }
    manager->mask[EID][0] = false;
    manager->stack->push(manager->stack, EID);
  }
}

void add_component(EntityManager *manager, Entity EID, int component_id)
{
  if (manager->mask[EID][0])
  {
    void *component_type;
    switch (component_id)
    {
    case INPUT:
    {
      Input *input = malloc(sizeof(Input));
      component_type = input;
      break;
    }
    case SPRITE:
    {
      Sprite *sprite = malloc(sizeof(Sprite));
      component_type = sprite;
      break;
    }
    case STATE:
    {
      State *state = malloc(sizeof(State));
      component_type = state;
      break;
    }
    case STATUS:
    {
      Status *status = malloc(sizeof(Status));
      component_type = status;
      break;
    }
    case TRANSFORM:
    {
      Transform *transform = malloc(sizeof(Transform));
      component_type = transform;
      break;
    }
    case POSITION:
    {
      Position *position = malloc(sizeof(Position));
      component_type = position;
      break;
    }
    default:
      component_type = NULL;
    }

    if (component_type)
    {
      manager->mask[EID][component_id] = true;
      if (manager->component_vectors[component_id])
        manager->component_vectors[component_id]->Cadd(manager->component_vectors[component_id], component_type, EID);
    }
  }
}

void remove_component(EntityManager *manager, Entity EID, int component_id)
{
  if (manager->mask[EID][0])
  {
    if (manager->mask[EID][component_id])
    {
      manager->mask[EID][component_id] = false;
      manager->component_vectors[component_id]->Cremove(manager->component_vectors[component_id], EID);
    }
  }
}

bool has_component(EntityManager *manager, Entity EID, int component_id)
{
  if (manager->mask[EID][0])
  {
    return manager->mask[EID][component_id];
  }
  else
    return false;
}

Entity *fetch_with(EntityManager *manager, int component_count, ... /*components*/)
{
  Entity *arr = calloc(manager->stack->top + 1, sizeof(Entity));

  if (arr)
  {
    va_list valist;
    va_start(valist, component_count);
    int components[component_count];
    for (int i = 0; i < component_count; i++)
    {
      components[i] = va_arg(valist, int);
    }
    va_end(valist);
    unsigned int i = 1;

    for (Entity ID = 0; ID < manager->stack->top; ID++)
    {
      bool all = true;
      for (int ct = 0; ct < component_count; ct++)
      {
        if (manager->mask[ID][0] && manager->mask[ID][components[ct]])
        {
        }
        else
        {
          all = false;
          break;
        }
      }
      if (all)
      {
        arr[i] = ID;
        i++;
      }
    }
    if (i - 1)
    {
      arr[0] = i - 1;
      return realloc(arr, sizeof(Entity) * i);
    }
    free(arr);
    arr = NULL;
    return NULL;
  }

  return NULL;
}

void *return_component(EntityManager *manager, Entity EID, int component_id)
{
  if (manager->mask[EID][0])
  {
    ComponentVector *cv = manager->component_vectors[component_id];
    return cv->Cget(cv, EID);
  }
  else
    return NULL;
}

void clean_manager(EntityManager *manager)
{

  for (int c = 0; c < MAX_COMPONENTS; c++)
  {
    if (manager->component_vectors[c])
    {
      for (int i = 0; i < MAX_ENTITIES; i++)
      {
        destroy_entity(manager, i);
      }

      free(manager->component_vectors[c]->component_array);
      free(manager->component_vectors[c]);
    }
  }
  if (manager->stack)
    free(manager->stack);
  if (manager)
    free(manager);
}
