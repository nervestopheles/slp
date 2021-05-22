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
        double colorR, double colorG, double colorB) /* Cool gradient in comment) */
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
