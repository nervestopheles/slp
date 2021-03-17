#include "settings.h"
#include "math.c"
#include "calculation.c"
#include "graphics.c"

int main(void) 
{
    /* --------------- Sets Vars --------------- */
    currentArr = 0;
    minV = 1, maxV = 12; midV = (minV + maxV) / 2;
    minM = 300, maxM = 1200; midM = (minM + maxM) / 2;

    /* --------------- Graphics Vars --------------- */
    SDL_Window *window;
    SDL_GLContext glContext;
    SDL_Event evt;

    drawSet = 0;
    dataMessage = 0;
    alphaMessage = 0;
    indexMessage = 0;
    alphaCut = 0;

    struct nk_context *ctx;
    struct glRegion camera = defaultGlRegion;
    struct bgColor bg = {defaultBgColor};

    /* --------------- Setup --------------- */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow(
            appName, 
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            winWidth, winHeight, 
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN 
                              | SDL_WINDOW_RESIZABLE);
    glContext = SDL_GL_CreateContext(window);

    glewInit();
    ctx = nk_sdl_init(window);

    gluOrtho2D(camera.xL, camera.xR, camera.yD, camera.yU);
    glEnable(GL_POINT_SMOOTH);
    glClearColor(bg.r, bg.g, bg.b, 1);

    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    struct nk_font *font = nk_font_atlas_add_from_file(
        atlas, fontPath, fontSize, 0);
    nk_sdl_font_stash_end();
    nk_style_set_font(ctx, &font->handle);

    /* --------------- Loop --------------- */
    while (PollEvent(&camera, ctx, evt))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        GraphRenderingCondition(drawSet);
        MainMenu(ctx);
        Messages(ctx);

        glFlush();
        nk_sdl_render(NK_ANTI_ALIASING_ON, 
            MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
        SDL_GL_SwapWindow(window);
    }

    /* --------------- Exit --------------- */
    nk_sdl_shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("\nGoodbye.\n");
    return 0;
}
