#ifndef COMPONENTS_H
#define COMPONENTS_H
#include<stdbool.h>

typedef enum
{
  INPUT = 1, SPRITE, STATE, STATUS, TRANSFORM, POSITION, PHYSICS, CHEMICAL, AUDIO, PHYSICAL, VISUAL, AI, INTERACTION
}COMPONENT_LIST;

/*
INPUT- Only the player has this. It deals with device input. SPRITE- Dictates the visual representation of an entity. Works well with the state component. STATE- Stores an entity's current action, animation, and behaviour.
STATUS- Tracks the abstract concept of an entity, its class, attributes, race, information, etc. TRANSFORM- Stores position data and provides the ability to move and to be moved. Pairs with the physics component with the rigid flag.
PHYSICS- Allows the entity to be influenced by the physics system. CHEMICAL- Provides the chemical properties of an entity and its ability to have chemical reactions. Perfect for alchemy.
AUDIO- Adds the ability to both perceive and create sound with flags. PHYSICAL- Has information about the owner's material and its ability to sense physically. VISUAL- An entity's capability to see and be seen, with the use of flags.
AI- Adds the ability to be controlled by the AI system. INTERACTION- The ability of an entity to interact with its enviroment and with others.
*/
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
