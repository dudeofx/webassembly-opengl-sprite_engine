#ifndef __tGuyWalking_H__
#define __tGuyWalking_H__

typedef struct _tGuyWalking tGuyWalking;

#include "sprite_engine.h"

struct _tGuyWalking {
   tActor _;
   tSprite sprite;
   int frame;
};

tActor *CreateGuyWalking();
void    InitGuyWalking(tGuyWalking *guy_walking);

#endif

