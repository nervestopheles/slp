#include <GL/glew.h>

#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

#define colorGraph_V 0.6, 0, 0
#define colorGraph_M 0, 0.6, 0
#define colorGraph_VM 0, 0.6, 0.6
#define colorForFill 0, 0.1, 0.15

#define NK_IMPLEMENTATION
#define NK_SDL_GL3_IMPLEMENTATION

#include "../include/nuklear.h"
#include "../include/nuklear_sdl_gl3.h"

const char *appName = "Lab One";
const char *fontPath = "/usr/share/fonts/truetype/hack/Hack-Bold.ttf";

const int fontSize = 14;
const int arrLength = 7; 
const int pointSize = 8;
const int lineWidth = 3;

const int winWidth = 1200;
const int winHeight = 800;

const int _empty = 0;
const int _membership = 1;
const int _complement = 2;
const int _intersection = 3;
const int _union = 4;
const int _amount = 5;
const int _difference = 6;
const int _multiplication = 7;

struct obj {
    char *name;
    double V, M;
};

struct bgColor {
    double r,g,b;
};

struct glRegion
{
    double xL, xR, yD, yU;
};

struct nkPosition {
    int x1, y1, x2, y2;
};
