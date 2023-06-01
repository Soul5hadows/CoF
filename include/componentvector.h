#ifndef COMPONENTVECTOR_H
#define COMPONENTVECTOR_H

#include <stdlib.h>
#include "shared.h"

typedef struct ComponentVector ComponentVector;
struct ComponentVector
{
	void **component_array;
	Entity active;
	Entity capacity;
	void (*Cadd)(ComponentVector *, void *, Entity);
	void *(*Cget)(ComponentVector *, Entity);
	void (*Cremove)(ComponentVector *, Entity);
};
void Init_Component_Vector(ComponentVector *);

#endif
