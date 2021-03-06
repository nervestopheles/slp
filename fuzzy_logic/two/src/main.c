#include "settings.c"
#include "math.c"
#include "engine.c"
#include "gui.c"

int main(void)
{
    GetPerformanceFurnaceStat(performance_stat);
    InitDataLength(performance_stat, perf_src_buf, perf_src_len);
    min_perf_len = sprintf(min_perf_buf, "%5.4f", min_perf);
    max_perf_len = sprintf(max_perf_buf, "%5.4f", max_perf);

    GetVolumeFurnaceStat(volume_stat);
    InitDataLength(volume_stat, volu_src_buf, volu_src_len);
    min_vol_len = sprintf(min_vol_buf, "%5.4f", min_vol);
    max_vol_len = sprintf(max_vol_buf, "%5.4f", max_vol);

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

    char font_size = 15;
    SetFont(nk_ctx, font_path, font_size);
    glClearColor(0.1, 0.1, 0.1, 1);

    UpdateMenuPosition(&main_menu, main_menu_gaps);
    Intro(window, nk_ctx);

    /* ------- Main Loop ------- */
    while (GetEvent(window, nk_ctx))
    {
        Render(window, nk_ctx);
    };

    SDL_GL_DeleteContext(gl_ctx);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("\nGoodbye.\n\n");
    return 0;
}
