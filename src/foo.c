/* Функции Принадлежности */
double Membership(double x, 
    double min, double mid, double max, char choice)
{
    if (choice) {
        if (x <= min) return 0;
        else if (x > min && x <= mid) 
            return 2.0*((x-min)/(max-min))*((x-min)/(max-min));
        else if (x > mid && x <  max) 
            return 1.0-2.0*((x-max)/(max-min))*((x-max)/(max-min));
        else return 1.0;
    } else {
        if (x <= min) return 1.0;
        else if (x > min && x <= mid) 
            return 1.0+2.0*((x-max)/(max-min))*((x-min)/(max-min));
        else if (x > mid && x <  max) 
            return 2.0*((x-min)/(max-min))*((x-max)/(max-min));
        else return 0;
    }
    return -1;
}

/* Дополнение | Инверсия */
double Complement(double x) 
{ 
    return 1-x; 
}

/* Алгебраическое произведение */
double Multiplication(double x, double y) 
{ 
    return x*y; 
}

/* Ограниченная Сумма */
double LimitedAmount(double x, double y)
{
    if (x+y > 1) return 1;
    else return x+y;
}

/* Пересечение | MIN */
double Intersection(double x, double y) 
{
    if (x > y) return y;
    else return x;
}

/* Объединение | MAX */
double Union(double x, double y) 
{
    if (x > y) return x;
    else return y;
}

/* Разность */
double Difference(double x, double y) 
{ 
    return Intersection(x, Complement(y)); 
}

/* Декартово | Прямое произведение */
double* CartesianProduct(double arrX[], double arrY[])
{
    double *cartesianProductArr = malloc(sizeof(double)*arrLength*arrLength);
    int step = 0;
    for (int i = 0; i < arrLength; i++) {
        for (int j = 0; j < arrLength; j++) {
            *(cartesianProductArr+step) = arrX[i] * arrY[j];
            step++;
        }
    }
    return cartesianProductArr;
}

/* Альфа Срез */
int alpha(double x, double slice)
{
    if (x >= slice) return 1;
    return 0;
}

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
                        camera->xL += cameraStepX;
                        camera->xR -= cameraStepX;
                        camera->yD += cameraStepY;
                        camera->yU -= cameraStepY;
                        break;
                    case SDLK_i: 
                        camera->xL -= cameraStepX;
                        camera->xR += cameraStepX;
                        camera->yD -= cameraStepY;
                        camera->yU += cameraStepY;
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

void DrawGraph(int arrLength, double set[],
        double colorR, double colorG, double colorB) 
{
    glColor3f(colorR, colorG, colorB);
    glLineWidth(lineWidth);
    glBegin(GL_LINES);
        for (int i = 0; i < arrLength-1; i++) {
            glVertex2f(i, set[i]);
            glVertex2f(i+1, set[i+1]);
        }
    glEnd();
    glPointSize(pointSize);
    glBegin(GL_POINTS);
        for (int i = 0; i < arrLength; i++) {
            glColor3f(colorR+0.4, colorG+0.4, colorB+0.4);
            glVertex2f(i, set[i]);
        }
    glEnd();
}

void FillGraph(int arrLength, double set[],
        double colorR, double colorG, double colorB) 
{
    glColor3f(colorR, colorG, colorB);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < arrLength; i++) {
        glVertex2f(i, 0);
        glVertex2f(i, set[i]);
    }
    glEnd();
}

void AlphaChoice(struct nk_context *ctx, int *alphaMessage, double *slice)
{
    static int len = 5;
    static char sliceChar[12] = {"0.000"};
    nk_edit_string(ctx, NK_EDIT_SIMPLE, sliceChar, &len, 12, nk_filter_float);
    if (nk_button_label(ctx, "Alpha")) *alphaMessage = 1;
    *slice = atof(sliceChar);
}

void AlphaMessage(struct nk_context *ctx, 
        int *alphaMessage, double arr[], double slice)
{
    static char* names[12];
    static char strHead[20];
    static char strName[40];

    sprintf(strHead, "Alpha: %4.3f", slice);
    if (nk_begin(ctx, strHead, 
            nk_rect(winWidth / 2 - 75, winHeight / 2 - 120, 190, 210),
            NK_WINDOW_CLOSABLE | NK_WINDOW_BORDER | 
            NK_WINDOW_TITLE | NK_WINDOW_MOVABLE | 
            NK_WINDOW_NO_SCROLLBAR))
    {
        for (int i = 0; i < arrLength; i++) {
            if (alpha(arr[i], slice)) {
                names[i] = defaultData[i].name;
            } else names[i] = 0;
        }
        nk_layout_row_dynamic(ctx, 1, 4);
        nk_spacing(ctx, 0);
        nk_layout_row_dynamic(ctx, 15, 1);
        for (int i = 0; i < arrLength; i++) {
            if (names[i]) {
                sprintf(strName, "%10s - %6.5f%3c", names[i], arr[i], ' ');
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
        AlphaChoice(ctx, alphaMessage, slice);

        nk_layout_row_dynamic(ctx, 4, 1);
        nk_spacing(ctx, 0);

        nk_layout_row_dynamic(ctx, 40, 1);
        if (nk_button_label(ctx, "Clear")) 
            *drawSet = _empty;

        nk_layout_row_dynamic(ctx, 4, 1);
        nk_spacing(ctx, 0);

        nk_layout_row_dynamic(ctx, 40, 3);
        if (nk_button_label(ctx, "Membership")) 
            *drawSet = _membership;
        if (nk_button_label(ctx, "Supplement")) 
            *drawSet = _supplement;
        if (nk_button_label(ctx, "Intersection")) 
            *drawSet = _intersection;
        if (nk_button_label(ctx, "Union")) 
            *drawSet = _union;
        if (nk_button_label(ctx, "Limited Amount")) 
            *drawSet = _amount;
        if (nk_button_label(ctx, "Difference")) 
            *drawSet = _difference;
        if (nk_button_label(ctx, "Multiplication")) 
            *drawSet = _multiplication;
    } nk_end(ctx); 
}
