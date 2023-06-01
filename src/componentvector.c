#include "componentvector.h"

void Cadd(ComponentVector *component_vector, void *component_type, Entity EID)
{
  if (component_vector->active != component_vector->capacity)
    {
      component_vector->component_array[EID] = component_type;
      component_vector->active++;
    }
}

void* Cget(ComponentVector *component_vector, Entity EID)
{
  return component_vector->component_array[EID];
}

void Cremove(ComponentVector *component_vector, Entity EID)
{
  if (component_vector->active)
    {
      free(component_vector->component_array[EID]);
      component_vector->component_array[EID] = NULL;
      component_vector->active--;
    }
}

void Init_Component_Vector(ComponentVector *component_vector)
{
  component_vector->active = 0;
  component_vector->capacity = MAX_ENTITIES;
  component_vector->Cadd = Cadd;
  component_vector->Cget = Cget;
  component_vector->Cremove = Cremove;
}
