#include "settings.c"
#include "reductions.c"

int main(void)
{
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
    );
    SDL_GLContext gl_ctx = SDL_GL_CreateContext(window); 

    glewInit();
    struct nk_context *nk_ctx = nk_sdl_init(window);

    SetFont(nk_ctx, font_path);
    glClearColor(0.1, 0.1, 0.1, 1);

    glClear(GL_COLOR_BUFFER_BIT); glFlush();
    SDL_GL_SwapWindow(window);

    SDL_Delay(100);
    Hello(window, nk_ctx);

    /* ------- Main Loop  ------- */
    while (GetEvent(window, nk_ctx))
    {
        Drawing(window, nk_ctx);
    };

    SDL_GL_DeleteContext(gl_ctx);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("\nGoodbye.\n");
    return 0;
}
