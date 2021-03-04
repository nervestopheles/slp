#include <GL/glew.h>

#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

#define colorGraph_V 0.75, 0, 0
#define colorGraph_M 0, 0.75, 0
#define colorGraph_VM 0, 0.5, 0.5
#define colorForFill 0, 0.2, 0.2

#define setGlRegion -3, 6.05, -0.01, 1.008

#define NK_IMPLEMENTATION
#define NK_SDL_GL3_IMPLEMENTATION

#include "../include/nuklear.h"
#include "../include/nuklear_sdl_gl3.h"

const char *appName = "Lab One";
const char *fontPath = "/usr/share/fonts/truetype/hack/Hack-Bold.ttf";

const int winWidth = 1200;
const int winHeight = 800;

const int arrLength = 7; 

const int _empty = 0;
const int _membership = 1;
const int _complement = 2;
const int _intersection = 3;
const int _union = 4;

struct obj {
    char *name;
    double V, M;
};

struct bgColor {
    double r,g,b;
};

