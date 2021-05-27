#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>

const char *application_name = "Lab Two";
const int screen_width= 800;
const int screen_height = 600;

struct Furnace {
    char *name;
    int performance;
    int volume;
};

int main(void)
{
    printf("Hello World!\n");

    SDL_Init(SDL_INIT_VIDEO);
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
        | SDL_RENDERER_PRESENTVSYNC 
    );
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    glClearColor(0.1, 0.1, 0.1, 1);

    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    SDL_GL_SwapWindow(window);

    SDL_Delay(2500);

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("\nGoodbye.\n");
    return 0;
}