#ifndef __tExplosion_H__
#define __tExplosion_H__

typedef struct _tExplosion tExplosion;

#include "sprite_engine.h"

struct _tExplosion {
   tActor _;
   tSprite sprite;
   int stage;
   int delay;
};

tActor *CreateExplosion();
void    InitExplosion(tExplosion *explosion);

#endif

