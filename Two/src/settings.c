#include <GL/glew.h>

#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT

#define MAX_VERTEX_MEMORY 1024 * 1024
#define MAX_ELEMENT_MEMORY 1024 * 1024

#include <nuklear.h>
#include <nuklear_sdl_gl3.h>

#define default_screen_gaps 10
#define default_gaps_step 5

const char *application_name = "Lab Two";
const char *font_path = "/usr/share/fonts/truetype/hack/Hack-Bold.ttf";

int screen_width = 780;
int screen_height = 920;

int screen_gaps = default_screen_gaps;
int gaps_step = default_gaps_step;

int matrix_width = 0;

struct nk_rect main_menu;

struct {
    char name[20];
    int performance;
    float volume;
} furnace[] = {
    { "550-1"       ,  250 ,  10.0 },
    { "550-2"       ,  250 ,  19.0 },
    { "1012-3"      ,  700 ,  29.2 },
    { "1012-4"      ,  700 ,  56.0 },
    { "1012A-5"     , 1000 ,  37.6 },
    { "1012A-6"     , 1000 ,  79.7 },
    { "571-7"       ,  200 ,  19.0 },
    { "1030-8"      ,  800 ,  73.8 },
    { "CMK-158A-9"  ,  400 ,  41.0 },
    { "СМК-158А-10" ,  350 ,  41.0 }
};

struct Properties {
    char *ref_status;
    char *sym_status;
    char *trs_status;
};

#define REFLECTIVE     "    Reflective"
#define NON_REFLECTIVE "    Non reflective"
#define ANTIREFLECTIVE "    Antireflective"

#define SYMMETRIC      "    Symmetric"
#define NON_SYMMETRIC  "    Non symmetric"

#define TRANSITIVE     "    Transitive"
#define NON_TRANSITIVE "    Non transitive"

#define main_menu_gaps \
    screen_gaps, screen_gaps,\
    screen_width-screen_gaps*2+1,\
    screen_height-screen_gaps*2+1

#define furnace_count 10

float min_perf = 50; float max_perf = 500;
float performance_stat[furnace_count];
float performance_diff[furnace_count][furnace_count];
float performance_membership[furnace_count][furnace_count];
struct Properties performance_properties;
int perf_src_len[furnace_count];
char perf_src_buf[furnace_count][20];

float min_vol = 0; float max_vol = 35;
float volume_stat[furnace_count];
float volume_diff[furnace_count][furnace_count];
float volume_membership[furnace_count][furnace_count];
struct Properties volume_properties;
int volu_src_len[furnace_count];
char volu_src_buf[furnace_count][20];
