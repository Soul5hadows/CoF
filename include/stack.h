#ifndef STACK_H
#define STACK_H

#include "shared.h"

typedef struct Stack Stack;
struct Stack
{
  Entity top;
  Entity ID[MAX_ENTITIES];

  //Function Pointers
  void (*push)(Stack *, unsigned int);
  unsigned int (*pop)(Stack *);
};

void Stack_Init(Stack *);

#endif
