/* ----------------- Graphics Foo ----------------- */

void DrawGrid()
{
    glColor3f(0.3,0.3,0.3);
    glLineWidth(2);
    glBegin(GL_LINES);
        for (int i = 0; i < arrLength; i++) {
            glVertex2f(i, 0); 
            glVertex2f(i, 1);
        }
        for (double i = 0; i < 1; i += 0.1) {
            glVertex2f(0, i); 
            glVertex2f(arrLength-1, i);
        }
    glEnd();
}

void DrawGraph(int length, double set[],
        double colorR, double colorG, double colorB) 
{
    glColor3f(colorR, colorG, colorB);
    glLineWidth(graphLineWidth);
    glBegin(GL_LINES);
        for (int i = 0; i < length-1; i++) {
            glVertex2f(i, set[i]);
            glVertex2f(i+1, set[i+1]);
        }
    glEnd();
    glPointSize(graphPointSize);
    glBegin(GL_POINTS);
        for (int i = 0; i < length; i++) {
            glColor3f(colorR+0.4, colorG+0.4, colorB+0.4);
            glVertex2f(i, set[i]);
        }
    glEnd();
}

void FillGraph(int length, double set[],
        double colorR, double colorG, double colorB) 
{
    glColor3f(colorR, colorG, colorB);
    /* const float gradIndex = 1.5; */
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < length; i++) {
        /* glColor3f(0, 0.1/gradIndex, 0.1/gradIndex); */
        glVertex2f(i, 0);
        /* glColor3f(0, set[i]/gradIndex, set[i]/gradIndex); */
        glVertex2f(i, set[i]);
    }
    glEnd();
}

void SetCut(struct nk_context *ctx, double *cut)
{
    static int len = 5;
    static char sliceChar[8] = {"0.000"};
    nk_edit_string(ctx, NK_EDIT_SIMPLE, sliceChar, &len, 6, nk_filter_float);
    if (nk_button_label(ctx, "Alpha")) alphaMessage = !alphaMessage;
    sliceChar[len] = '\0';
    *cut = atof(sliceChar);
}

void AlphaMessage(struct nk_context *ctx, double arr[], const char curArr[])
{
    static char* names[arrLength];
    static char menuName[40];
    static char strName[40];

    sprintf(menuName, "%s Cut: %4.3f", curArr, alphaCut);
    if (nk_begin(ctx, menuName, 
            nk_rect(398+280+6, 6, 230, 200),
            NK_WINDOW_CLOSABLE | NK_WINDOW_BORDER  
            | NK_WINDOW_TITLE | NK_WINDOW_MOVABLE  
            /* | NK_WINDOW_NO_SCROLLBAR */ ))
    {
        for (int i = 0; i < arrLength; i++) {
            if (Alpha(arr[i], alphaCut)) {
                names[i] = data[i].name;
            } else names[i] = 0;
        }
        nk_layout_row_dynamic(ctx, 1, 4);
        nk_spacing(ctx, 0);
        nk_layout_row_dynamic(ctx, 15, 1);
        for (int i = 0; i < arrLength; i++) {
            if (names[i]) {
                sprintf(strName, "x%i: %8s - %6.5f", i+1, names[i], arr[i]);
                nk_label(ctx, strName, NK_TEXT_CENTERED);
            }
        }
    } else alphaMessage = 0;
    nk_end(ctx);
}

