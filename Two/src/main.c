#include "settings.c"
#include "reductions.c"
#include "logic.c"

int main(void)
{
    const int furnace_count = sizeof(furnace)/sizeof(furnace[0]);

    int performance_stat[furnace_count][furnace_count];
    int volume_stat[furnace_count][furnace_count];

    GetPerformanceDiff(furnace_count, performance_stat);
    GetVolumeDiff(furnace_count, volume_stat);

    printf("Performance diff:\n");
    PrintingSquarArray(furnace_count, performance_stat);
    printf("\nVolume diff:\n");
    PrintingSquarArray(furnace_count, volume_stat);

    /* ------- Setup ------- */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window *window = SDL_CreateWindow(
        application_name,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screen_width,
        screen_height,
        SDL_WINDOW_SHOWN
        | SDL_WINDOW_OPENGL
        | SDL_WINDOW_RESIZABLE
        | SDL_RENDERER_ACCELERATED
        | SDL_RENDERER_PRESENTVSYNC
    );
    SDL_GLContext gl_ctx = SDL_GL_CreateContext(window); 

    glewInit();
    struct nk_context *nk_ctx = nk_sdl_init(window);

    SetFont(nk_ctx, font_path);
    glClearColor(0.1, 0.1, 0.1, 1);

    Intro(window, nk_ctx);

    /* ------- Main Loop ------- */
    while (GetEvent(window, nk_ctx))
    {
        Render(window, nk_ctx);
    };

    SDL_GL_DeleteContext(gl_ctx);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("\nGoodbye.\n");
    return 0;
}
