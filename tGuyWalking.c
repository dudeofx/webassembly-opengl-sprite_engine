#include <malloc.h>
#include <stdlib.h>
#include <math.h>

#include "tGuyWalking.h"

//--------------------------------------------------------------
static void UpdateGuyWalking(tActor *actor) {
   tGuyWalking *guy_walking = (tGuyWalking *) actor;

   guy_walking->frame++;

   float angle = ((float) (guy_walking->frame)) * 0.0174533;

   guy_walking->sprite.a = angle;

   guy_walking->_.x_pos = cos(angle + 1.5708) * 150.0f + 320.0f;
   guy_walking->_.y_pos = sin(angle + 1.5708) * 150.0f + 320.0f;

   float x = (((float) guy_walking->_.x_pos) / 320.0f ) - 1.0f;
   float y = (((float) guy_walking->_.y_pos) / 320.0f ) - 1.0f;

   guy_walking->sprite.x = x;
   guy_walking->sprite.y = y;

   guy_walking->sprite.i = 10 + (guy_walking->frame / 2) % 15;

   SubmitSprite(&(guy_walking->sprite));
}
//--------------------------------------------------------------
tActor *CreateGuyWalking() {
   tGuyWalking *tmp = NULL;

   tmp = malloc(sizeof(tGuyWalking));
   InitGuyWalking(tmp);

   return (tActor *) tmp;
}
//--------------------------------------------------------------
void InitGuyWalking(tGuyWalking *guy_walking) {
   InitActor((tActor *) guy_walking);

   guy_walking->_.x_pos = 320;
   guy_walking->_.y_pos = 320;
   guy_walking->_.UpdateCycle = UpdateGuyWalking;

   float x = (((float) guy_walking->_.x_pos) / 320.0f ) - 1.0f;
   float y = (((float) guy_walking->_.y_pos) / 320.0f ) - 1.0f;

   guy_walking->sprite.x = x;
   guy_walking->sprite.y = y;

   guy_walking->sprite.p = 0.0f;
   guy_walking->sprite.q = 1.0f;
   guy_walking->sprite.a = 0.0f;
   guy_walking->sprite.s = 2.0f;
   guy_walking->sprite.t = 1.0f;
   guy_walking->sprite.i = 10;
   guy_walking->sprite.o = _ENG_OPT_HFLIP;

   guy_walking->frame = 0;
}
//--------------------------------------------------------------