void DataMessage(struct nk_context *ctx, struct obj data[])
{
    const char* menuName = "Current Data";
    static char dataCharV[arrLength][8];
    static char dataCharM[arrLength][8];
    static char elemName[20];
    static char beginStr[20];
    static char endStr[20];

    static int init = 1;
    static int len[arrLength*2];

    if (init) {
        for (int i = 0; i < arrLength; i++) {
            len[i] = sprintf(dataCharV[i], "%.1f", data[i].V); 
            len[i+arrLength] = sprintf(dataCharM[i], "%.1f", data[i].M);
        }
        init = 0;
    }

    if (nk_begin(ctx, menuName, 
            nk_rect(398, 6, 280, 480),
            NK_WINDOW_CLOSABLE | NK_WINDOW_BORDER
            | NK_WINDOW_TITLE | NK_WINDOW_MOVABLE
            | NK_WINDOW_SCALABLE
            /* NK_WINDOW_NO_SCROLLBAR */ ))
    {
        for (int i = 0; i < arrLength; i++) {
            sprintf(elemName, "(x%i) - %9s:", i+1, data[i].name);
            sprintf(beginStr, "Capacity: ");
            sprintf(endStr, "Mass: ");

            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, elemName, NK_TEXT_LEFT);
            nk_layout_row_dynamic(ctx, 20, 2);
            nk_label_colored(ctx, beginStr, NK_TEXT_RIGHT, nk_rgb(220,30,30));
            nk_edit_string(ctx, NK_EDIT_SIMPLE, dataCharV[i], 
                &len[i], 6, nk_filter_float);
            nk_label_colored(ctx, endStr, NK_TEXT_RIGHT, nk_rgb(30, 220, 30));
            nk_edit_string(ctx, NK_EDIT_SIMPLE, dataCharM[i], 
                &len[i+arrLength], 7, nk_filter_float);

            dataCharV[i][len[i]] = '\0';
            dataCharM[i][len[i+arrLength]] = '\0';
            data[i].V = atof(dataCharV[i]);
            data[i].M = atof(dataCharM[i]);
        }
    } else dataMessage = 0;
    nk_end(ctx);
}

void IndexMessage(struct nk_context *ctx)
{
    #define __arraySize 15
    #define __stringSize 40

    const static char menuName[] = "Fuzzy Indices:";
    char str[__arraySize][__stringSize];

    sprintf(str[0], "Linear Fuzzy Index:");
    sprintf(str[1], "%10s %5.3f", "Capacity:", linearFuzzyIndexV);
    sprintf(str[2], "%10s %5.3f", "Mass:", linearFuzzyIndexM);

    sprintf(str[3], "Quadro Fuzzy Index:");
    sprintf(str[4], "%10s %5.3f", "Capacity:", quadroFuzzyIndexV);
    sprintf(str[5], "%10s %5.3f", "Mass:", quadroFuzzyIndexM);

    sprintf(str[6], "Eger Fuzzy Measure (p=1):");
    sprintf(str[7], "%10s %5.3f", "Capacity:", fuzOneV);
    sprintf(str[8], "%10s %5.3f", "Mass:", fuzOneM);

    sprintf(str[9], "Eger Fuzzy Measure (p=2):");
    sprintf(str[10], "%10s %5.3f", "Capacity:", fuzTwoV);
    sprintf(str[11], "%10s %5.3f", "Mass:", fuzTwoM);

    sprintf(str[12], "Kosko Fuzzy Measure:");
    sprintf(str[13], "%10s %5.3f", "Capacity:", koskoV);
    sprintf(str[14], "%10s %5.3f", "Mass:", koskoM);

    if (nk_begin(ctx, menuName, 
            nk_rect(398+280+6+230+6, 6, 220, 335),
            NK_WINDOW_CLOSABLE | NK_WINDOW_BORDER 
            | NK_WINDOW_TITLE  | NK_WINDOW_MOVABLE))
    {
        for (int i = 0; i < __arraySize; i+=3) {
            nk_layout_row_dynamic(ctx, 2, layoutSpacing);
            nk_spacing(ctx, 0);
            nk_layout_row_dynamic(ctx, 12, 1);
            nk_label_colored(ctx, str[i], NK_TEXT_LEFT, nk_rgb(240,240,240));
            nk_label(ctx, str[i+1], NK_TEXT_LEFT);
            nk_label(ctx, str[i+2], NK_TEXT_LEFT);
        }
    } else indexMessage = 0;
    nk_end(ctx);
}

void ComparisonMessage(struct nk_context *ctx) 
{
    const static char menuName[] = "Comparison of sets:";
    if (nk_begin(ctx, menuName, 
            nk_rect(398, winHeight-80-8, 365, 80),
            NK_WINDOW_CLOSABLE | NK_WINDOW_BORDER  |
            NK_WINDOW_TITLE    | NK_WINDOW_MOVABLE |
            NK_WINDOW_NO_SCROLLBAR))
    {
        nk_layout_row_dynamic(ctx, layoutSpacing, 1);
            nk_spacing(ctx, 0);
        nk_layout_row_dynamic(ctx, 10, 1);
            nk_label(ctx, compStr, NK_TEXT_CENTERED);
    } else comparisonMessage = 0;
    nk_end(ctx);
}

