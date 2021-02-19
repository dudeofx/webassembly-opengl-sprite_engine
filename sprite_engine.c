#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES2/gl2.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "sprite_engine.h"
#include "tAnimal.h"
#include "tExplosion.h"
#include "tGirlWalking.h"
#include "tGuyWalking.h"


GLfloat sprite_template[] = {
//    x,     y,      u,     v,
  -1.0f,  1.0f,   0.0f,  0.0f,
  -1.0f, -1.0f,   0.0f,  1.0f,
   1.0f,  1.0f,   1.0f,  0.0f,

   1.0f,  1.0f,   1.0f,  0.0f,
   1.0f, -1.0f,   1.0f,  1.0f,
  -1.0f, -1.0f,   0.0f,  1.0f,
};

tSprite sprite_buffer[MAX_SPRITES];
int sprite_count;

GLfloat vertex_buffer[VERTEX_MAX_COUNT];
int vertex_count = 0;

tActor *acting_cast = NULL;

const GLchar *vertex_shader_source = 
	 "attribute vec2 aVertex;"
	 "attribute vec2 aTexel;"

	 "varying vec2 vTexel;"

   "void main() {"
	 "   vTexel = aTexel;"
	 "   gl_Position = vec4(aVertex, 0.0, 1.0);"
	 "}";
		
const GLchar *fragment_shader_source =
	 "precision mediump float;"

	 "varying vec2 vTexel;"

	 "uniform sampler2D uTexmap;"

	 "void main() {"
	 "   gl_FragColor = texture2D(uTexmap, vec2(vTexel.s, vTexel.t));"
	 "}";

   GLuint   vbo;
   GLint    handle_aVertex;
   GLint    handle_aTexel;
   GLint    handle_uTexmap;
   GLuint   texture_handle[1];

//-------------------------------------------------------------------------------
void DummyUpdateCycle(tActor *actor) { };
//-------------------------------------------------------------------------------
void InitActor(tActor *actor) {
   static int uid = 0x1000;

   actor->uid = uid++;
   actor->x_pos = 50;
   actor->y_pos = 50;
   actor->UpdateCycle = DummyUpdateCycle;
   actor->next = NULL;
}
//-------------------------------------------------------------------------------
void CommissionActor(tActor *actor) {
   if (acting_cast == NULL) {
      acting_cast = actor;
   } else {
      tActor *mark = acting_cast;
      while (mark->next != NULL) mark = mark->next;
      mark->next = actor;
   }
}
//-------------------------------------------------------------------------------
void SubmitSprite(tSprite *sprite) {
   if (sprite_count >= MAX_SPRITES) return;

   memcpy(sprite_buffer + sprite_count, sprite, sizeof(tSprite));
   sprite_count++;
}
//-------------------------------------------------------------------------------
void InitScene() {
// don't be afraid to uncomment the line below to produce 800 animal sprites
// if you want to see even more be sure to increase MAX_SPRITES up above

// for (int j = 0; j < 100; j++)
   for (int i = 0; i < 8; i++) {
      tActor *actor = (tActor *) CreateAnimal(i);
      CommissionActor(actor);
   }

   CommissionActor((tActor *) CreateGirlWalking());

   CommissionActor((tActor *) CreateGuyWalking());

   for (int i = 0; i < 4; i++) {
      tActor *actor = (tActor *) CreateExplosion();
      CommissionActor(actor);
   }

}
//-------------------------------------------------------------------------------
void UpdateScene() {
   sprite_count = 0;

   tActor *mark = acting_cast;
   while (mark != NULL) {
      mark->UpdateCycle(mark);
      mark = mark->next;
   }
}
//-------------------------------------------------------------------------------
void ComputeVertices() {
   vertex_count = 0;
   for (int i = 0; i < sprite_count; i++) {
      for (int j = 0; j < 6; j++) {
         float x = (sprite_template[j*4] + sprite_buffer[i].p) / 8.0f;
         float y = (sprite_template[j*4+1] + sprite_buffer[i].q) / 8.0f;

         float u = sprite_template[j*4+2] / 8.0f;
         if ((sprite_buffer[i].o & _ENG_OPT_HFLIP) == _ENG_OPT_HFLIP) u = (1.0f / 8.0f) - u;
          
         float v = sprite_template[j*4+3] / 8.0f;
         if ((sprite_buffer[i].o & _ENG_OPT_VFLIP) == _ENG_OPT_VFLIP) v = (1.0f / 8.0f) - v;

         x *= sprite_buffer[i].s;
         y *= sprite_buffer[i].s;
         float rx = cos(sprite_buffer[i].a)*x - sin(sprite_buffer[i].a)*y;
         float ry = sin(sprite_buffer[i].a)*x + cos(sprite_buffer[i].a)*y;

         float tx = rx + sprite_buffer[i].x;
         float ty = ry + sprite_buffer[i].y;

         int txtr = sprite_buffer[i].i;

         vertex_buffer[vertex_count++] = tx;
         vertex_buffer[vertex_count++] = ty;
         vertex_buffer[vertex_count++] = u + ((float) (txtr % 8)) / 8.0f;
         vertex_buffer[vertex_count++] = v + ((float) (txtr / 8)) / 8.0f;
      }
   }
}
//-------------------------------------------------------------------------------
void OnDrawFrame() {
   static int frame_count = 0;
   frame_count++;

   glClearColor(0.339f, 0.492f, 0.561f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);

   UpdateScene();
   ComputeVertices();
   glBufferData(GL_ARRAY_BUFFER, vertex_count*4*sizeof(GLfloat), vertex_buffer, GL_STATIC_DRAW);

   glDrawArrays(GL_TRIANGLES, 0, vertex_count/4);
}
//-------------------------------------------------------------------------------
void LoadTexture() {
   int w, h;
   char *img_data;

   img_data = emscripten_get_preloaded_image_data("assets/sprite_sheet00.png", &w, &h);
   glGenTextures(1, texture_handle);

   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, texture_handle[0]);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
   free(img_data);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
