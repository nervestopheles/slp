/* ----------------- Math Foo ----------------- */

/* Функции Принадлежности */
void MembershipHigh(double x[], double res[],
    double min, double mid, double max)
{
    for (int i = 0; i < arrLength; i++) {
        if (x[i] <= min) res[i] = 0;
        else if (x[i] > min && x[i] <= mid) 
            res[i] = 2.0*((x[i]-min)/(max-min))*((x[i]-min)/(max-min));
        else if (x[i] > mid && x[i] < max) 
            res[i] = 1.0-2.0*((x[i]-max)/(max-min))*((x[i]-max)/(max-min));
        else res[i] = 1.0;
    }
}

void MembershipLow(double x[], double res[],
    double min, double mid, double max)
{
    for (int i = 0; i < arrLength; i++) {
        if (x[i] <= min) res[i] = 1.0;
        else if (x[i] > min && x[i] <= mid) 
            res[i] = 1.0+2.0*((x[i]-max)/(max-min))*((x[i]-min)/(max-min));
        else if (x[i] > mid && x[i] < max) 
            res[i] = fabs(2.0*((x[i]-min)/(max-min))*((x[i]-max)/(max-min)));
        else res[i] = 0;
    }
}

/* Дополнение | Инверсия */
void Supplement(double x[], double res[]) 
{
    for (int i = 0; i < arrLength; i++) {
        res[i] = 1 - x[i];
    }
}

/* Алгебраическое произведение */
void Multiplication(double x[], double y[], double res[]) 
{
    for (int i = 0; i < arrLength; i++) {
        res[i] = x[i] * y[i]; 
    }
}

/* Ограниченная Сумма */
void LimitedAmount(double x[], double y[], double res[])
{
    for (int i = 0; i < arrLength; i++) {
        if (x[i] + y[i] > 1) res[i] = 1;
        else res[i] = x[i] + y[i];
    }
}

/* Пересечение | MIN */
void Intersection(double x[], double y[], double res[]) 
{
    for (int i = 0; i < arrLength; i++) {
        if (x[i] > y[i]) res[i] = y[i];
        else res[i] = x[i];
    }
}

/* Объединение | MAX */
void Union(double x[], double y[], double res[]) 
{
    for (int i = 0; i < arrLength; i++) {
        if (x[i] > y[i]) res[i] = x[i];
        else res[i] = y[i];
    }
}

/* Разность */
void Difference(double x[], double y[], double res[]) 
{
    double un_y[arrLength];
    Supplement(y, un_y);
    Intersection(x, un_y, res); 
}

/* Альфа Срез */
int Alpha(double x, double cut)
{
    if (x >= cut) return 1;
    return 0;
}

/* Нахождение ближайшего четкого множества */
void Near(double x[], double res[])
{
    for (int i = 0; i < arrLength; i++) {
        if (x[i] >= 0.5) res[i] = 1;
        else res[i] = 0;
    }
}

/* Линейный индекс нечеткости */
double LinearFuzzyIndex(double x[], double y[])
{
    double sum = 0;
    for (int i = 0; i < arrLength; i++)
        sum += sqrt((x[i] - y[i])*(x[i] - y[i]));
    return 2.0 * sum / arrLength;
}

/* Квадратичный индекс нечеткости */
double QuadroFuzzyIndex(double x[], double y[])
{
    double sum;
    for (int i = 0; i < arrLength; i++) {
        sum += (x[i] - y[i])*(x[i] - y[i]);
    }
    return 2.0 * sqrt(sum) / sqrt(arrLength);
}

/* Степень нечеткости Егера при p=1 */
double FUZone(double x[])
{
    double sum = 0;
    for (int i = 0; i < arrLength; i++) {
        sum += sqrt((2*x[i]-1)*(2*x[i]-1));
    }
    return 1 - sum / arrLength;
}

/* Степень нечеткости Егера при p=2 */
double FUZtwo(double x[])
{
    double sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += (2*x[i]-1)*(2*x[i]-1);
    } sum = sqrt(sum);
    return 1 - sum / sqrt(5);
}

/* Кардинальное число */
double Cardinalis(double x[])
{
    double cardinal = 0;
    for (int i = 0; i < arrLength; i++) {
        cardinal += x[i];
    } return cardinal;
}

/* Степень нечеткости Коско */
double Kosko(double x[])
{
    double supplementX[arrLength]; 
    double intersectionX[arrLength];
    double unionX[arrLength];
    Supplement(x, supplementX);
    Intersection(x, supplementX, intersectionX);
    Union(x, supplementX, unionX);
    return Cardinalis(intersectionX) / Cardinalis(unionX);
}

int Comparison(double x[], double y[])
{
    int flag;

    flag = 0;
    for (int i = 0; i < arrLength; i++) {
        if (x[i] <= y[i]) flag++;
        else break;
    } if (flag == arrLength) return _compXinY;

    flag = 0;
    for (int i = 0; i < arrLength; i++) {
        if (x[i] >= y[i]) flag++;
        else break;
    } if (flag == arrLength) return _compYinX;

    flag = 0;
    for (int i = 0; i < arrLength; i++) {
        if (x[i] == y[i]) flag++; 
        else break;
    } if (flag == arrLength) return _compEqual;

    return -1;
}