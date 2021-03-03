#include "settings.h"
#include "foo.c"

int main(void) 
{
    /* --------------- Sets Vars --------------- */
    double memberArrV[arrLength];
    double memberArrM[arrLength];

    double complementArrV[arrLength];
    double complementArrM[arrLength];

    double intersectionArr[arrLength];
    double unionArr[arrLength];

    double limitedAmountArr[arrLength];
    double differenceArr[arrLength];

    double multiplicationArr[arrLength];
    double *cartesianProductArr;

    double minV = 1, maxV = 12;
    double midV = (minV + maxV) / 2;

    double minM = 300, maxM = 1200;
    double midM = (minM + maxM) / 2;

    /* --------------- Graphics Vars --------------- */
    SDL_Window *window;
    SDL_GLContext glContext;
    SDL_Event evt;

    struct nk_context *ctx;
    struct nk_colorf bgColor;
    
    int winWidth = appWidth;
    int winHeight = appHeight;

    bgColor.a = 1.0f;
    bgColor.r = 0.10f;
    bgColor.g = 0.10f;
    bgColor.b = 0.10f; 

    /* --------------- Console Output --------------- */
    printf("\n-------------------- Source Data --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        printf("%10s:  (x%i) | V = %6.3f | M = %.0f \n", 
                Data[i].name, i+1, Data[i].V, Data[i].M);
    } 
    
    /* Функции Принадлежности */
    printf("\n-------------------- Membership Functions --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        memberArrV[i] = Membership(Data[i].V, minV, midV, maxV, 1);
        memberArrM[i] = Membership(Data[i].M, minM, midM, maxM, 0);
        printf("%10s:  (x%i) | %5.3f | %5.3f \n", 
                Data[i].name, i+1, memberArrV[i], memberArrM[i]);
    }

    /* Дополнение | Инверсия */
    printf("\n-------------------- Complemet --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        complementArrV[i] = Complement(memberArrV[i]);
        complementArrM[i] = Complement(memberArrM[i]);
        printf("%10s:  (x%i) | %5.3f | %5.3f \n", 
                Data[i].name, i+1, complementArrV[i], complementArrM[i]);
    }

    /* Пересечение | MIN */
    printf("\n-------------------- Intersection --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        intersectionArr[i] = Intersection(memberArrV[i], memberArrM[i]);
        printf("  (x%i) | %5.3f \n", i+1, intersectionArr[i]);
    }

    /* Объединение | MAX */
    printf("\n-------------------- Union --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        unionArr[i] = Union(memberArrV[i], memberArrM[i]);
        printf("  (x%i) | %5.3f \n", i+1, unionArr[i]);
    }

    /* Разность */
    printf("\n-------------------- Difference --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        differenceArr[i] = Difference(memberArrV[i], memberArrM[i]);
        printf("  (x%i) | %5.3f \n", i+1, differenceArr[i]);
    }

    /* Ограниченная Сумма */
    printf("\n-------------------- Limited Amount --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        limitedAmountArr[i] = LimitedAmount(memberArrV[i], memberArrM[i]);
        printf("  (x%i) | %5.3f \n", i+1, limitedAmountArr[i]);
    }

    /* Алгебраическое произведение */
    printf("\n-------------------- Multiplication --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        multiplicationArr[i] = Multiplication(memberArrV[i], memberArrM[i]);
        printf("  (x%i) | %5.3f \n", i+1, multiplicationArr[i]);
    }

    /* Декартово | Прямое произведение */
    printf("\n-------------------- Cartesian Product --------------------\n\n"); 
    cartesianProductArr = CartesianProduct(memberArrV, memberArrM);
    for (int i = 0; i < arrLength*arrLength; i++) {
        printf("  (x%2i) | %5.3f \n", i+1, *(cartesianProductArr + i));
    }

    printf("\n-------------------------------------------------------------\n");

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
    for (int quit = 0; !quit;) 
    {
        nk_input_begin(ctx);
        while(SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) quit = 1;
            nk_sdl_handle_event(&evt);
        } nk_input_end(ctx);



        SDL_GetWindowSize(window, &winWidth, &winHeight);
        glViewport(0, 0, winWidth, winHeight);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);

        nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
        SDL_GL_SwapWindow(window);
    }

    /* --------------- Exit --------------- */
    free(cartesianProductArr);

    nk_sdl_shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("Goodbye.\n");
    return 0;
}