//-------------------------------------------------------------------------------
void InitWebGLStuff() {
   EmscriptenWebGLContextAttributes attr;
   emscripten_webgl_init_context_attributes(&attr);

   // a context is required to use the WebGL API
   EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context("my_canvas", &attr);

   // binds the WebGL API to the context
   emscripten_webgl_make_context_current(ctx);
   emscripten_set_canvas_element_size("my_canvas", 640, 640);

   glViewport(0, 0, 640, 640);

   glEnable(GL_BLEND);
   glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);

   GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
   glCompileShader(vertex_shader);

   GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
   glCompileShader(fragment_shader);

   GLuint shader_program = glCreateProgram();
   glAttachShader(shader_program, vertex_shader);
   glAttachShader(shader_program, fragment_shader);
   glLinkProgram(shader_program);
   glUseProgram(shader_program); 

   handle_aVertex = glGetAttribLocation(shader_program, "aVertex");
   handle_aTexel = glGetAttribLocation(shader_program, "aTexel");
   handle_uTexmap = glGetUniformLocation(shader_program, "uTexmap");

   LoadTexture();

   glVertexAttribPointer(handle_aVertex, 2, GL_FLOAT, GL_FALSE, sizeof(float)*4, 0);
   glEnableVertexAttribArray(handle_aVertex);   

   glVertexAttribPointer(handle_aTexel, 2, GL_FLOAT, GL_FALSE, sizeof(float)*4, (void *)(2*sizeof(float)));
   glEnableVertexAttribArray(handle_aTexel);   

   glUniform1i(handle_uTexmap, 0);
}
//-------------------------------------------------------------------------------
int main() {

   InitWebGLStuff();

   InitScene();

   emscripten_set_main_loop(OnDrawFrame, 0, 1);

   return 0;
}
//-------------------------------------------------------------------------------

