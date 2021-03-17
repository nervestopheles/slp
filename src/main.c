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

    int drawSet = 0;
    int alphaMessage = 0;
    double alphaCut = 0;

    struct nk_context *ctx;
    struct glRegion camera = defaultGlRegion;
    struct bgColor bg = {defaultBgColor};

    /* --------------- Setup --------------- */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow(
            appName, 
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            winWidth, winHeight, 
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    glContext = SDL_GL_CreateContext(window);

    glewInit();
    gluOrtho2D(camera.xL, camera.xR, camera.yD, camera.yU);
    glEnable(GL_POINT_SMOOTH);

    glClearColor(bg.r, bg.g, bg.b, 1);

    ctx = nk_sdl_init(window);
    struct nk_font_atlas *atlas;

    nk_sdl_font_stash_begin(&atlas);
    struct nk_font *font = nk_font_atlas_add_from_file(
        atlas, fontPath, fontSize, 0);
    nk_sdl_font_stash_end();

    nk_style_set_font(ctx, &font->handle);
    nk_sdl_render(NK_ANTI_ALIASING_ON, 
        MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);

    /* --------------- Loop --------------- */
    while (PollEvent(&camera, ctx, evt))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if (drawSet == _membership) {
            DrawGrid();
            DrawGraph(arrLength, memberArrV, colorGraph_V);
            DrawGraph(arrLength, memberArrM, colorGraph_M);
        } else if (drawSet == _supplement) {
            DrawGrid();
            DrawGraph(arrLength, supplementArrV, colorGraph_V);
            DrawGraph(arrLength, supplementArrM, colorGraph_M);
        } else if (drawSet == _intersection) {
            FillGraph(arrLength, intersectionArr, colorForFill);
            DrawGrid();
            DrawGraph(arrLength, memberArrV, colorGraph_V);
            DrawGraph(arrLength, memberArrM, colorGraph_M);
            DrawGraph(arrLength, intersectionArr, colorGraph_VM);
        } else if (drawSet == _union) {
            FillGraph(arrLength, unionArr, colorForFill);
            DrawGrid();
            DrawGraph(arrLength, memberArrV, colorGraph_V);
            DrawGraph(arrLength, memberArrM, colorGraph_M);
            DrawGraph(arrLength, unionArr, colorGraph_VM);
        } else if (drawSet == _amount) {
            FillGraph(arrLength, limitedAmountArr, colorForFill);
            DrawGrid();
            DrawGraph(arrLength, memberArrV, colorGraph_V);
            DrawGraph(arrLength, memberArrM, colorGraph_M);
            DrawGraph(arrLength, limitedAmountArr, colorGraph_VM);
        } else if (drawSet == _differenceVM) {
            FillGraph(arrLength, differenceArr_VM, colorForFill);
            DrawGrid();
            DrawGraph(arrLength, memberArrV, colorGraph_V);
            DrawGraph(arrLength, supplementArrM, colorGraph_M);
            DrawGraph(arrLength, differenceArr_VM, colorGraph_VM);
        } else if (drawSet == _differenceMV) {
            FillGraph(arrLength, differenceArr_MV, colorForFill);
            DrawGrid();
            DrawGraph(arrLength, supplementArrV, colorGraph_V);
            DrawGraph(arrLength, memberArrM, colorGraph_M);
            DrawGraph(arrLength, differenceArr_MV, colorGraph_VM);
        } else if (drawSet == _multiplication) {
            FillGraph(arrLength, multiplicationArr, colorForFill);
            DrawGrid();
            DrawGraph(arrLength, memberArrV, colorGraph_V);
            DrawGraph(arrLength, memberArrM, colorGraph_M);
            DrawGraph(arrLength, multiplicationArr, colorGraph_VM);
        } else DrawGrid();

        MainMenu(ctx, &drawSet, &alphaMessage, &alphaCut, &currentArr);

        if (alphaMessage) {
            if (currentArr == 0) 
                AlphaMessage(ctx, &alphaMessage, memberArrV, alphaCut);
            else if (currentArr == 1)
                AlphaMessage(ctx, &alphaMessage, memberArrM, alphaCut);
        }

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
