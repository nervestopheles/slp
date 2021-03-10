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

#define defaultBgColor 0.08, 0.08, 0.1
#define defaultNkPosition 6, 6, 385, winHeight-6*2

#define NK_IMPLEMENTATION
#define NK_SDL_GL3_IMPLEMENTATION

#include "../include/nuklear.h"
#include "../include/nuklear_sdl_gl3.h"

struct obj {
    char *name;
    double V, M;
};

struct bgColor {
    double r,g,b;
};

struct glRegion {
    double xL, xR, yD, yU;
};

const struct obj defaultData[] = 
{ 
    { "K/SQ 2"   , 0.3  , 110  },
    { "K/SQ 3"   , 0.9  , 200  },
    { "K/SQ 5"   , 4.5  , 380  },
    { "CM-243 V" , 4    , 550  },
    { "CM-489 B" , 8    , 1220 },
    { "K/SQ 7"   , 13.5 , 1230 },
    { "K/SQ 10"  , 38   , 2700 }
};

const struct glRegion defaultGlRegion = { -3, 6.05, -0.01, 1.008 };

const char *appName = "Lab One";
const char *fontPath = "/usr/share/fonts/truetype/hack/Hack-Bold.ttf";

const char *setsArr[] =  {"Capacity", "Mass"};

const int zoomBorderMin = 12;
const int zoomBorderMax = 8;
const double cameraStepX = 0.1;
const double cameraStepY = 0.01;

const int graphLineWidth = 3;
const int graphPointSize = 8;
const int fontSize = 14;
const int arrLength = 7; 

const int winWidth = 1200;
const int winHeight = 800;

const int _empty = 0;
const int _membership = 1;
const int _supplement = 2;
const int _intersection = 3;
const int _union = 4;
const int _amount = 5;
const int _difference = 6;
const int _multiplication = 7;
