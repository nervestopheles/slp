/* ----------------- Graphics Foo ----------------- */

int PollEvent(struct glRegion *camera, struct nk_context *ctx, SDL_Event evt)
{
    nk_input_begin(ctx);
    while(SDL_PollEvent(&evt)) {
        switch (evt.type) {
            case SDL_QUIT: 
                return 0;
            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym) {
                    case SDLK_o:
                        if (camera->xL+cameraStepX*zoomBorderMax < 
                                camera->xR-cameraStepX*zoomBorderMax) {
                            camera->xL += cameraStepX;
                            camera->xR -= cameraStepX;
                            camera->yD += cameraStepY;
                            camera->yU -= cameraStepY;
                        }
                        break;
                    case SDLK_i: 
                        if (camera->xR - camera->xL < zoomBorderMin) {
                            camera->xL -= cameraStepX;
                            camera->xR += cameraStepX;
                            camera->yD -= cameraStepY;
                            camera->yU += cameraStepY;
                        }
                        break;
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
        }
        nk_sdl_handle_event(&evt);
    } nk_input_end(ctx); 
    return 1;
}

void DrawGrid()
{
    glColor3f(0.3,0.3,0.3);
    glLineWidth(2);
    glBegin(GL_LINES);
        for (int i = 0; i < 7; i++) {
            glVertex2f(i, 0); 
            glVertex2f(i, 1);
        }
        for (double i = 0; i <= 1; i += 0.1) {
            glVertex2f(0, i); 
            glVertex2f(6, i);
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
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < length; i++) {
        glVertex2f(i, 0);
        glVertex2f(i, set[i]);
    }
    glEnd();
}

void SetsChoice(struct nk_context *ctx, int *alphaMessage, double *slice)
{
    static int len = 5;
    static char sliceChar[8] = {"0.000"};
    nk_edit_string(ctx, NK_EDIT_SIMPLE, sliceChar, &len, 6, nk_filter_float);
    if (nk_button_label(ctx, "Alpha")) *alphaMessage = !*alphaMessage;
    *slice = atof(sliceChar);
}

void AlphaMessage(struct nk_context *ctx, 
        int *alphaMessage, double arr[], double slice)
{
    static char* names[12];
    static char strHead[20];
    static char strName[40];

    sprintf(strHead, "Cut: %4.3f", slice);
    if (nk_begin(ctx, strHead, 
            nk_rect(398, 6, 230, 200),
            NK_WINDOW_CLOSABLE | NK_WINDOW_BORDER | 
            NK_WINDOW_TITLE | NK_WINDOW_MOVABLE | 
            NK_WINDOW_NO_SCROLLBAR ))
    {
        for (int i = 0; i < arrLength; i++) {
            if (Alpha(arr[i], slice)) {
                names[i] = defaultData[i].name;
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
    } else *alphaMessage = 0;
    nk_end(ctx);
}

void MainMenu(struct nk_context *ctx,
        int *drawSet, int *alphaMessage, double *slice, int *currentArr)
{
    if (nk_begin(ctx, "Menu", nk_rect(defaultNkPosition),
            NK_WINDOW_BORDER | NK_WINDOW_MINIMIZABLE | 
            NK_WINDOW_TITLE | NK_WINDOW_NO_SCROLLBAR | 
            NK_WINDOW_BACKGROUND)) 
    {
        nk_layout_row_dynamic(ctx, 4, 1);
            nk_spacing(ctx, 0);
        nk_layout_row_dynamic(ctx, 30, 3);
            *currentArr = nk_combo(ctx, setsArr, 
                NK_LEN(setsArr), *currentArr, 25, nk_vec2(200,200));
            SetsChoice(ctx, alphaMessage, slice);

        nk_layout_row_dynamic(ctx, 4, 1);
            nk_spacing(ctx, 0);
        nk_layout_row_dynamic(ctx, 40, 2);
            if (nk_button_label(ctx, "Calc of Sets")) 
                CalcOfSets();
            if (nk_button_label(ctx, "Clear")) 
                *drawSet = _empty;

        nk_layout_row_dynamic(ctx, 4, 1);
            nk_spacing(ctx, 0);
        nk_layout_row_dynamic(ctx, 40, 2);
            if (nk_button_label(ctx, "Membership")) 
                *drawSet = _membership;
            if (nk_button_label(ctx, "Supplement")) 
                *drawSet = _supplement;

        nk_layout_row_dynamic(ctx, 40, 3);
            if (nk_button_label(ctx, "Intersection")) 
                *drawSet = _intersection;
            if (nk_button_label(ctx, "Difference V-M")) 
                *drawSet = _differenceVM;
            if (nk_button_label(ctx, "Limited Amount")) 
                *drawSet = _amount;
            if (nk_button_label(ctx, "Union")) 
                *drawSet = _union;
            if (nk_button_label(ctx, "Difference M-V")) 
                *drawSet = _differenceMV;
            if (nk_button_label(ctx, "Multiplication")) 
                *drawSet = _multiplication;
    } nk_end(ctx); 
}
