#ifndef COMPONENTS_H
#define COMPONENTS_H
#include<stdbool.h>

typedef enum
{
  INPUT = 1, SPRITE, STATE, STATUS, TRANSFORM, POSITION, PHYSICS, PHYSICAL, CHEMICAL, AUDIO, VISUAL, AI, INTERACTION
}COMPONENT_LIST;

typedef struct
{
  double x;
  double y;
  double z;
}VEC3D;

typedef struct
{
  VEC3D direction;
  double magnitude;
}Acceleration;

typedef struct
{
  VEC3D direction;
  double magnitude;
}Velocity;

typedef struct
{
  char prev_inputs[5];
  char input;	
}Input;

typedef struct
{
  unsigned int length;
  unsigned int width;
  char sprite;
}Sprite;

typedef struct
{
  bool active[20];
}State;

typedef struct
{
  char name[20];
  char race [20];
  char species[20];
  char class[20];
  int age;
}Status;

typedef struct
{
  Acceleration acceleration;
  Velocity velocity;
}Transform;

typedef struct
{
  VEC3D coordinate;
  VEC3D orientation;
  VEC3D scale;
}Position;

typedef struct
{

}Physics;

typedef struct
{

}Audio;

typedef struct
{

}Physical;

typedef struct
{

}Visual;

typedef struct
{

}Ai;

typedef struct
{

}Interaction;

#endif
