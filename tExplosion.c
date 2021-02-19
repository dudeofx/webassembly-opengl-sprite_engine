#include <malloc.h>
#include <stdlib.h>

#include "tExplosion.h"

//--------------------------------------------------------------
static void UpdateExplosion(tActor *actor) {
   tExplosion *explosion = (tExplosion *) actor;

   if (explosion->delay > 0) {
      explosion->delay--;
      return;
   }

   if (explosion->stage <= 15) {
      explosion->sprite.s = (1.0f/15.0f) * ((float) explosion->stage);
   }

   if ((explosion->stage >= 16) &&  (explosion->stage <= 23)) {
      int txtr = 33 + (explosion->stage - 16);
      explosion->sprite.i = txtr;
      explosion->sprite.s = 1.0f + (1.0f/8.0f) * ((float) (explosion->stage - 16));
   }

   if (explosion->stage >= 24) {
      explosion->_.x_pos = rand() % 640;
      explosion->_.y_pos = rand() % 640;
      float x = (((float) explosion->_.x_pos) / 320.0f ) - 1.0f;
      float y = (((float) explosion->_.y_pos) / 320.0f ) - 1.0f;
      explosion->sprite.x = x;
      explosion->sprite.y = y;
      explosion->sprite.i = 33;
      explosion->stage = 0;
      explosion->delay = rand() % 60;
      return;
   }

   SubmitSprite(&(explosion->sprite));

   explosion->stage++;

}
//--------------------------------------------------------------
tActor *CreateExplosion() {
   tExplosion *tmp = NULL;

   tmp = malloc(sizeof(tExplosion));
   InitExplosion(tmp);

   return (tActor *) tmp;
}
//--------------------------------------------------------------
void InitExplosion(tExplosion *explosion) {
   InitActor((tActor *) explosion);

   explosion->_.x_pos = rand() % 640;
   explosion->_.y_pos = rand() % 640;
   explosion->_.UpdateCycle = UpdateExplosion;

   float x = (((float) explosion->_.x_pos) / 320.0f ) - 1.0f;
   float y = (((float) explosion->_.y_pos) / 320.0f ) - 1.0f;

   explosion->sprite.x = x;
   explosion->sprite.y = y;

   explosion->sprite.p = 0.0f;
   explosion->sprite.q = 0.0f;
   explosion->sprite.a = 0.0f;
   explosion->sprite.s = 1.0f;
   explosion->sprite.t = 1.0f;
   explosion->sprite.i = 33;
   explosion->sprite.o = 0;
   explosion->stage = 0;
   explosion->delay = rand() % 60;
}
//--------------------------------------------------------------

