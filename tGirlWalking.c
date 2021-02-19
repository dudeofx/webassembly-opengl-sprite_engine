#include <malloc.h>
#include <stdlib.h>

#include "tGirlWalking.h"

//--------------------------------------------------------------
static void UpdateGirlWalking(tActor *actor) {
   tGirlWalking *girl_walking = (tGirlWalking *) actor;

   girl_walking->frame++;

   girl_walking->sprite.i = (girl_walking->frame / 4) % 10;

   // every 128 frames (about 2 secs) flip her direction
   if ( ((girl_walking->frame / 128) & 1) == 0) {
      girl_walking->sprite.o |= _ENG_OPT_HFLIP;
   } else {
      girl_walking->sprite.o &= ~_ENG_OPT_HFLIP;
   }

   SubmitSprite(&(girl_walking->sprite));
}
//--------------------------------------------------------------
tActor *CreateGirlWalking() {
   tGirlWalking *tmp = NULL;

   tmp = malloc(sizeof(tGirlWalking));
   InitGirlWalking(tmp);

   return (tActor *) tmp;
}
//--------------------------------------------------------------
void InitGirlWalking(tGirlWalking *girl_walking) {
   InitActor((tActor *) girl_walking);

   girl_walking->_.x_pos = 320;
   girl_walking->_.y_pos = 320;
   girl_walking->_.UpdateCycle = UpdateGirlWalking;

   float x = (((float) girl_walking->_.x_pos) / 320.0f ) - 1.0f;
   float y = (((float) girl_walking->_.y_pos) / 320.0f ) - 1.0f;

   girl_walking->sprite.x = x;
   girl_walking->sprite.y = y;

   girl_walking->sprite.p = 0.0f;
   girl_walking->sprite.q = 0.0f;
   girl_walking->sprite.a = 0.0f;
   girl_walking->sprite.s = 3.0f;
   girl_walking->sprite.t = 1.0f;
   girl_walking->sprite.i = 0;
   girl_walking->sprite.o = 0;

   girl_walking->frame = 0;
}
//--------------------------------------------------------------

