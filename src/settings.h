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

const int arrLength = 7; 

struct obj {
    char *name;
    double V, M;
};

struct bgColor {
    double r,g,b,a;
};

