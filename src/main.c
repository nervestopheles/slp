#include "settings.h"
#include "mathFoo.c"
#include "graphFoo.c"

int main(void) 
{
    /* --------------- Sets Vars --------------- */
    int currentArr = 0;

    double minV = 1, maxV = 12,       minM = 300, maxM = 1200;
    double midV = (minV + maxV) / 2,  midM = (minM + maxM) / 2;

    double memberArrV[arrLength], memberArrM[arrLength];
    double supplementArrV[arrLength], supplementArrM[arrLength];

    double intersectionArr[arrLength];
    double unionArr[arrLength];
    double limitedAmountArr[arrLength];
    double differenceArr[arrLength];
    double multiplicationArr[arrLength];
    double cartesianProductArr[arrLength*arrLength];

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

    /* --------------- Console Output --------------- */
    printf("\n-------------------- Source Data --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        printf("%10s:  (x%i) | V = %6.3f | M = %.0f \n", 
                defaultData[i].name, i+1, defaultData[i].V, defaultData[i].M);
    } 
    
    /* Функции Принадлежности */
    printf("\n-------------------- Membership Functions --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        memberArrV[i] = Membership(defaultData[i].V, minV, midV, maxV, 1);
        memberArrM[i] = Membership(defaultData[i].M, minM, midM, maxM, 0);
        printf("%10s:  (x%i) | %5.3f | %5.3f \n", 
                defaultData[i].name, i+1, memberArrV[i], memberArrM[i]);
    }

    /* Дополнение | Инверсия */
    printf("\n-------------------- Supplement --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        supplementArrV[i] = Supplement(memberArrV[i]);
        supplementArrM[i] = Supplement(memberArrM[i]);
        printf("%10s:  (x%i) | %5.3f | %5.3f \n", 
                defaultData[i].name, i+1, supplementArrV[i], supplementArrM[i]);
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
    CartesianProduct(memberArrV, memberArrM, cartesianProductArr);
    for (int i = 0; i < sizeof(cartesianProductArr)/sizeof(double); i++) {
        printf("  (x%2i) | %5.3f \n", i+1, *(cartesianProductArr + i));
    }

    /* --------------- Setup --------------- */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow(
            appName, 
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            winWidth, winHeight, 
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN 
            /* | SDL_WINDOW_RESIZABLE */ );
    glContext = SDL_GL_CreateContext(window);

    glewInit();
    gluOrtho2D(camera.xL, camera.xR, camera.yD, camera.yU);
    glEnable(GL_POINT_SMOOTH);

    glClearColor(bg.r, bg.g, bg.b, 1);

    ctx = nk_sdl_init(window);
    struct nk_font_atlas *atlas;

    nk_sdl_font_stash_begin(&atlas);
    struct nk_font *font = nk_font_atlas_add_from_file(atlas, fontPath, fontSize, 0);
    nk_sdl_font_stash_end();

    nk_style_set_font(ctx, &font->handle);
    nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);

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
        } else if (drawSet == _difference) {
            FillGraph(arrLength, differenceArr, colorForFill);
            DrawGrid();
            DrawGraph(arrLength, memberArrV, colorGraph_V);
            DrawGraph(arrLength, supplementArrM, colorGraph_M);
            DrawGraph(arrLength, differenceArr, colorGraph_VM);
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
        nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
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
