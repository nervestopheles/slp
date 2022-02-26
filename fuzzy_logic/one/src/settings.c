#include <GL/glew.h>

#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

#include <nuklear.h>
#include <nuklear_sdl_gl3.h>

#define defaultBgColor 0.08, 0.08, 0.1
#define defaultNkPosition 6, 6, 385, winHeight-6*2
#define colorGraph_V 0.6, 0, 0
#define colorGraph_M 0, 0.6, 0
#define colorGraph_VM 0, 0.6, 0.6
#define colorForFill 0, 0.12, 0.16

#define _empty 0
#define _membership 1
#define _supplement 2
#define _intersection 3
#define _union 4
#define _amount 5
#define _differenceVM 6
#define _differenceMV 7
#define _multiplication 8

#define _compEqual 0
#define _compXinY 1
#define _compYinX 2

#define layoutSpacing 5
#define arrLength 7

#define defaultData \
    { "K/SQ 2"   , 0.3  , 110  }, \
    { "K/SQ 3"   , 0.9  , 200  }, \
    { "K/SQ 5"   , 4.5  , 380  }, \
    { "CM-243 V" , 4    , 550  }, \
    { "CM-489 B" , 8    , 1220 }, \
    { "K/SQ 7"   , 13.5 , 1230 }, \
    { "K/SQ 10"  , 38   , 2700 } 

struct obj { char name[12]; double V, M; };
struct bgColor { double r, g, b; };
struct glRegion { double xL, xR, yD, yU; };

const struct glRegion defaultGlRegion = { -3, arrLength+0.05-1, -0.01, 1.008 };

struct obj data[arrLength] = {defaultData};

const char *appName = "Lab One";
const char *fontPath = "/usr/share/fonts/truetype/hack/Hack-Bold.ttf";
const char *setsArr[] =  {"Capacity (V)", "Mass (M)"};

const double zoomWidthMax = 2*arrLength;
const double zoomWidthMin = 2;
const double cameraStepX = 0.1;
const double cameraStepY = 0.01;

const int graphLineWidth = 3;
const int graphPointSize = 8;
const int fontSize = 14;

const int winWidth = 1200;
const int winHeight = 800;

char *compStr; int compFlag;

int currentArr;
int drawSet;

int dataMessage;
int indexMessage;
int alphaMessage;
int comparisonMessage;

double alphaCut;

double minV, midV, maxV;
double minM, midM, maxM;

double memberArrV[arrLength], memberArrM[arrLength];
double supplementArrV[arrLength], supplementArrM[arrLength];

double nearArrV[arrLength], nearArrM[arrLength];
double linearFuzzyIndexV, linearFuzzyIndexM;
double quadroFuzzyIndexV, quadroFuzzyIndexM;
double fuzOneV, fuzTwoV, fuzOneM, fuzTwoM;
double koskoV, koskoM;

double intersectionArr[arrLength];
double unionArr[arrLength];
double limitedAmountArr[arrLength];
double differenceArr_VM[arrLength];
double differenceArr_MV[arrLength];
double multiplicationArr[arrLength];
