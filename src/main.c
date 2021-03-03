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

void calculator(struct nk_context *ctx);

int main(void)
{
    /* --------------- Vars --------------- */
    SDL_Window *window;
    SDL_GLContext glContext;
    SDL_Event evt;

    struct nk_context *ctx;
    struct nk_colorf bgColor;
    
    int winWidth = appWidth;
    int winHeight = appHeight;

    int quit = 0;

    bgColor.a = 1.0f;
    bgColor.r = 0.10f;
    bgColor.g = 0.10f;
    bgColor.b = 0.10f; 

    /* --------------- Setup --------------- */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    window = SDL_CreateWindow(
            appName, 
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            winWidth, winHeight, 
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    glContext = SDL_GL_CreateContext(window);
    SDL_GetWindowSize(window, &winWidth, &winHeight);

    glViewport(0, 0, winWidth, winHeight);
    glewExperimental = 1;
    glewInit();

    ctx = nk_sdl_init(window);
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    struct nk_font *font = nk_font_atlas_add_from_file(atlas, fontPath, 12, 0);
    nk_sdl_font_stash_end();
    nk_style_set_font(ctx, &font->handle);

    /* --------------- Loop --------------- */
    while (!quit) {
        nk_input_begin(ctx);
        while(SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) goto exit;
            nk_sdl_handle_event(&evt);
        } nk_input_end(ctx);

        calculator(ctx);

        SDL_GetWindowSize(window, &winWidth, &winHeight);
        glViewport(0, 0, winWidth, winHeight);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);

        nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
        SDL_GL_SwapWindow(window);
    }

    /* --------------- Exit --------------- */
exit:
    nk_sdl_shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("Goodbye.\n");
    return 0;
}

void calculator(struct nk_context *ctx)
{
    if (nk_begin(ctx, "Calculator", nk_rect(0, 0, appWidth, appHeight), NK_WINDOW_NO_SCROLLBAR))
    {
        static int set = 0, prev = 0, op = 0;
        static const char numbers[] = "789456123";
        static const char ops[] = "+-*/";
        static double a = 0, b = 0;
        static double *current = &a;

        size_t i = 0;
        int solve = 0;
        int len; char buffer[256];
        nk_layout_row_dynamic(ctx, 40, 1);
        len = snprintf(buffer, 256, "%.2f", *current);
        nk_edit_string(ctx, NK_EDIT_SIMPLE, buffer, &len, 255, nk_filter_float);
        buffer[len] = 0;
        *current = atof(buffer);

        nk_layout_row_dynamic(ctx, 35, 4);
        for (i = 0; i < 16; ++i) {
            if (i >= 12 && i < 15) {
                if (i > 12) continue;
                if (nk_button_label(ctx, "C")) {
                    a = b = op = 0; current = &a; set = 0;
                } if (nk_button_label(ctx, "0")) {
                    *current = *current*10.0f; set = 0;
                } if (nk_button_label(ctx, "=")) {
                    solve = 1; prev = op; op = 0;
                }
            } else if (((i+1) % 4)) {
                if (nk_button_text(ctx, &numbers[(i/4)*3+i%4], 1)) {
                    *current = *current * 10.0f + numbers[(i/4)*3+i%4] - '0';
                    set = 0;
                }
            } else if (nk_button_text(ctx, &ops[i/4], 1)) {
                if (!set) {
                    if (current != &b) {
                        current = &b;
                    } else {
                        prev = op;
                        solve = 1;
                    }
                }
                op = ops[i/4];
                set = 1;
            }
        }
        if (solve) {
            if (prev == '+') a = a + b;
            if (prev == '-') a = a - b;
            if (prev == '*') a = a * b;
            if (prev == '/') a = a / b;
            current = &a;
            if (set) current = &b;
            b = 0; set = 0;
        }
    }
    nk_end(ctx);
}
