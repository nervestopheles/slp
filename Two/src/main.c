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

    /* ------- Main Loop  ------- */
    while (GetEvent(window, nk_ctx))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        nk_begin(nk_ctx, "",
            nk_rect(gaps, gaps,
                screen_width-gaps*2+1,
                screen_height-gaps*2+1),
            NK_WINDOW_BORDER
            | NK_WINDOW_NO_SCROLLBAR
            | NK_WINDOW_BACKGROUND);
        nk_end(nk_ctx);

        nk_sdl_render(
            NK_ANTI_ALIASING_OFF,
            MAX_VERTEX_MEMORY,
            MAX_ELEMENT_MEMORY);
        SDL_GL_SwapWindow(window);
    };

    SDL_GL_DeleteContext(gl_ctx);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("\nGoodbye.\n");
    return 0;
}
