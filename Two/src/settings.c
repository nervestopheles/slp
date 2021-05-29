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

const char *application_name = "Lab Two";
const char *font_path = "/usr/share/fonts/truetype/hack/Hack-Bold.ttf";

int screen_width = 650;
int screen_height = 450;
int screen_gaps = 560;