void Messages(struct nk_context *ctx)
{
    if (alphaMessage) {
        if (currentArr == 0) 
            AlphaMessage(ctx, memberArrV, setsArr[currentArr]);
        else if (currentArr == 1)
            AlphaMessage(ctx, memberArrM, setsArr[currentArr]);
    }
    if (dataMessage) {
        DataMessage(ctx, data);
    }
    if (indexMessage) {
        IndexMessage(ctx);
    }
    if (comparisonMessage) {
        ComparisonMessage(ctx);
    }
}

void MainMenu(struct nk_context *ctx)
{
    if (nk_begin(ctx, "Menu", nk_rect(defaultNkPosition),
            NK_WINDOW_BORDER     | NK_WINDOW_MINIMIZABLE  | 
            NK_WINDOW_TITLE      | NK_WINDOW_NO_SCROLLBAR | 
            NK_WINDOW_BACKGROUND | NK_WINDOW_SCALABLE     |
            NK_WINDOW_MOVABLE)) 
    {
        nk_layout_row_dynamic(ctx, 18, 4);
        nk_label(ctx, "Legend:", NK_TEXT_LEFT);
        nk_label_colored(ctx, "Capacity", NK_TEXT_CENTERED, nk_rgb(220, 30, 30));
        nk_label_colored(ctx, "Mass", NK_TEXT_CENTERED, nk_rgb(30, 220, 30));
        nk_label_colored(ctx, "Function", NK_TEXT_CENTERED, nk_rgb(30, 220, 220));
        nk_layout_row_dynamic(ctx, layoutSpacing, 1);
            nk_spacing(ctx, 0);

        nk_layout_row_dynamic(ctx, 40, 2);
            if (nk_button_label(ctx, "Current Data")) 
                dataMessage = !dataMessage;
            if (nk_button_label(ctx, "Calc of Sets")) 
                CalcOfSets();
        nk_layout_row_dynamic(ctx, 30, 1);
            if (nk_button_label(ctx, "Clear Graph")) 
                drawSet = _empty;

        nk_layout_row_dynamic(ctx, layoutSpacing, 1);
            nk_spacing(ctx, 0);
        nk_layout_row_dynamic(ctx, 40, 2);
            if (nk_button_label(ctx, "Membership")) 
                drawSet = _membership;
            if (nk_button_label(ctx, "Supplement")) 
                drawSet = _supplement;
        nk_layout_row_dynamic(ctx, 40, 3);
            if (nk_button_label(ctx, "Intersection")) 
                drawSet = _intersection;
            if (nk_button_label(ctx, "Difference V-M")) 
                drawSet = _differenceVM;
            if (nk_button_label(ctx, "Limited Amount")) 
                drawSet = _amount;
            if (nk_button_label(ctx, "Union")) 
                drawSet = _union;
            if (nk_button_label(ctx, "Difference M-V")) 
                drawSet = _differenceMV;
            if (nk_button_label(ctx, "Multiplication")) 
                drawSet = _multiplication;

        nk_layout_row_dynamic(ctx, layoutSpacing, 1);
            nk_spacing(ctx, 0);
        nk_layout_row_dynamic(ctx, 30, 2);
            if (nk_button_label(ctx, "Fuzzy Indices"))
                indexMessage = !indexMessage;
            if (nk_button_label(ctx, "Comparison"))
                comparisonMessage = !comparisonMessage;

        nk_layout_row_dynamic(ctx, layoutSpacing, 1);
            nk_spacing(ctx, 0);
        /* Выбор множества для альфа среза */
        nk_layout_row_dynamic(ctx, 30, 2);
            currentArr = nk_combo(ctx, setsArr, 
                NK_LEN(setsArr), currentArr, 25, nk_vec2(160, 200));
        nk_layout_row_dynamic(ctx, 30, 4);
            SetCut(ctx, &alphaCut);

    } nk_end(ctx); 
}

