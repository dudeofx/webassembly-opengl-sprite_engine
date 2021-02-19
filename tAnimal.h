#ifndef __tAnimal_H__
#define __tAnimal_H__

typedef struct _tAnimal tAnimal;

#include "sprite_engine.h"

struct _tAnimal {
   tActor _;
   tSprite sprite;
   int animal_type;
   int dx;
   int dy;
   float ds;
};

tActor *CreateAnimal(int animal_type);
void    InitAnimal(tAnimal *animal, int animal_type);

#endif
