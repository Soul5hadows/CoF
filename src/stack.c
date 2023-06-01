#include "stack.h"

void push(Stack *stack, unsigned int ID)
{
  if (stack->top == 0)
  {
    return;
  }

  stack->ID[--stack->top] = ID;
}

unsigned int pop(Stack *stack)
{

  if (stack->top != MAX_ENTITIES - 1)
  {
    return stack->ID[stack->top++];
  }
  return MAX_ENTITIES;
}

void Stack_Init(Stack *stack)
{
  stack->top = 0;
  Entity ID = 0;
  for (; ID < MAX_ENTITIES; ID++)
  {
    stack->ID[ID] = ID;
  }
  stack->pop = &pop;
  stack->push = push;
}
