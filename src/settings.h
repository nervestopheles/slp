#include <GL/glew.h>

#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

#define NK_IMPLEMENTATION
#define NK_SDL_GL3_IMPLEMENTATION

#include "../include/nuklear.h"
#include "../include/nuklear_sdl_gl3.h"

const char *appName = "Lab One";
const char *fontPath = "/usr/share/fonts/truetype/hack/Hack-Bold.ttf";

const int appWidth = 600;
const int appHeight = 600;

/* 
    const int arrLength = 7; 

    struct obj {
        char *name;
        double V;
        double M;
    };

    struct obj Data[] = {
        { "K/SQ 2"   , 0.3  , 110   }, 
        { "K/SQ 3"   , 0.9  , 200   }, 
        { "K/SQ 5"   , 4.5  , 380   }, 
        { "CM-243 V" , 4    , 550   }, 
        { "CM-489 B" , 8    , 1220  }, 
        { "K/SQ 7"   , 13.5 , 1230  }, 
        { "K/SQ 10"  , 38   , 2700  }
    };
*/
