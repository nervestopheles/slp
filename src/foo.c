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

/* ----------------- Graphics Foo ----------------- */
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

int PollEvent(struct nk_context *ctx, SDL_Event evt)
{
    nk_input_begin(ctx);
    while(SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT) return 0;
        nk_sdl_handle_event(&evt);
    } nk_input_end(ctx); 
    return 1;
}

void DrawGraph(int arrLength, double set[],
        double colorR, double colorG, double colorB) 
{
    glColor3f(colorR, colorG, colorB);

    glLineWidth(3);
    glBegin(GL_LINES);
        for (int i = 0; i < arrLength-1; i++) {
            glVertex2f(i, set[i]);
            glVertex2f(i+1, set[i+1]);
        }
    glEnd();

    glPointSize(8);
    glBegin(GL_POINTS);
        for (int i = 0; i < arrLength; i++) {
            glColor3f(1,1,1);
            glVertex2f(i, set[i]);
        }
    glEnd();
}

void FillGraph(int arrLength, double set[],
        double colorR, double colorG, double colorB) 
{
    glColor3f(colorR, colorG, colorB);
    for (int i = 0; i < arrLength-1; i++)
    {
        if (set[i] < set[i+1]){
            glBegin(GL_POLYGON);
                glVertex2f(i, set[i]);
                glVertex2f(i, 0);
                glVertex2f(i+1, set[i+1]);
            glEnd();
            glBegin(GL_POLYGON);
                glVertex2f(i, 0);
                glVertex2f(i+1, 0);
                glVertex2f(i+1, set[i+1]);
            glEnd();
        } else {
            glBegin(GL_POLYGON);
                glVertex2f(i, set[i]);
                glVertex2f(i, 0);
                glVertex2f(i+1, 0);
            glEnd();
            glBegin(GL_POLYGON);
                glVertex2f(i, set[i]);
                glVertex2f(i+1, set[i+1]);
                glVertex2f(i+1, 0);
            glEnd();
        }
    }
}
