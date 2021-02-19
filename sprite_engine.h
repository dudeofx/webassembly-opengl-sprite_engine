#ifndef __SPRITE_ENGINE_H__
#define __SPRITE_ENGINE_H__

#define _ENG_OPT_HFLIP  1
#define _ENG_OPT_VFLIP  2

#define MAX_SPRITES       1500
#define MAX_TRIANGLES     (MAX_SPRITES*2)
// each triangle has 3 vertices and each vertex has 4 floats
#define VERTEX_MAX_COUNT  (MAX_TRIANGLES*3*4)
#define VERTEX_BUFF_SIZE  (VERTEX_MAX_COUNT*sizeof(GLfloat))


typedef struct _tSprite tSprite;
struct _tSprite {
   float x; // xpos
   float y; // ypos
   float p; // x hot spot
   float q; // y hot spot
   float a; // angle of ration over xy plane
   float s; // scale
   float t; // transparency
   int   i; // texture index
   int   o; // options
};

typedef struct _tActor tActor;
struct _tActor {
   int uid;
   int x_pos;
   int y_pos;
   void (*UpdateCycle)(tActor *);
   tActor *next;
};

void InitActor(tActor *actor);
void SubmitSprite(tSprite *sprite);

#endif
