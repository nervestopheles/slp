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

    struct obj Data[] = {
        { "K/SQ 2"   , 0.3  , 110   }, 
        { "K/SQ 3"   , 0.9  , 200   }, 
        { "K/SQ 5"   , 4.5  , 380   }, 
        { "CM-243 V" , 4    , 550   }, 
        { "CM-489 B" , 8    , 1220  }, 
        { "K/SQ 7"   , 13.5 , 1230  }, 
        { "K/SQ 10"  , 38   , 2700  }
    };

    /* --------------- Graphics Vars --------------- */
    SDL_Window *window;
    SDL_GLContext glContext;
    SDL_Event evt;

    int drawSet = 0;

    struct nk_context *ctx;
    struct bgColor bg = {0.08, 0.08, 0.1};
    struct glRegion camera = {-3, 6.05, -0.01, 1.008};
    struct nkPosition pos = {6, 6, 385, winHeight-6*2};

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
        } else if (drawSet == _complement) {
            DrawGrid();
            DrawGraph(arrLength, complementArrV, colorGraph_V);
            DrawGraph(arrLength, complementArrM, colorGraph_M);
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
            DrawGraph(arrLength, complementArrM, colorGraph_M);
            DrawGraph(arrLength, differenceArr, colorGraph_VM);
        } else if (drawSet == _multiplication) {
            FillGraph(arrLength, multiplicationArr, colorForFill);
            DrawGrid();
            DrawGraph(arrLength, memberArrV, colorGraph_V);
            DrawGraph(arrLength, memberArrM, colorGraph_M);
            DrawGraph(arrLength, multiplicationArr, colorGraph_VM);
        } else DrawGrid();

        if (nk_begin(ctx, "Menu", nk_rect(pos.x1, pos.y1, pos.x2, pos.y2),
                NK_WINDOW_BORDER | NK_WINDOW_MINIMIZABLE | 
                NK_WINDOW_TITLE | NK_WINDOW_NO_SCROLLBAR)) 
        {
            nk_layout_row_dynamic(ctx, 40, 1);
            if (nk_button_label(ctx, "Clear")) drawSet = _empty;
            nk_layout_row_dynamic(ctx, 40, 3);
            if (nk_button_label(ctx, "Membership")) drawSet = _membership;
            if (nk_button_label(ctx, "Complement")) drawSet = _complement;
            if (nk_button_label(ctx, "Intersection")) drawSet = _intersection;
            if (nk_button_label(ctx, "Union")) drawSet = _union;
            if (nk_button_label(ctx, "Limited Amount")) drawSet = _amount;
            if (nk_button_label(ctx, "Difference")) drawSet = _difference;
            if (nk_button_label(ctx, "Multiplication")) drawSet = _multiplication;
        } nk_end(ctx);

        glFlush();
        nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
        SDL_GL_SwapWindow(window);
    }

    /* --------------- Exit --------------- */
    free(cartesianProductArr);

    nk_sdl_shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("\nGoodbye.\n");
    return 0;
}
