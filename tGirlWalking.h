#ifndef __tGirlWalking_H__
#define __tGirlWalking_H__

typedef struct _tGirlWalking tGirlWalking;

#include "sprite_engine.h"

struct _tGirlWalking {
   tActor _;
   tSprite sprite;
   int frame;
};

tActor *CreateGirlWalking();
void    InitGirlWalking(tGirlWalking *girl_walking);

#endif


