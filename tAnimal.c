#include <stdlib.h>
#include <malloc.h>
#include "tAnimal.h"

//--------------------------------------------------------------
static void UpdateAnimal(tActor *actor) {
   tAnimal *animal = (tAnimal *) actor;

   animal->_.x_pos += animal->dx;
   if (animal->_.x_pos < 0) {
      animal->_.x_pos = 0;
      animal->dx = (rand() % 4) + 1;
   }
   if (animal->_.x_pos >= 640) {
      animal->_.x_pos = 639;
      animal->dx = -(rand() % 4) - 1;
   }

   animal->_.y_pos += animal->dy;
   if (animal->_.y_pos < 0) {
      animal->_.y_pos = 0;
      animal->dy = (rand() % 4) + 1;
   }
   if (animal->_.y_pos >= 640) {
      animal->_.y_pos = 639;
      animal->dy = -(rand() % 4) - 1;
   }

   animal->sprite.s += animal->ds;
   if (animal->sprite.s < 0.25f) {
      animal->sprite.s = 0.25f;
      animal->ds = 0.01f + ((float) (rand() % 10)) / 100.0f;
   }

   if (animal->sprite.s > 2.5f) {
      animal->sprite.s = 2.5f;
      animal->ds = -1.0f * (0.01f + ((float) (rand() % 10)) / 100.0f );
   }

   float x = (((float) animal->_.x_pos) / 320.0f ) - 1.0f;
   float y = (((float) animal->_.y_pos) / 320.0f ) - 1.0f;

   animal->sprite.x = x;
   animal->sprite.y = y;

   SubmitSprite(&(animal->sprite));
}
//--------------------------------------------------------------
tActor *CreateAnimal(int animal_type) {
   tAnimal *tmp = NULL;

   tmp = malloc(sizeof(tAnimal));
   InitAnimal(tmp, animal_type);

   return (tActor *) tmp;
}
//--------------------------------------------------------------
void InitAnimal(tAnimal *animal, int animal_type) {
   InitActor((tActor *) animal);

   animal->_.x_pos = rand() % 640;
   animal->_.y_pos = rand() % 640;
   animal->_.UpdateCycle = UpdateAnimal;
   animal->animal_type = animal_type;
   animal->dx = (rand() % 10) - 5;
   if (animal->dx == 0) animal->dx = 1;
   animal->dy = (rand() % 10) - 5;
   if (animal->dy == 0) animal->dy = 1;

   animal->ds = 0.01f + ((float) (rand() % 10)) / 100.0f;
   if ((rand() & 1) == 0) animal->ds *= -1.0f;

   animal->sprite.x = 0.0f;
   animal->sprite.y = 0.0f;
   animal->sprite.p = 0.0f;
   animal->sprite.q = 0.0f;
   animal->sprite.a = 0.0f;
   // as small as 1/4th to as big as 2.25X
   animal->sprite.s = 0.25f + (2.0f / ((float) (rand() % 10)) );
   animal->sprite.t = 1.0f;
   animal->sprite.i = 25 + animal_type; 
   animal->sprite.o = 0; 
}
//--------------------------------------------------------------

