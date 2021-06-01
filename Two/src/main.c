#include "settings.c"
#include "engine.c"
#include "math.c"
#include "gui.c"

int main(void)
{
    const int furnace_count = sizeof(furnace)/sizeof(furnace[0]);

    /* ------- Performance ------- */
    float performance_stat[furnace_count][furnace_count];
    GetPerformanceFurnaceDiff(furnace_count, performance_stat);

    float min_perf = 50; float max_perf = 500;
    float performance_membership[furnace_count][furnace_count];
    GetPerformanceMembership(min_perf, max_perf, furnace_count, 
        performance_stat, performance_membership);

    struct Properties performance_properties = {
        ReflectiveStatus(furnace_count, performance_membership),
        SymmetricStatus(furnace_count, performance_membership),
        TransitiveStatus(furnace_count, performance_membership)
    };

    printf("Performance diff:\n");
    PrintingSquarArray(furnace_count, performance_stat);

    printf("\nPerformance Membership:\n");
    PrintingSquarArray(furnace_count, performance_membership);

    printf("\nPerformance Properties:\n");
    printf("    Ref status code: %#x\n", performance_properties.ref_status);
    printf("    Sym status code: %#x\n", performance_properties.sym_status);
    printf("    Trs status code: %#x\n", performance_properties.trs_status);

    /* ------- Volume ------- */
    float volume_stat[furnace_count][furnace_count];
    GetVolumeFurnaceDiff(furnace_count, volume_stat);

    float min_vol = 0; float max_vol = 35;
    float volume_membership[furnace_count][furnace_count];
    GetVolumeMembership(min_vol, max_vol, furnace_count,
        volume_stat, volume_membership);

    struct Properties volume_properties = {
        ReflectiveStatus(furnace_count, volume_membership),
        SymmetricStatus(furnace_count, volume_membership),
        TransitiveStatus(furnace_count, volume_membership)
    };

    printf("\nVolume diff:\n");
    PrintingSquarArray(furnace_count, volume_stat);
    printf("\nVolume Membership:\n");
    PrintingSquarArray(furnace_count, volume_membership);

    printf("\nVolume Properties:\n");
    printf("    Ref status code: %#x\n", volume_properties.ref_status);
    printf("    Sym status code: %#x\n", volume_properties.sym_status);
    printf("    Trs status code: %#x\n", volume_properties.trs_status);

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

    char font_size = 60;
    SetFont(nk_ctx, font_path, font_size);
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

    printf("\nGoodbye.\n\n");
    return 0;
}
