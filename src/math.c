/* ----------------- Math Foo ----------------- */

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
double Supplement(double x) 
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
    return Intersection(x, Supplement(y)); 
}

/* Декартово | Прямое произведение */
void CartesianProduct(double arrX[], double arrY[], double res[])
{
    int step = 0;
    for (int i = 0; i < arrLength; i++) {
        for (int j = 0; j < arrLength; j++) {
            *(res+step) = arrX[i] * arrY[j];
            step++;
        }
    }
}

/* Альфа Срез */
int Alpha(double x, double cut)
{
    if (x >= cut) return 1;
    return 0;
}

/* Нахождение ближайшего четекого множества */
double Near(double x)
{
    if (x >= 0.5) return 1;
    else  return 0;
}

/* Расстояние Хемминга */
void HammingDistance(double x[], double y[], double res[])
{
    for (int i = 0; i < arrLength; i++) {
        res[i] = sqrt((x[i] - y[i])*(x[i] - y[i]));
    }
}

/* Линейный индекс нечеткости */
double LinearFuzzyIndex(double x[])
{
    double sum = 0;
    for (int i = 0; i < arrLength; i++)
        sum += x[i];
    return 2.0 * sum / arrLength;
}

/* Квадратичный индекс нечеткости */
void QuadroIndex(double egerDist[], double res[])
{
    for (int i = 0; i < arrLength; i++) {
        res[i] = (2.0 / sqrt(arrLength)) * egerDist[i];
    }
}