void GraphRendering(int drawSet)
{
    switch (drawSet)
    {
        case _membership:
            DrawGrid();
            DrawGraph(arrLength, memberArrV, colorGraph_V);
            DrawGraph(arrLength, memberArrM, colorGraph_M);
            break;
        case _supplement:
            DrawGrid();
            DrawGraph(arrLength, supplementArrV, colorGraph_V);
            DrawGraph(arrLength, supplementArrM, colorGraph_M);
            break;
        case _intersection:
            FillGraph(arrLength, intersectionArr, colorForFill);
            DrawGrid();
            DrawGraph(arrLength, memberArrV, colorGraph_V);
            DrawGraph(arrLength, memberArrM, colorGraph_M);
            DrawGraph(arrLength, intersectionArr, colorGraph_VM);
            break;
        case _union:
            FillGraph(arrLength, unionArr, colorForFill);
            DrawGrid();
            DrawGraph(arrLength, memberArrV, colorGraph_V);
            DrawGraph(arrLength, memberArrM, colorGraph_M);
            DrawGraph(arrLength, unionArr, colorGraph_VM);
            break;
        case _amount:
            FillGraph(arrLength, limitedAmountArr, colorForFill);
            DrawGrid();
            DrawGraph(arrLength, memberArrV, colorGraph_V);
            DrawGraph(arrLength, memberArrM, colorGraph_M);
            DrawGraph(arrLength, limitedAmountArr, colorGraph_VM);
            break;
        case _differenceVM:
            FillGraph(arrLength, differenceArr_VM, colorForFill);
            DrawGrid();
            DrawGraph(arrLength, memberArrV, colorGraph_V);
            DrawGraph(arrLength, supplementArrM, colorGraph_M);
            DrawGraph(arrLength, differenceArr_VM, colorGraph_VM);
            break;
        case _differenceMV:
            FillGraph(arrLength, differenceArr_MV, colorForFill);
            DrawGrid();
            DrawGraph(arrLength, supplementArrV, colorGraph_V);
            DrawGraph(arrLength, memberArrM, colorGraph_M);
            DrawGraph(arrLength, differenceArr_MV, colorGraph_VM);
            break;
        case _multiplication:
            FillGraph(arrLength, multiplicationArr, colorForFill);
            DrawGrid();
            DrawGraph(arrLength, memberArrV, colorGraph_V);
            DrawGraph(arrLength, memberArrM, colorGraph_M);
            DrawGraph(arrLength, multiplicationArr, colorGraph_VM);
            break;
        default:
            DrawGrid();
    }
}

int KeyDown(struct glRegion *camera, struct nk_context *ctx, SDL_Event evt)
{
    #define regionWidth sqrt((camera->xR - camera->xL)*(camera->xR - camera->xL))
    switch (evt.type) {
        case SDL_QUIT: 
            return 0;
        case SDL_KEYDOWN:
            switch (evt.key.keysym.sym) {
                case SDLK_o:
                    if (regionWidth > zoomWidthMin) {
                        camera->xL += cameraStepX;
                        camera->xR -= cameraStepX;
                        camera->yD += cameraStepY;
                        camera->yU -= cameraStepY;
                    } break;
                case SDLK_i: 
                    if (regionWidth < zoomWidthMax) {
                        camera->xL -= cameraStepX;
                        camera->xR += cameraStepX;
                        camera->yD -= cameraStepY;
                        camera->yU += cameraStepY;
                    } break;
                case SDLK_h:
                    camera->xL -= cameraStepX;
                    camera->xR -= cameraStepX;
                    break;
                case SDLK_j:
                    camera->yD -= cameraStepY;
                    camera->yU -= cameraStepY;
                    break;
                case SDLK_k:
                    camera->yD += cameraStepY;
                    camera->yU += cameraStepY;
                    break;
                case SDLK_l:
                    camera->xL += cameraStepX;
                    camera->xR += cameraStepX;
                    break;
                case SDLK_d:
                    *camera = defaultGlRegion;
                    break;
                case SDLK_q:
                    return 0;
            } 
            glLoadIdentity();
            gluOrtho2D(camera->xL, camera->xR, camera->yD, camera->yU);
            glMatrixMode(GL_MODELVIEW);
            break;
        default:
            break;
    } nk_sdl_handle_event(&evt);
    return 1;
}

void RefreshRender(struct nk_context *ctx, SDL_Window *window)
{
    glClear(GL_COLOR_BUFFER_BIT);
    GraphRendering(drawSet);
    MainMenu(ctx);
    Messages(ctx);

    glFlush();
    nk_sdl_render(NK_ANTI_ALIASING_ON, 
        MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
    SDL_GL_SwapWindow(window);
}

int PollEvent(struct glRegion *camera, struct nk_context *ctx, SDL_Window *window)
{
    static SDL_Event evt;
    nk_input_begin(ctx);
    while(SDL_PollEvent(&evt)) 
        if (!KeyDown(camera, ctx, evt)) return 0;
    nk_input_end(ctx); 
    return 1;
}