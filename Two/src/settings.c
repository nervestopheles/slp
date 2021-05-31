#include <GL/glew.h>

#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT

#define MAX_VERTEX_MEMORY 64 * 1024
#define MAX_ELEMENT_MEMORY 64 * 1024

#include <nuklear.h>
#include <nuklear_sdl_gl3.h>

#define default_screen_gaps 12
#define default_gaps_step 5

const char *application_name = "Lab Two";
const char *font_path = "/usr/share/fonts/truetype/hack/Hack-Bold.ttf";

int screen_width = 800;
int screen_height = 600;

#define main_menu_gaps screen_gaps, screen_gaps,\
                       screen_width-screen_gaps*2+1,\
                       screen_height-screen_gaps*2+1

int screen_gaps = default_screen_gaps;
int gaps_step = default_gaps_step;

struct nk_rect main_menu;

struct Furnace {
    char name[35];
    int performance;
    float volume;
};

#define furnace_data \
    { "550-1"       ,   250 ,   10.0 },\
    { "550-2"       ,   250 ,   19.0 },\
    { "1012-3"      ,   700 ,   29.2 },\
    { "1012-4"      ,   700 ,   56.0 },\
    { "1012A-5"     ,  1000 ,   37.6 },\
    { "1012A-6"     ,  1000 ,   79.7 },\
    { "571-7"       ,   200 ,   19.0 },\
    { "1030-8"      ,   800 ,   73.8 },\
    { "CMK-158A-9"  ,   400 ,   41.0 },\
    { "СМК-158А-10" ,   350 ,   41.0 }

struct Furnace furnace[] = { furnace_data };
